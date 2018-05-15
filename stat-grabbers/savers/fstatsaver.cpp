#include "fstatsaver.h"



FStatSaver::FStatSaver(const std::string& dir, const int& max_writes)
{
    if (!CheckIsDirectory(dir))
    {
        std::string mes = dir + " is not a directory or dosent exist.";
        syslog (LOG_ERR, mes.c_str());
        exit(1);
    }

    if(dir[dir.length()-1]!='/')
        this->dir = dir + "/";
    else
        this->dir = dir;

    CreateLogFile();
    SetMaxWrites(max_writes);
}


void FStatSaver::Save(const vector<StatisticData*>& st)
{
    if (st.size())
    {
        if(writes >= max_writes)
            CreateLogFile();

        vector<StatisticData*> data = vector<StatisticData*>(st);
        sort(data.begin(), data.end());

        ofstream fout(log_file, ios_base::app);
        if (fout.is_open())
        {
          for(int i = 0; i < data.size(); i++)
            fout << data[i]->ToString() << endl;
          fout.close();
        }
        else
            syslog (LOG_ERR, "FStatSaver Unable to open file.");

        writes++;
    }
}


bool FStatSaver::CheckIsDirectory(const std::string& path)
{
    try
    {
        filesys::path pathObj(path);
        if (filesys::exists(pathObj) && filesys::is_directory(pathObj))
            return true;
    }
    catch (filesys::filesystem_error & e)
    {
        syslog (LOG_ERR, e.what());
    }

    return false;
}


void FStatSaver::CreateLogFile()
{
    time_t date;
    time(&date);
    log_file = dir + StringUtilities::ToString(date) + extension;
    writes = 0;
}


void FStatSaver::SetMaxWrites(const int& max_writes)
{
    this->max_writes = max_writes > 0 ? max_writes : DEF_MAX_WRITES;
}
