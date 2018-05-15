#ifndef DISKSTATISTICDATA_H
#define DISKSTATISTICDATA_H
#define DEFAULT_DISK_NAME "sda"
#define NAME_INDEX 2
#define READS_INDEX 3
#define WRITES_INDEX 7
#define IOTIME_INDEX 13
#define INFO_COUNT 14

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
