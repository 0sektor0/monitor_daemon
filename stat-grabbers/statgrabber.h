#ifndef STATGRABBER_H
#define STATGRABBER_H
#define _GLIBCXX_USE_CXX11_ABI 0

#include "statisticdata.h"
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <thread>

using namespace std;


class StatGrabber
{
public:
    StatGrabber();
    ~StatGrabber();
    void Start();
    void Stop();
    bool IsEmpty();
    int GetStatisticNum();
    const bool& GetState();
    virtual void Grab() = 0;
    void SetPeriod(const int& new_period);
    vector<StatisticData*> GetStatistic();


protected:
    vector<StatisticData*> stat_data;
    int period;
    bool state;
};

#endif // STATGRABBER_H
