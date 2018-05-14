#ifndef CPUSTATISTICDATA_H
#define CPUSTATISTICDATA_H

#include <regex>
#include "statisticdata.h"
#include "stringutilities.h"

using namespace StringUtilities;


struct CpuInfo
{
    CpuInfo() {}
    CpuInfo(const std::string&, const std::string&);
    static bool IsCpuFormat(const std::string&, const std::string&);
    static bool IsCpuFormat(const vector<std::string>&, const std::string&);
    CpuInfo operator - (const CpuInfo& c);

    std::string name;
    unsigned int user;
    unsigned int nice;
    unsigned int system;
    unsigned int idle;
    unsigned int iowait;
    unsigned int irq;
    unsigned int softirq;
};


class CpuStatisticData : public StatisticData
{
public:
    CpuStatisticData(const CpuInfo&);
    virtual ~CpuStatisticData() {}
    std::string ToString();


private:
    double CalcPercentage(const double& val, const double& sum);
};

#endif // CPUSTATISTICDATA_H
