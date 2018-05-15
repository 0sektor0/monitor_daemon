#ifndef FSTATSAVER_H
#define FSTATSAVER_H

#include <string>
#include <vector>
#include <fstream>
#include <time.h>
#include <syslog.h>
#include <iostream>
#include "statsaver.h"
#include "stringutilities.h"
#include <boost/filesystem.hpp>

using namespace std;
using namespace StringUtilities;
namespace filesys = boost::filesystem;

#define DEF_MAX_WRITES 3600


class FStatSaver : public StatSaver
{
public:
    FStatSaver(const std::string&, const int&);
    virtual ~FStatSaver() {}
    void Save(const vector<StatisticData*>&);
    void SetMaxWrites(const int&);

private:
    int writes;
    int max_writes;
    std::string dir;
    std::string log_file;
    const std::string extension = ".log";

    std::string CreateFname(const StatisticData*);
    bool CheckIsDirectory(const std::string&);
    void CreateLogFile();
};

#endif // FSTATSAVER_H
