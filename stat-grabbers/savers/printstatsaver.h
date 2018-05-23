#ifndef PRINTSTATSAVER_H
#define PRINTSTATSAVER_H

#include "statsaver.h"
#include "algorithm"
#include <iostream>


class PrintStatSaver : public StatSaver
{
public:
    PrintStatSaver() {}
    virtual ~PrintStatSaver() {}
    void Save(const vector<shared_ptr<StatisticData>>&);
};

#endif // PRINTSTATSAVER_H
