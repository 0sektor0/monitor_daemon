#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>
#include <fstream>

#define PID_FILE_PATH "/var/run/monitor_daemon/monitor_daemon.pid"

void SetPidFile( char const *fileName ) {
  FILE* f;

  std::ofstream pidFile( fileName, std::ios_base::out | std::ios_base::trunc );

  if( !pidFile.is_open() ) {
    syslog (LOG_ERR, "Can not create pid file.");
    exit(1);
  } else {
    pidFile << getpid() << std::flush;
    pidFile.close();
  }
}

void finish() {
  syslog( LOG_NOTICE, "Monitor-daemon terminated." );
  closelog();
  unlink( PID_FILE_PATH );
  exit( EXIT_SUCCESS );
}

void signal_handler( int sig ) {
  switch( sig ) {
    case SIGTERM:
      finish();
    default:
      break;
  }
}

static void daemonize() {
  pid_t pid;

  // Форк от родителя
  pid = fork();
  // Если не получился форк
  if( pid < 0 ) {
    exit( EXIT_FAILURE );
  }
  // Если форк успешен, завершаем родителя
  if( pid > 0 ) {
    exit( EXIT_SUCCESS );
  }

  if( setsid() < 0 ) {
    exit( EXIT_FAILURE );
  }

  pid = fork();
  if( pid < 0 ) {
    exit( EXIT_FAILURE );
  }
  if( pid > 0 ) {
    exit( EXIT_SUCCESS );
  }

  umask( 0 );

  // Открытие логов
  // /var/log/syslog
  openlog( "monitor-daemon", LOG_NDELAY | LOG_PID, LOG_USER );
  SetPidFile( PID_FILE_PATH );

  if( chdir( "/" ) < 0 ) {
    syslog( LOG_ERR, "Could not change working directory to /" );
    exit( EXIT_FAILURE );
  }

  // Закрытие всех файловых дескрипторов
  for( int x = sysconf( _SC_OPEN_MAX ); x>=0; x--) {
    close( x );
  }

  // Сигналы
  signal( SIGTERM, signal_handler );
}


int main() {
  daemonize();
  syslog( LOG_NOTICE, "Monitor-daemon started." );

  while( true ) {
    // launch statGrabber
    sleep( 5 );
  }

  finish();
}