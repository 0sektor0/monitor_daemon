#include "printstatsaver.h"


void PrintStatSaver::Save(const vector<StatisticData*>& st)
{
    vector<StatisticData*> data = vector<StatisticData*>(st);
    sort(data.begin(), data.end());

    for(int i = 0; i < st.size(); i++)
        cout << data[i]->ToString() << endl;
}
