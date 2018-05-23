#ifndef CPUSTATGRABBER_H
#define CPUSTATGRABBER_H
#define CPU_FILE "/proc/stat"

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
    const std::string cpuinfo = CPU_FILE;
    std::map<string, CpuInfo> cpus;
    std::string cpu_name_pattern;
    int cpu_count;
};

#endif // CPUSTATGRABBER_H
