#include "supervisor.h"



Supervisor::Supervisor(unsigned int sleep_time)
{
    SetSleepTime(sleep_time);
}


void Supervisor::AddContainer(GrabbersContainer* container)
{
    enabled_containers.push_back(shared_ptr<GrabbersContainer>(container));
}


void Supervisor::AddSaver(StatSaver* saver)
{
    savers.push_back(shared_ptr<StatSaver>(saver));
}


void Supervisor::SetSleepTime(unsigned int sleep_time)
{
    this->sleep_time = sleep_time != 0 ? sleep_time : DEFAULT_SUPERVISOR_SLEEP;
}


void Supervisor::RunContainer(shared_ptr<GrabbersContainer> container)
{
    container->running = true;

    while(container->running)
    {
        container->mx.lock();
        for(int i = 0; i < container->grabbers.size(); i++)
            try {container->grabbers[i]->Grab();}
            catch(std::runtime_error e) {syslog( LOG_ERR, e.what());}
        container->mx.unlock();

        std::this_thread::sleep_for(std::chrono::milliseconds(container->sleep_time));
    }
}


void Supervisor::Start()
{
    for(shared_ptr<GrabbersContainer> container : enabled_containers)
    {
        std::string message;

        try
        {
            std::thread th([container, this] {RunContainer(container);});
            th.detach();

            message = container->name + " [OK]";
            syslog( LOG_NOTICE, message.c_str() );
        }
        catch(int e)
        {
            message = container->name + " [FAIL]";
            syslog( LOG_ERR, message.c_str() );
        }
    }
}


void Supervisor::Stop()
{
    for(shared_ptr<GrabbersContainer> container : enabled_containers)
    {
        container->running = false;
        std::string message = container->name + " [STOP]";
        syslog( LOG_NOTICE, message.c_str() );
    }
}


void Supervisor::Save()
{
    for(shared_ptr<StatSaver> ss : savers)
        ss->Save(gathered_statistic);

    gathered_statistic = vector<shared_ptr<StatisticData>>();
}


void Supervisor::GrabStatistic()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));

    for(shared_ptr<GrabbersContainer> container : enabled_containers)
        for(shared_ptr<StatGrabber> grabber : container->grabbers)
        {
            container->mx.lock();
            if(!grabber->IsEmpty())
            {
                vector<shared_ptr<StatisticData>> st = grabber->MoveStatistic();
                gathered_statistic.insert(gathered_statistic.end(), st.begin(), st.end());
            }
            container->mx.unlock();
        }

    Save();
}


void Supervisor::DisableContainer(std::string name)
{
    MoveContainer(name, enabled_containers, disabled_containers);
}


void Supervisor::EnableContainer(std::string name)
{
    MoveContainer(name, disabled_containers, enabled_containers);
}


void Supervisor::MoveContainer(std::string name, vector<shared_ptr<GrabbersContainer>>& src, vector<shared_ptr<GrabbersContainer>>& dist)
{
    for(int i = 0; i < src.size(); i++)
        if(src[i]->name == name)
        {
            shared_ptr<GrabbersContainer> container = src[i];
            container->running = !container->running;

            src.erase(src.begin()+i);
            dist.push_back(container);
        }
}


void Supervisor::EnableAllContainers()
{
    MoveAllContainers(disabled_containers, enabled_containers);
}


void Supervisor::DisableAllContainers()
{
    MoveAllContainers(enabled_containers, disabled_containers);
}


void Supervisor::MoveAllContainers(vector<shared_ptr<GrabbersContainer>>& src, vector<shared_ptr<GrabbersContainer>>& dist)
{
    for(int i = 0; i < src.size(); i++)
    {
        src[i]->running = !src[i]->running;
        dist.push_back(src[i]);
    }

    src.clear();
}


Supervisor::~Supervisor()
{
    DisableAllContainers();
}



GrabbersContainer::GrabbersContainer()
{
    running = true;
    sleep_time = DEFAULT_CONTAINER_SLEEP;
}


void GrabbersContainer::SetSleepTime(unsigned int)
{
    this->sleep_time = sleep_time != 0 ? sleep_time : DEFAULT_SUPERVISOR_SLEEP;
}


void GrabbersContainer::AddGrabber(StatGrabber* grabber)
{
    grabbers.push_back(shared_ptr<StatGrabber>(grabber));
}
