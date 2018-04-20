#ifndef MEMSTATISTICDATA_H
#define MEMSTATISTICDATA_H

#include "statisticdata.h"


struct MemStatisticData : public StatisticData
{
    MemStatisticData(map<string, std::string>& new_data);
    std::string ToString();
};

#endif // MEMSTATISTICDATA_H
