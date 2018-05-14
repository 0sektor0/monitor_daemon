#ifndef MEMSTATISTICDATA_H
#define MEMSTATISTICDATA_H

#include "statisticdata.h"
#include "stringutilities.h"

using namespace StringUtilities;


struct MemStatisticData : public StatisticData
{
    MemStatisticData(map<string, std::string>& new_data);
    virtual ~MemStatisticData() {}
    std::string ToString();
};

#endif // MEMSTATISTICDATA_H
