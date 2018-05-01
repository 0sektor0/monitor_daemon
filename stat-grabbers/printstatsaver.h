#ifndef PRINTSTATSAVER_H
#define PRINTSTATSAVER_H

#include "statsaver.h"
#include <iostream>


class PrintStatSaver : public StatSaver
{
public:
    PrintStatSaver() {}
    ~PrintStatSaver() {}
    void Save(const vector<StatisticData*>&);

};

#endif // PRINTSTATSAVER_H
