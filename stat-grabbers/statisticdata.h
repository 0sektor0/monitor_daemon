#ifndef STATISTICDATA_H
#define STATISTICDATA_H

#include <map>
#include <time.h>

using namespace std;


class StatisticData
{
public:
    StatisticData(map<std::string, std::string>& new_data);
    virtual std::string ToString() = 0;
    const std::string& GetName();
    const time_t& GetDate();


protected:
    std::string name;
    time_t date;
    map<std::string, std::string> data;
};

#endif // STATISTICDATA_H
