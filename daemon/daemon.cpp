#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>
#include <fstream>
#include <iostream>
#include <libconfig.h++>
#include "supervisor.h"

using namespace std;
using namespace libconfig;

#define PID_FILE_PATH "/var/run/monitor_daemon.pid"
#define STATISTIC_DIRECTORY "/var/log/monitor_daemon"
#define CONFIG_FILE_PATH "/etc/monitor_daemon.cfg"



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


Supervisor Configure()
{
    //дефолтные значения
    int sv_sleep_time = 3000;
    int mdc_sleep_time = 3000;
    int net_sleep_time = 3000;
    bool disk_single = true;
    bool cpu_single = true;
    bool net_all = true;

    //считываем конфиги
    Config conf;
    try { conf.readFile(CONFIG_FILE_PATH); }
    catch(...)
    {
        std::string message = "Cant find config file: " + std::string(CONFIG_FILE_PATH);
        syslog( LOG_ALERT, message.c_str());
    }

    try { sv_sleep_time = conf.lookup("supervisor.sv_sleep_time"); }
    catch(...) { syslog( LOG_ALERT, "unnable to read sv_sleep_time from configs"); }

    try { mdc_sleep_time = conf.lookup("supervisor.mdc_sleep_time"); }
    catch(...) { syslog( LOG_ALERT, "unnable to read mdc_sleep_time from configs"); }

    try { net_sleep_time = conf.lookup("supervisor.net_sleep_time"); }
    catch(...) { syslog( LOG_ALERT, "unnable to read net_sleep_time from configs"); }

    try { disk_single = conf.lookup("supervisor.disk_single"); }
    catch(...) { syslog( LOG_ALERT, "unnable to read disk_single from configs"); }

    try { cpu_single = conf.lookup("supervisor.cpu_single"); }
    catch(...) { syslog( LOG_ALERT, "unnable to read cpu_single from configs"); }

    try { net_all = conf.lookup("supervisor.net_all"); }
    catch(...) { syslog( LOG_ALERT, "unnable to read net_all from configs"); }

    //устанавливаем интервал опроса контейнеров в 3 секуны
    Supervisor sv(sv_sleep_time);
    GrabbersContainer* grubc1 = new GrabbersContainer();
    GrabbersContainer* grubc2 = new GrabbersContainer();

    //инициализируем контейнер для сбора статистик о памяти, диках и цпу
    grubc1->name = "mdc";
    //устанавливаем интервал опроса этого контейнера в 3 секунды
    grubc1->SetSleepTime(mdc_sleep_time);
    grubc1->AddGrabber(new MemStatGrabber());
    grubc1->AddGrabber(new DiskStatGrabber(disk_single));
    grubc1->AddGrabber(new CpuStatGrabber(cpu_single));
    sv.AddContainer(grubc1);

    grubc2->name = "net";
    grubc1->SetSleepTime(net_sleep_time);
    grubc2->AddGrabber(new NetDevGrabber(net_all));
    sv.AddContainer(grubc2);

    //для сохранения статистики назначаем файловый Saver
    sv.AddSaver(new FStatSaver(STATISTIC_DIRECTORY, 0));
    return sv;
}


void start_stat_gathering()
{
    //устанавливаем интервал опроса контейнеров в 3 секуны
    Supervisor sv = Configure();
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
    Supervisor sv = Configure();
    sv.AddSaver((new PrintStatSaver()));

    sv.Start();
    for(int i = 0; i < 2; i++)
        sv.GrabStatistic();

    sv.Stop();
}*/
