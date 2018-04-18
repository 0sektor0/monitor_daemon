#include <iostream>
#include "memstatgrabber.h"

using namespace std;


int main()
{
    MemStatGrabber mg;

    cout << "mem stats number: " << mg.GetStatisticNum() << endl;
    mg.Parse();
    mg.Parse();
    cout << "mem stats number: " << mg.GetStatisticNum() << endl;

    vector<StatisticData*> stat;
    mg.GetStatistic(stat);
    cout << "mem stats number: " << mg.GetStatisticNum() << endl;

    return 0;
}
