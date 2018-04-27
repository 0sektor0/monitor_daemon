#ifndef DISKSTATISTICDATA_H
#define DISKSTATISTICDATA_H

#include "statisticdata.h"
#include "stringutilities.h"
#include <vector>

using namespace StringUtilities;


struct Disk
{
    Disk(const std::string&);
    Disk operator - (const Disk& d2);
    Disk();

    std::string name;
    unsigned int reads;
    unsigned int writes;
    unsigned int iotime;
};


struct DiskStatisticData : public StatisticData
{
    DiskStatisticData(const Disk&);
    std::string ToString();
};

#endif // DISKSTATISTICDATA_H
