#ifndef STATISTICDATA_H
#define STATISTICDATA_H

#include <map>
#include <time.h>
#include <sstream>

using namespace std;


struct StatisticData
{
    std::string name;
    time_t date;
    map<std::string, std::string> data;

    StatisticData(map<std::string, std::string>& new_data);
    StatisticData();
    virtual ~StatisticData() {}
    virtual std::string ToString() = 0;
    bool operator<(const StatisticData&);
};

#endif // STATISTICDATA_H
