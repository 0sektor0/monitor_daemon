#include "statgrabber.h"


StatGrabber::StatGrabber() : period(1), state(false)
{
    stat_data = vector<StatisticData*>();
}


vector<StatisticData*> StatGrabber::GetStatistic()
{
    if (stat_data.empty())
        throw std::runtime_error("stat-grabber is empty");

    vector<StatisticData*> dest;
    dest = move(stat_data);
    return dest;
}


bool StatGrabber::IsEmpty()
{
    return stat_data.empty();
}


void StatGrabber::Start()
{
    if(!state)
    {
        state = true;

        while(true)
        {
            Grab();
            sleep(period);
        }
    }
}


void StatGrabber::Stop()
{
    state = false;
}


void StatGrabber::SetPeriod(const int& new_period)
{
    period = new_period;
}


const bool& StatGrabber::GetState()
{
    return state;
}


int StatGrabber::GetStatisticNum()
{
    return stat_data.size();
}


StatGrabber::~StatGrabber()
{
    vector<StatisticData*>::iterator i;
    for (i = stat_data.begin(); i < stat_data.end(); i++)
        delete *i;
}
