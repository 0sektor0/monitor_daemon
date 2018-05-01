#ifndef STATSAVER_H
#define STATSAVER_H

#include "statisticdata.h"
#include <vector>

using namespace std;


class StatSaver
{
public:
    virtual void Save(const vector<StatisticData*>&) = 0;
};

#endif // STATSAVER_H
