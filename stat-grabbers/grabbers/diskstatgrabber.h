#ifndef DISKSTATGRABBER_H
#define DISKSTATGRABBER_H

#include "fstatgrabber.h"
#include "diskstatisticdata.h"
#include <regex>


class DiskStatGrabber : public FStatGrabber
{
public:
    DiskStatGrabber(bool);
    virtual ~DiskStatGrabber() {}
    void Grab();


private:

    const std::string diskinfo = "/proc/diskstats";
    map<string, DiskInfo> disks;
    std::string disk_name_pattern;
};

#endif // DISKSTATGRABBER_H
