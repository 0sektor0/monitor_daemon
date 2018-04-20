#ifndef STATISTICDATA_H
#define STATISTICDATA_H
#define _GLIBCXX_USE_CXX11_ABI 0

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
    virtual std::string ToString() = 0;
    const std::string& GetName();
    const time_t& GetDate();
};

#endif // STATISTICDATA_H
