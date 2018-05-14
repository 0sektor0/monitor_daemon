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

#define PID_FILE_PATH "/var/run/monitor_daemon/monitor_daemon.pid"
#define STATISTIC_DIRECTORY "/var/log/monitor_daemon"


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

void start_stat_gathering()
{
    Supervisor sv;
    GrabbersContainer* grubc = new GrabbersContainer();

    grubc->name = "md";
    grubc->period = 3000;
    grubc->grabbers.push_back(new MemStatGrabber());
    grubc->grabbers.push_back(new DiskStatGrabber(true));
    grubc->grabbers.push_back(new CpuStatGrabber(true));
    sv.AddContainer(grubc);

    //sv.AddSaver(new PrintStatSaver());
    sv.AddSaver(new FStatSaver(STATISTIC_DIRECTORY));
    sv.SetPeriod(3000);

    sv.Start();
    for(;;)
        sv.GrabStatistic();

    sv.Stop();
}


int main()
{
    daemonize();
    syslog( LOG_NOTICE, "Monitor-daemon started." );

    //запуск сбора статистики
    start_stat_gathering();

    finish();
}

/*int main()
{
    openlog( "monitor-daemon", LOG_NDELAY | LOG_PID, LOG_USER );

    Supervisor sv;
    GrabbersContainer* grubc = new GrabbersContainer();

    grubc->name = "md";
    grubc->period = 3000;
    grubc->grabbers.push_back(new MemStatGrabber());
    grubc->grabbers.push_back(new DiskStatGrabber(true));
    grubc->grabbers.push_back(new CpuStatGrabber(true));
    sv.AddContainer(grubc);

    sv.AddSaver(new PrintStatSaver());
    sv.AddSaver(new FStatSaver(STATISTIC_DIRECTORY));
    sv.SetPeriod(3000);

    sv.Start();
    for(;;)
        sv.GrabStatistic();

    sv.Stop();
}*/
