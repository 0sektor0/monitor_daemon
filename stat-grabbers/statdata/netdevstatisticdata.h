#ifndef NETDEVSTATISTICDATA_H
#define NETDEVSTATISTICDATA_H
#define VALUES_SIZE 17

#define INTERFACE_INDEX 0
#define BYTES_RECIVED_INDEX 1
#define PACKETS_RECIVED_INDEX 2
#define ERRS_RECIVED_INDEX 3

#define BYTES_SENDED_INDEX 8
#define PACKETS_SENDED_INDEX 9
#define ERRS_SENDED_INDEX 10

#include "statisticdata.h"
#include "stringutilities.h"

using namespace StringUtilities;


struct NetDevInfo
{
    NetDevInfo();
    NetDevInfo(const std::string&);
    NetDevInfo operator - (const NetDevInfo&);

    std::string interface;
    unsigned int errs_recived;
    unsigned int bytes_recived;
    unsigned int packets_recived;
    unsigned int errs_sended;
    unsigned int bytes_sended;
    unsigned int packets_sended;
};


class NetDevStatisticData : public StatisticData
{
public:
    NetDevStatisticData(const NetDevInfo&);
    virtual ~NetDevStatisticData(){}
    std::string ToString();
};

#endif // NETDEVSTATISTICDATA_H
