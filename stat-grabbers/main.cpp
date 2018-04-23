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

    for(;;)
    {
        system("clear");

        dg.Grab();
        if (!dg.IsEmpty())
        {
            vector<StatisticData*> st = dg.GetStatistic();
            for(int i = 0; i < st.size(); i++)
            {
                cout << st[i]->ToString() << endl;
                delete st[i];
            }
        }

        mg.Grab();
        if (!mg.IsEmpty())
        {
            vector<StatisticData*> st = mg.GetStatistic();
            for(int i = 0; i < st.size(); i++)
            {
                cout << st[i]->ToString() << endl;
                delete st[i];
            }
        }

        sleep(1);
    }

    return 0;
}
