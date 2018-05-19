#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include <unistd.h>
#include <curses.h>
#include <algorithm>
#include <time.h>
#include <boost/filesystem.hpp>
using namespace boost::filesystem;

#define LOG_DIR_PATH "/Users/andrey/tp-s1-cpp-project/daemon/logs/"
#define LOG_FILE_EXTENSION ".log"

static void show_usage( std::string name ) {
  std::cout << "Usage: " << name << " [-l | --live] [cpu | memory | sda]\n"
  << "Options:\n"
  << "\t-h,--help\tShow this help message\n"
  << "\t-l,--live\tShow real time statistics\n"
  << "\tcpu\t\tShow cpu statistics\n"
  << "\tmemory\t\tShow memory statistics\n"
  << "\tsda\t\tShow sda statistics"
  << std::endl;
} 

std::string newest_log_file() {
  path directory( LOG_DIR_PATH );
  if( !( exists( directory ) && is_directory( directory ) ) ) {
    std::cout << "Statistic files directory is invalid." << std::endl;
    exit( 1 );
  }
  long int newest_file_name = 1; 
  for( auto &p : directory_iterator( directory ) ) {
    path file( p );
    long int file_name = atol( file.stem().c_str() );
    newest_file_name = std::max( file_name, newest_file_name );
  }
  path file( std::to_string( newest_file_name ) );
  return file.string();
}

std::vector<std::string> get_stats( std::string type ) {
  type += "_statistic";
  std::string statFileName = LOG_DIR_PATH + newest_log_file() + LOG_FILE_EXTENSION;
  std::ifstream statFile( statFileName, std::ios_base::in );
  if( !statFile.is_open() ) {
    std::cout << "Can not open statistic file." << std::endl;
    exit( 1 );
  } 

  std::vector<std::string> fileLines;
  std::string line;
  while( getline( statFile, line ) ) {
    fileLines.push_back( line );
  }
  statFile.close();

  std::vector<std::string>::reverse_iterator statLine = std::find_if( fileLines.rbegin(), fileLines.rend(), [type]( std::string i ) { return i == type; });

  std::vector<std::string> statsVector;
  statsVector.push_back( *(statLine--) );
  while( !(*statLine).empty() ) {
    statsVector.push_back( *(statLine--) );
  }

  // Время в удобном виде
  struct tm timeInfo;
  memset( &timeInfo, 0, sizeof( struct tm ) );
  strptime( statsVector[1].c_str(), "%s", &timeInfo );
  statsVector[1] = asctime( &timeInfo );
  statsVector[1].pop_back();
  
  return statsVector;
}

void show_live_data( std::string type = "all" ) {
  initscr();
  noecho();
  halfdelay( 10 );
  bool ex = false;
  while( !ex ) {
    clear();
    printw( "PRESS q TO EXIT.\n" );
    std::vector<std::string> data;
    if( strcmp( type.c_str(), "all" ) == 0 ) {
      data = get_stats( "cpu" );
      for( auto line : data ) {
        printw( "%s\n", line.c_str() );
      }
      printw( "\n" );
      data = get_stats( "memory" );
      for( auto line : data ) {
        printw( "%s\n", line.c_str() );
      }
      printw( "\n" );
      data = get_stats( "sda" );
      for( auto line : data ) {
        printw( "%s\n", line.c_str() );
      }
    } else {
      data = get_stats( type );
      for( auto line : data ) {
        printw( "%s\n", line.c_str() );
      }
    }
    refresh();

    int ch = getch();
    if( ch == 'q' ) {
      ex = true;
    }
  }

  endwin();
}

void show_data( std::string type = "all" ) {
  std::vector<std::string> data;
  if( strcmp( type.c_str(), "all" ) == 0 ) {
    data = get_stats( "cpu" );
    for( auto line : data ) {
      std::cout << line << std::endl;
    }
    std::cout << '\n';
    data = get_stats( "memory" );
    for( auto line : data ) {
      std::cout << line << std::endl;
    }
    std::cout << '\n';
    data = get_stats( "sda" );
    for( auto line : data ) {
      std::cout << line << std::endl;
    }
  } else {
    data = get_stats( type );
    for( auto line : data ) {
      std::cout << line << std::endl;
    }
  }
}


int main(int argc, char const *argv[]) {
  switch( argc ) {
    case 1: {
      show_data();
      return 0;
    }

    case 2: {
      if( strcmp( argv[1], "-h" ) == 0 || strcmp( argv[1], "--help") == 0 ) {
        show_usage( argv[0] );
        return 0;
      } else if( strcmp( argv[1], "cpu" ) == 0 || strcmp( argv[1], "memory") == 0 || strcmp( argv[1], "sda") == 0 ) {
        show_data( argv[1] );
        return 0;
      } else if( strcmp( argv[1], "-l" ) == 0 || strcmp( argv[1], "--live") == 0 ) {
        show_live_data();
        return 0;
      } else {
        show_usage( argv[0] );
        return 1;
      }
    }

    case 3: {
      if( strcmp( argv[1], "-l" ) == 0 || strcmp( argv[1], "--live") == 0 ) {
        if( strcmp( argv[2], "cpu" ) == 0 || strcmp( argv[2], "memory") == 0 || strcmp( argv[2], "sda") == 0 ) {
          show_live_data( argv[2] );
          return 0;
        } else {
          show_usage( argv[0] );
          return 1;
        }
      } else {
        show_usage( argv[0] );
        return 1;
      }
    }

    default: {
      show_usage( argv[0] );
      return 1;
    }
  }
}