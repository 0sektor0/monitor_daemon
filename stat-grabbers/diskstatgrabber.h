#ifndef DISKSTATGRABBER_H
#define DISKSTATGRABBER_H

#include "statgrabber.h"
#include "stringutilities.h"


struct Disk
{
    Disk(const std::string&);

    std::string name;
    unsigned int reads;
    unsigned int writes;
    unsigned int iotime;
};


class DiskStatGrabber : public StatGrabber
{
public:
    DiskStatGrabber();
    void Parse();


private:

    const std::string diskinfo = "/proc/diskstats";
    vector<Disk> disks;
};

#endif // DISKSTATGRABBER_H
