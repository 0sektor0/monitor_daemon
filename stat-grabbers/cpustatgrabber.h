#ifndef CPUSTATGRABBER_H
#define CPUSTATGRABBER_H

#include <map>
#include "fstatgrabber.h"
#include "cpustatisticdata.h"


class CpuStatGrabber : public FStatGrabber
{
public:
    CpuStatGrabber(bool);
    virtual ~CpuStatGrabber() {}
    void Grab();


private:
    const std::string cpuinfo = "/proc/stat";
    std::map<string, CpuInfo> cpus;
    std::string cpu_name_pattern;
    int cpu_count;
};

#endif // CPUSTATGRABBER_H
