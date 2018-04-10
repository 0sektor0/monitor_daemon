#ifndef STATISTICDATA_H
#define STATISTICDATA_H

#include <map>
#include <time.h>

using namespace std;


class StatisticData
{
public:
    StatisticData(const map<string, string>& new_data);
    ~StatisticData();
    virtual string ToString() = 0;

    string name;
    time_t date;
    map<string, string> data;
};

#endif // STATISTICDATA_H
