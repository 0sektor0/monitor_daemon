#ifndef FSTATGRABBER_H
#define FSTATGRABBER_H

#include "statgrabber.h"


class FStatGrabber : public StatGrabber
{
public:
    FStatGrabber();
    ~FStatGrabber();

protected:
    vector<std::ifstream> stat_files;
};

#endif // FSTATGRABBER_H
