#ifndef STATGRABBER_H
#define STATGRABBER_H

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
    const bool& GetState();
    void SetPeriod(const int& new_period);
    virtual vector<StatisticData> GetStatData(string req) = 0;


private:
    virtual void Parse() = 0;

    vector<ifstream> stat_files;
    vector<StatisticData> stat_data;
    int period;
    bool state;
};

#endif // STATGRABBER_H
