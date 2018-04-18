#ifndef MEMSTATISTICDATA_H
#define MEMSTATISTICDATA_H

#include "statisticdata.h"


class MemStatisticData : public StatisticData
{
public:
    MemStatisticData(map<string, std::string>& new_data);
    std::string ToString();
};

#endif // MEMSTATISTICDATA_H
