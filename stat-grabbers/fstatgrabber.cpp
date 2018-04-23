#include "fstatgrabber.h"


FStatGrabber::FStatGrabber() : StatGrabber()
{
    stat_files = vector<std::ifstream>();
}


FStatGrabber::~FStatGrabber()
{
    for (int i = 0; i < stat_files.size(); i++)
        stat_files[i].close();
}
