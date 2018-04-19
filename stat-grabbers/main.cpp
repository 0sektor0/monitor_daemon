#include <iostream>
#include "memstatgrabber.h"
#include "diskstatgrabber.h"

using namespace std;


int main()
{
    /*Code for testing new statgrabbers*/
    DiskStatGrabber dg;
    MemStatGrabber mg;

    cout << endl << "mem stats number: " << mg.GetStatisticNum() << endl;
    dg.Parse();
    dg.Parse();
    mg.Parse();
    mg.Parse();
    cout << endl << "mem stats number: " << mg.GetStatisticNum() << endl;

    vector<StatisticData*> stat;
    mg.GetStatistic(stat);
    cout << endl << "mem stats number: " << mg.GetStatisticNum() << endl;

    cout << endl << stat[0]->ToString();

    return 0;
}
