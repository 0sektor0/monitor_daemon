#include "supervisor.h"



Supervisor::Supervisor()
{
    period = 60000;
}


void Supervisor::AddContainer(GrabbersContainer* container)
{
    enabled_containers.push_back(container);
}


void Supervisor::AddSaver(StatSaver* saver)
{
    savers.push_back(saver);
}


void Supervisor::SetPeriod(const int& period)
{
    this->period = period;
}


void Supervisor::RunContainer(GrabbersContainer* container)
{
    container->running = true;

    while(container->running)
    {
        container->mx.lock();
        for(int i = 0; i < container->grabbers.size(); i++)
            container->grabbers[i]->Grab();
        container->mx.unlock();

        //clog << "container " + container->name + " processed" << endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(container->period));
    }
}


void Supervisor::Start()
{
    for(GrabbersContainer* container : enabled_containers)
    {
        std::string message;

        try
        {
            std::thread th([=] { RunContainer(container); });
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
    for(GrabbersContainer* container : enabled_containers)
    {
        container->running = false;
        std::string message = container->name + " [STOP]";
        syslog( LOG_NOTICE, message.c_str() );
    }
}


void Supervisor::Save()
{
    for(StatSaver* ss : savers)
        ss->Save(gathered_statistic);

    DeleteVectorsElements(gathered_statistic);
    gathered_statistic = vector<StatisticData*>();
}


void Supervisor::GrabStatistic()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(period));

    for(GrabbersContainer* container : enabled_containers)
        for(StatGrabber* grabber : container->grabbers)
        {
            container->mx.lock();
            if(!grabber->IsEmpty())
            {
                vector<StatisticData*> st = grabber->GetStatistic();
                gathered_statistic.insert(gathered_statistic.end(), st.begin(), st.end());
            }
            container->mx.unlock();
        }

    Save();
}


void Supervisor::DisableContainer(const std::string& name)
{
    MoveContainer(name, enabled_containers, disabled_containers);
}


void Supervisor::EnableContainer(const std::string& name)
{
    MoveContainer(name, disabled_containers, enabled_containers);
}


void Supervisor::MoveContainer(const std::string& name, vector<GrabbersContainer*>& src, vector<GrabbersContainer*>& dist)
{
    for(int i = 0; i < src.size(); i++)
        if(src[i]->name == name)
        {
            GrabbersContainer* container = src[i];
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


void Supervisor::MoveAllContainers(vector<GrabbersContainer*>& src, vector<GrabbersContainer*>& dist)
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
    DeleteVectorsElements(disabled_containers);
    DeleteVectorsElements(enabled_containers);
    DeleteVectorsElements(gathered_statistic);
    DeleteVectorsElements(savers);
}
