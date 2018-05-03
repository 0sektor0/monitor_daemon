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

        clog << "container " + container->name + " processed" << endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(container->period));
    }
}


void Supervisor::Start()
{
    for(GrabbersContainer* container : enabled_containers)
    {
        try
        {
            std::thread th([=] { RunContainer(container); });
            th.detach();
            cout << container->name + " [OK]" << endl;
        }
        catch(int e)
        {
            clog << container->name + " [FAIL]" << endl;
        }
    }
}


void Supervisor::Stop()
{
    for(GrabbersContainer* container : enabled_containers)
    {
        container->running = false;
        clog << container->name + " [STOP]" << endl;
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


Supervisor::~Supervisor()
{
    DeleteVectorsElements(disabled_containers);
    DeleteVectorsElements(enabled_containers);
    DeleteVectorsElements(gathered_statistic);
    DeleteVectorsElements(savers);
}
