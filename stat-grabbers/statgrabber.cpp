#include "statgrabber.h"


StatGrabber::StatGrabber() : period(1), state(false)
{
    stat_files = vector<std::ifstream>();
    stat_data = vector<StatisticData*>();
}


bool StatGrabber::GetStatistic(vector<StatisticData*>& dest)
{
    if (stat_data.empty())
        return 0;

    dest = move(stat_data);
    return 1;
}


void StatGrabber::Start()
{
    if(!state)
    {
        state = true;

        while(true)
        {
            Parse();
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
    for (i = stat_data.begin(); i < stat_data.end(); ++i)
        delete *i;
}
