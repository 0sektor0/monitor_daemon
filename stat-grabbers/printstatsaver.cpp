#include "printstatsaver.h"


void PrintStatSaver::Save(const vector<StatisticData*>& st)
{
    for(int i = 0; i < st.size(); i++)
        cout << st[i]->ToString() << endl;
}
