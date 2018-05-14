#ifndef FSTATSAVER_H
#define FSTATSAVER_H

#include <string>
#include <vector>
#include <fstream>
#include <syslog.h>
#include <iostream>
#include "statsaver.h"
#include "stringutilities.h"
#include <boost/filesystem.hpp>

using namespace std;
using namespace StringUtilities;
namespace filesys = boost::filesystem;


class FStatSaver : public StatSaver
{
public:
    FStatSaver(const std::string&);
    virtual ~FStatSaver() {}
    void Save(const vector<StatisticData*>&);

private:
    std::string dir;
    const std::string extension = ".log";

    std::string CreateFname(const StatisticData*);
    bool CheckIsDirectory(const std::string&);
};

#endif // FSTATSAVER_H