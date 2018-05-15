#ifndef STATGRABBER_H
#define STATGRABBER_H

#include "statisticdata.h"
#include <syslog.h>
#include <vector>
#include <memory>

using namespace std;


class StatGrabber
{
public:
    StatGrabber();
    virtual ~StatGrabber();
    bool IsEmpty();
    int GetStatisticNum();
    virtual void Grab() = 0;
    vector<shared_ptr<StatisticData>> MoveStatistic();


protected:
    vector<shared_ptr<StatisticData>> stat_data;
};

#endif // STATGRABBER_H
