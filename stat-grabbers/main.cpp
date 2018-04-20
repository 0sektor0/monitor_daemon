#define _GLIBCXX_USE_CXX11_ABI 0

#include <iostream>
#include "memstatgrabber.h"
#include "diskstatgrabber.h"

using namespace std;


int main()
{
    /*Code for testing new statgrabbers*/
    DiskStatGrabber dg;
    MemStatGrabber mg;


    cout << "mem stats number: " << mg.GetStatisticNum() << endl;
    mg.Parse();
    dg.Parse();
    sleep(1);
    mg.Parse();
    dg.Parse();
    cout << "mem stats number: " << mg.GetStatisticNum() << endl;

    vector<StatisticData*> stat;
    mg.GetStatistic(stat);
    cout << "mem stats number: " << mg.GetStatisticNum() << endl;

    cout << endl << stat[0]->ToString();
    cout << endl << stat[1]->ToString();

    return 0;
}
