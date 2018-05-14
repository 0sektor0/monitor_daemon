#ifndef SUPERVISOR_H
#define SUPERVISOR_H

#include <mutex>
#include <thread>
#include <chrono>
#include "statsaver.h"
#include "statgrabber.h"
#include "printstatsaver.h"
#include "fstatsaver.h"
#include "memstatgrabber.h"
#include "cpustatgrabber.h"
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
    virtual ~Supervisor();
    void Stop();
    void Start();
    void GrabStatistic();
    void AddSaver(StatSaver*);
    void SetPeriod(const int&);
    void AddContainer(GrabbersContainer*);
    void EnableAllContainers();
    void DisableAllContainers();
    void EnableContainer(const std::string&);
    void DisableContainer(const std::string&);


private:
    vector<GrabbersContainer*> enabled_containers;
    vector<GrabbersContainer*> disabled_containers;
    vector<StatisticData*> gathered_statistic;
    vector<StatSaver*> savers;
    unsigned int period;

    void MoveContainer(const std::string&, vector<GrabbersContainer*>&, vector<GrabbersContainer*>&);
    void MoveAllContainers(vector<GrabbersContainer*>&, vector<GrabbersContainer*>&);
    void RunContainer(GrabbersContainer*);
    void Save();

    template<class T>
    void DeleteVectorsElements(vector<T*>& v)
    {
        for(int i = 0; i < v.size(); i++)
            delete v[i];
    }
};

#endif // SUPERVISOR_H
