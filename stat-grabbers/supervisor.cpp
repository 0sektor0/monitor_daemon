#include "supervisor.h"



Supervisor::Supervisor()
{
    GrabbersContainer* grubc = new GrabbersContainer();
    grubc->name = "md";
    grubc->grabbers.push_back(new MemStatGrabber());
    grubc->grabbers.push_back(new DiskStatGrabber());

    enabled_containers.push_back(grubc);

    period = 2000;
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

        cout << "container " + container->name + " processed" << endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(container->period));
    }
}


void Supervisor::Start()
{
    for(int i = 0; i < enabled_containers.size(); i++)
    {
        try
        {
            std::thread th([=] { RunContainer(enabled_containers[i]); });
            th.detach();
            cout << enabled_containers[i]->name + " [OK]" << endl;
        }
        catch(int e)
        {
            cout << enabled_containers[i]->name + " [FAIL]" << endl;
        }
    }

    std::thread th([=] { GrabStatistic(); });
    th.detach();
}


void Supervisor::Stop()
{
    for(int i = 0; i < enabled_containers.size(); i++)
    {
        enabled_containers[i]->running = false;
        cout << enabled_containers[i]->name + " [STOP]" << endl;
    }
}


void Supervisor::Save()
{
    for(int i = 0; i < gathered_statistic.size(); i++)
    {
        cout << gathered_statistic[i]->ToString() << endl;
        delete gathered_statistic[i];
    }

    gathered_statistic = vector<StatisticData*>();
}


void Supervisor::GrabStatistic()
{
    for(;;)
    {
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

        cout << "statistic grabbed: " + gathered_statistic.size() << endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(period));
    }
}


Supervisor::~Supervisor()
{
    for(int i = 0; i < enabled_containers.size(); i++)
        delete enabled_containers[i];

    for(int i = 0; i < disabled_containers.size(); i++)
        delete disabled_containers[i];

    for(int i = 0; i < gathered_statistic.size(); i++)
        delete gathered_statistic[i];
}
