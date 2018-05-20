#ifndef NETDEVGRABBERS_H
#define NETDEVGRABBERS_H
#define NETDEV_FILE "/proc/net/dev"

#include <map>
#include "fstatgrabber.h"
#include "netdevstatisticdata.h"


class NetDevGrabber : public FStatGrabber
{
public:
    NetDevGrabber(const bool&);
    virtual ~NetDevGrabber() {}
    void Grab();


private:
    const std::string netdevinfo = NETDEV_FILE;
    std::map<string, NetDevInfo> interfaces;
    bool is_raw;

    void GrabRaw();
    void GrabDiffer();
};

#endif // NETDEVGRABBERS_H
