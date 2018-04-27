#ifndef DISKSTATGRABBER_H
#define DISKSTATGRABBER_H

#include "fstatgrabber.h"
#include "diskstatisticdata.h"


class DiskStatGrabber : public FStatGrabber
{
public:
    DiskStatGrabber();
    void Grab();


private:

    const std::string diskinfo = "/proc/diskstats";
    map<string, Disk> disks;
};

#endif // DISKSTATGRABBER_H
