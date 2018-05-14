#include "fstatsaver.h"



FStatSaver::FStatSaver(const std::string& dir)
{
    if (!CheckIsDirectory(dir))
    {
        cerr << "given path is not a directory or dosent exist\n";
        exit(-1);
    }

    if(dir[dir.length()-1]!='/')
        this->dir = dir + "/";
    else
        this->dir = dir;

}


void FStatSaver::Save(const vector<StatisticData*>& st)
{
    if (st.size())
    {
        vector<StatisticData*> data = vector<StatisticData*>(st);
        sort(data.begin(), data.end());

        std::string fn = dir+StringUtilities::ToString(data[0]->date)+extension;
        ofstream stfile(fn);

        if (stfile.is_open())
        {
          for(int i = 0; i < data.size(); i++)
            stfile << data[i]->ToString() << endl;
          stfile.close();
        }
        else
            cerr << "Unable to open file\n";
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
        cerr << e.what() << std::endl;
    }

    return false;
}