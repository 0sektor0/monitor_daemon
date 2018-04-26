#include <iostream>
#include "unistd.h"
#include "supervisor.h"

using namespace std;


int main()
{
    Supervisor sv;

    sv.Start();
    sleep(5);
    sv.Stop();
    sv.Save();

    return 0;
}
