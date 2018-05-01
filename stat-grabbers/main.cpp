#include <iostream>
#include "unistd.h"
#include "supervisor.h"

using namespace std;


int main()
{
    Supervisor sv;

    sv.Start();
    sv.SetPeriod(60000);
    for(;;)
        sv.GrabStatistic();
    sv.Stop();

    return 0;
}
