#ifndef STATSAVER_H
#define STATSAVER_H

#include "statisticdata.h"
#include <syslog.h>
#include <vector>
#include <memory>

using namespace std;


class StatSaver
{
public:
    virtual void Save(const vector<shared_ptr<StatisticData>>&) = 0;
    //void
};

#endif // STATSAVER_H
