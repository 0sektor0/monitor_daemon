#ifndef SUPERVISOR_H
#define SUPERVISOR_H
#define DEFAULT_CONTAINER_SLEEP 3000
#define DEFAULT_SUPERVISOR_SLEEP 3000

#include <mutex>
#include <thread>
#include <chrono>
#include <memory>
#include "statsaver.h"
#include "statgrabber.h"
#include "printstatsaver.h"
#include "fstatsaver.h"
#include "memstatgrabber.h"
#include "cpustatgrabber.h"
#include "diskstatgrabber.h"
#include "netdevgrabbers.h"


struct GrabbersContainer
{
    vector<StatGrabber*> grabbers;
    unsigned int sleep_time;
    std::string name;
    std::mutex mx;
    bool running;

    GrabbersContainer();
    void SetSleepTime(const unsigned int&);
};


class Supervisor
{
public:
    void Stop();
    void Start();
    virtual ~Supervisor() {}
    Supervisor(const unsigned int&);
    Supervisor() : Supervisor(DEFAULT_SUPERVISOR_SLEEP) {}
    void GrabStatistic();
    void AddSaver(StatSaver*);
    void AddContainer(GrabbersContainer*);
    void EnableAllContainers();
    void DisableAllContainers();
    void SetSleepTime(const unsigned int&);
    void EnableContainer(const std::string&);
    void DisableContainer(const std::string&);


private:
    vector<shared_ptr<GrabbersContainer>> enabled_containers;
    vector<shared_ptr<GrabbersContainer>> disabled_containers;
    vector<shared_ptr<StatisticData>> gathered_statistic;
    vector<shared_ptr<StatSaver>> savers;
    unsigned int sleep_time;

    void MoveContainer(const std::string&, vector<shared_ptr<GrabbersContainer>>&, vector<shared_ptr<GrabbersContainer>>&);
    void MoveAllContainers(vector<shared_ptr<GrabbersContainer>>&, vector<shared_ptr<GrabbersContainer>>&);
    void RunContainer(shared_ptr<GrabbersContainer>);
    void Save();
};

#endif // SUPERVISOR_H
