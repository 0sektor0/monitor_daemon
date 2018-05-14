#ifndef DISKSTATISTICDATA_H
#define DISKSTATISTICDATA_H

#include "statisticdata.h"
#include "stringutilities.h"
#include <vector>

using namespace StringUtilities;


struct DiskInfo
{
    DiskInfo(const std::string&);
    DiskInfo operator - (const DiskInfo& d2);
    DiskInfo();

    std::string name;
    unsigned int reads;
    unsigned int writes;
    unsigned int iotime;
};


struct DiskStatisticData : public StatisticData
{
    DiskStatisticData(const DiskInfo&);
    virtual ~DiskStatisticData() {}
    std::string ToString();
};

#endif // DISKSTATISTICDATA_H
