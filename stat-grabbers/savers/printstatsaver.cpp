#include "printstatsaver.h"


void PrintStatSaver::Save(const vector<shared_ptr<StatisticData>>& st)
{
    vector<shared_ptr<StatisticData>> data = vector<shared_ptr<StatisticData>>(st);
    stable_sort(data.begin(), data.end());

    for(int i = 0; i < st.size(); i++)
        cout << data[i]->ToString() << endl;
}
