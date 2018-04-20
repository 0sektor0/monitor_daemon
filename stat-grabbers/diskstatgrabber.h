#ifndef DISKSTATGRABBER_H
#define DISKSTATGRABBER_H

#include "statgrabber.h"
#include "diskstatisticdata.h"


class DiskStatGrabber : public StatGrabber
{
public:
    DiskStatGrabber();
    void Parse();


private:

    const std::string diskinfo = "/proc/diskstats";
    map<string, Disk> disks;
};

#endif // DISKSTATGRABBER_H
