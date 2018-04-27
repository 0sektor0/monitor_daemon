#ifndef STATGRABBER_H
#define STATGRABBER_H

#include "statisticdata.h"
#include <vector>

using namespace std;


class StatGrabber
{
public:
    StatGrabber();
    ~StatGrabber();
    bool IsEmpty();
    int GetStatisticNum();
    virtual void Grab() = 0;
    vector<StatisticData*> GetStatistic();


protected:
    vector<StatisticData*> stat_data;
};

#endif // STATGRABBER_H
