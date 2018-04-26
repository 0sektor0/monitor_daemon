#ifndef SUPERVISOR_H
#define SUPERVISOR_H

#include <thread>
#include <chrono>
#include <mutex>
#include "statgrabber.h"
#include "memstatgrabber.h"
#include "diskstatgrabber.h"



struct GrabbersContainer
{
    vector<StatGrabber*> grabbers;
    unsigned int period;
    std::string name;
    std::mutex mx;
    bool running;

    GrabbersContainer() : running(true), period(1000) {}
};


class Supervisor
{
public:
    Supervisor();
    ~Supervisor();
    void Start();
    void Save();
    void Stop();


private:
    vector<GrabbersContainer*> enabled_containers;
    vector<GrabbersContainer*> disabled_containers;
    vector<StatisticData*> gathered_statistic;
    void GrabStatistic();
    unsigned int period;

    void RunContainer(GrabbersContainer*);
};

#endif // SUPERVISOR_H
