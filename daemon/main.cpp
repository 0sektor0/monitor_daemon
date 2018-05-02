#include <sys/types.h>
#include <sys/stat.h>
#include <cstdio>
#include <cstdlib>
#include <fcntl.h>
#include <cerrno>
#include <unistd.h>
#include <syslog.h>
#include <cstring>
#include <csignal>

void signal_handler( int sig ) {
    switch( sig ) {
        case SIGHUP:
            // "hangup signal catched"
            break;
        case SIGTERM:
            // "terminate signal catched"
            syslog( LOG_NOTICE, "Stopping monitor-daemon" );
            closelog();
            exit( EXIT_SUCCESS );
        default:
            break;
    }
}

bool do_heartbeat() {
    // TODO: вызов supervisor
    syslog( LOG_NOTICE, "Made a heartbeat!" );
    return true;
}

// TODO: аргументы командной строки
int main( ) {
    printf( "test\n" );
    pid_t pid, sid;

    // Форк от родителя для демонизации
    pid = fork();

    // Проверка успешного форка
    if( pid > 0 ) {
        printf( "Forked\n" );
        exit( EXIT_SUCCESS );
    } else if( pid < 0 ) {
        printf( "Error: Start Daemon failed (%s)\n", strerror( errno ) );
        exit( EXIT_FAILURE );
    }

    // генерация sid для демона
    sid = setsid();
    // Проверка sid
    if( sid < 0) {
        syslog( LOG_ERR, "Could not generate session ID for child process" );
        exit( EXIT_FAILURE );
    }

    // новый форк, чтобы процесс не был session leader
    pid = fork();
    if (pid < 0) {
        printf( "Not forked\n" );
        exit( EXIT_FAILURE );
    } else if (pid > 0) {
        printf( "Forked\n" );
        exit( EXIT_SUCCESS );
    }

    // umask для доступа к файлам, сгенерированным демоном
    umask( 0 );

    // TODO: Открытие логов для демона ( /var/log/... )
    openlog( "monitor-daemon", LOG_NDELAY | LOG_PID, LOG_USER );
    syslog( LOG_NOTICE, "Successfully started monitor-daemon" );

    // Переход в корневую директорию
    if( chdir( "/" ) < 0) {
        syslog( LOG_ERR, "Could not change working directory to /" );
        exit( EXIT_FAILURE );
    }

    // Закрытие файловых дескрипторов в целях безопасности
    close( STDIN_FILENO );
    close( STDOUT_FILENO );
    close( STDERR_FILENO );

    // signals handler binding
    signal( SIGCHLD, SIG_IGN );
    signal( SIGTSTP, SIG_IGN );
    signal( SIGTTOU, SIG_IGN );
    signal( SIGTTIN, SIG_IGN );
    signal( SIGHUP, signal_handler );
    signal( SIGTERM, signal_handler );

    const char *pid_file_name = "/var/run/monitor_daemon/monitor_daemon.pid";
    int pidFileHandle = open( pid_file_name, O_RDWR|O_CREAT, 0600 );
    if( pidFileHandle == -1 ) {
        // открываем файл для pid
        syslog( LOG_NOTICE, "Could not open PID lock file %s, exiting", pid_file_name );
        exit( EXIT_FAILURE );
    }

    // блокируем файл для pid
    if( lockf( pidFileHandle, F_TLOCK, 0) == -1 ) {
        /* Couldn't get lock on lock file */
        syslog( LOG_ERR, "Could not lock PID lock file %s, exiting", pid_file_name );
        exit( EXIT_FAILURE );
    }
    // пишем pid
    char str[256];
    sprintf( str, "%d\n", getpid() );
    write( pidFileHandle, str, strlen( str ) );
    syslog( LOG_NOTICE, "Successfully wrote pid" );

    // Инициализация параметров демона
    // TODO: конфигурационный файл
    const int SLEEP_INTERVAL = 5;

    while( !do_heartbeat() ) {
        // sleep( SLEEP_INTERVAL );
    }
    // удаление pid файла
    syslog( LOG_NOTICE, "Stopping monitor-daemon" );
    closelog();
    exit( EXIT_SUCCESS );
}