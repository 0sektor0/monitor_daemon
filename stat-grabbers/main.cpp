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
    grubc->grabbers.push_back(new DiskStatGrabber());
    sv.AddContainer(grubc);

    sv.AddSaver(new PrintStatSaver());
    sv.AddSaver(new FStatSaver("/var/log/sg"));

    sv.SetPeriod(10000);
    sv.DisableAllContainers();
    //sv.DisableContainer(grubc->name);

    sv.Start();
    for(;;)
        sv.GrabStatistic();
    sv.Stop();

    return 0;
}
