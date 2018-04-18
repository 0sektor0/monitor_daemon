#ifndef MEMSTATGRABBER_H
#define MEMSTATGRABBER_H

#include "statgrabber.h"
#include "memstatisticdata.h"


class MemStatGrabber : public StatGrabber
{
public:
    MemStatGrabber();
    void Parse();


private:
    std::string GetStat(const std::string& token, std::ifstream& f);

    const std::string meminfo = "/proc/meminfo";
    const int meminfo_ind = 0;
    //vector<std::string>
};

#endif // MEMSTATGRABBER_H
