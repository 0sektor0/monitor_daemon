#include "statgrabber.h"


StatGrabber::StatGrabber() : period(1), state(false)
{
    stat_files = vector<ifstream>();
    stat_data = vector<StatisticData>();
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


StatGrabber::~StatGrabber()
{

}
