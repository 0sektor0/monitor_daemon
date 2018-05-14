#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include <unistd.h>
#include <curses.h>

#define DATA_FILE_PATH "/home/deploy/example.txt"

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

std::vector<std::string> parse_data( std::string type ) {
  std::vector<std::string> data;

  std::ifstream myFile( DATA_FILE_PATH, std::ios_base::in );
  if( myFile.is_open() ) {
    std::string line;
    // parse by type
    // while( getline ( myFile, line ) ) {
    //   data.push_back( line );
    // }
    myFile.close();
    return data;
  } else {
    exit(1);
  }
}

void show_live_data( std::string type = "all" ) {
  initscr();
  noecho();
  halfdelay( 10 );
  bool ex = false;
  while( !ex ) {
    clear();
    printw( "Press q to exit.\n" );
    std::vector<std::string> data;
    data = parse_data( type );
    for( auto line : data ) {
      printw( "%s\n", line.c_str() );
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
  data = parse_data( type );
  for( auto line : data ) {
    std::cout << line << std::endl;
  }
}

/*
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
*/
