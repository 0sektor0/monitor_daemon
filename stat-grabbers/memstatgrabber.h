#ifndef MEMSTATGRABBER_H
#define MEMSTATGRABBER_H

#include "fstatgrabber.h"
#include "memstatisticdata.h"


class MemStatGrabber : public FStatGrabber
{
public:
    MemStatGrabber();
    void Grab();


private:
    std::string GetStat(const std::string& token, std::ifstream& f);

    const std::string meminfo = "/proc/meminfo";
    const int meminfo_ind = 0;
    //vector<std::string>
};

#endif // MEMSTATGRABBER_H
