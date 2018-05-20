#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>
#include <fstream>
#include <iostream>
#include "supervisor.h"

using namespace std;

#define PID_FILE_PATH "/var/run/monitor_daemon.pid"
#define STATISTIC_DIRECTORY "/var/log/monitor_daemon"

bool is_daemon_running( const char *processName, char const *pidFileName ) {
  std::ifstream pidFile( pidFileName );
  if( !pidFile.good() ) {
    pidFile.close();
    return false;
  } else {
    std::string pid;
    getline( pidFile, pid );
    pidFile.close();
    if( kill( std::stoi(pid), 0) == 0 ) {
      return true;
    } else{
      return false;
    }
  }
}

void set_pid_file( char const *fileName ) {
  std::ofstream pidFile( fileName, std::ios_base::out | std::ios_base::trunc );

  if( !pidFile.is_open() ) {
    syslog (LOG_ERR, "Can not create pid file.");
    exit( 1 );
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
    case SIGHUP:
      break;
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
  set_pid_file( PID_FILE_PATH );

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
  signal( SIGHUP, signal_handler );
}

void start_stat_gathering()
{
    //устанавливаем интервал опроса контейнеров в 3 секуны
    Supervisor sv(3000);
    GrabbersContainer* grubc1 = new GrabbersContainer();
    GrabbersContainer* grubc2 = new GrabbersContainer();

    //инициализируем контейнер для сбора статистик о памяти, диках и цпу
    grubc1->name = "mdc";
    //устанавливаем интервал опроса этого контейнера в 3 секунды
    grubc1->SetSleepTime(3000);
    grubc1->grabbers.push_back(new MemStatGrabber());
    grubc1->grabbers.push_back(new DiskStatGrabber(true));
    grubc1->grabbers.push_back(new CpuStatGrabber(true));
    sv.AddContainer(grubc1);

    grubc2->name = "net";
    grubc1->SetSleepTime(6000);
    grubc2->grabbers.push_back(new NetDevGrabber(true));
    sv.AddContainer(grubc2);

    //для сохранения статистики назначаем файловый Saver
    sv.AddSaver(new FStatSaver(STATISTIC_DIRECTORY, 0));
    sv.Start();

    for(;;)
        sv.GrabStatistic();

    sv.Stop();
}


int main( int argc, char const *argv[] ) {
    if( is_daemon_running( argv[0], PID_FILE_PATH ) ) {
        std::cerr << "Daemon is already running." << std::endl;
        exit( 1 );
    }
    daemonize();
    syslog( LOG_NOTICE, "Monitor-daemon started." );

    //запуск сбора статистики
    start_stat_gathering();

    finish();
}

/*int main()
{
    openlog( "monitor-daemon", LOG_NDELAY | LOG_PID, LOG_USER );

    Supervisor sv(3000);
    GrabbersContainer* grubc1 = new GrabbersContainer();
    GrabbersContainer* grubc2 = new GrabbersContainer();

    grubc1->name = "mdc";
    grubc1->grabbers.push_back(new MemStatGrabber());
    grubc1->grabbers.push_back(new DiskStatGrabber(true));
    grubc1->grabbers.push_back(new CpuStatGrabber(true));
    sv.AddContainer(grubc1);

    grubc2->name = "net";
    grubc2->grabbers.push_back(new NetDevGrabber(true));
    sv.AddContainer(grubc2);

    sv.AddSaver(new PrintStatSaver());
    sv.AddSaver(new FStatSaver(STATISTIC_DIRECTORY, 5));

    sv.Start();
    for(int i = 0; i < 2; i++)
        sv.GrabStatistic();

    sv.Stop();
}*/
