#include <iostream>
#include "unistd.h"
#include "supervisor.h"

using namespace std;


int main()
{
    Supervisor sv;

    GrabbersContainer* grubc = new GrabbersContainer();
    grubc->name = "md";
    grubc->grabbers.push_back(new MemStatGrabber());
    grubc->grabbers.push_back(new DiskStatGrabber(true));
    grubc->grabbers.push_back(new CpuStatGrabber(true));
    sv.AddContainer(grubc);

    sv.AddSaver(new PrintStatSaver());
    sv.AddSaver(new FStatSaver("/var/log/sglog"));

    //sv.SetPeriod(1000);
    sv.SetPeriod(10000);

    //sv.DisableAllContainers();
    //sv.DisableContainer(grubc->name);

    sv.Start();
    //for(;;)
    for(int i = 0; i < 1; i++)
        sv.GrabStatistic();
    sv.Stop();

    return 0;
}
