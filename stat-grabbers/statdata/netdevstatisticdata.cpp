#include "netdevstatisticdata.h"



NetDevStatisticData::NetDevStatisticData(const NetDevInfo& info)
{
    name = info.interface + "_statistic";

    data["errs_recived"] = StringUtilities::ToString(info.errs_recived);
    data["bytes_recived"] = StringUtilities::ToString(info.bytes_recived);
    data["packets_recived"] = StringUtilities::ToString(info.packets_recived);
    data["errs_sended"] = StringUtilities::ToString(info.errs_sended);
    data["bytes_sended"] = StringUtilities::ToString(info.bytes_sended);
    data["packets_sended"] = StringUtilities::ToString(info.packets_sended);
}


std::string NetDevStatisticData::ToString()
{
    string res = name+"\n" + StringUtilities::ToString(date)+"\n";

    for(map<string, string>::iterator it = data.begin(); it != data.end(); ++it)
        res += it->first + ": " + it->second + "\n";

    return res;
}



NetDevInfo::NetDevInfo()
{
    interface = "";
    errs_recived = 0;
    bytes_recived = 0;
    packets_recived = 0;
    errs_sended = 0;
    bytes_sended = 0;
    packets_sended = 0;
}


NetDevInfo::NetDevInfo(const std::string& str)
{
    vector<string> values = StringUtilities::Split(str, ' ');

    if(values.size() == VALUES_SIZE)
    {
        interface = values[INTERFACE_INDEX];
        errs_recived = StringUtilities::Stoui(values[ERRS_RECIVED_INDEX]);
        bytes_recived = StringUtilities::Stoui(values[BYTES_RECIVED_INDEX]);
        packets_recived = StringUtilities::Stoui(values[PACKETS_RECIVED_INDEX]);
        errs_sended = StringUtilities::Stoui(values[ERRS_SENDED_INDEX]);
        bytes_sended = StringUtilities::Stoui(values[BYTES_SENDED_INDEX]);
        packets_sended = StringUtilities::Stoui(values[PACKETS_SENDED_INDEX]);
    }
    else
    {
        std::string message = "Wrong netdev string format: " + str;
        syslog(LOG_ERR, message.c_str());
        throw std::runtime_error(message);
    }
}


NetDevInfo NetDevInfo::operator -(const NetDevInfo& subtrahend)
{
    NetDevInfo result;

    result.interface = interface;
    result.errs_recived = this->errs_recived - subtrahend.errs_recived;
    result.errs_sended= this->errs_sended - subtrahend.errs_sended;
    result.bytes_recived = this->bytes_recived - subtrahend.bytes_recived;
    result.bytes_sended = this->bytes_sended - subtrahend.bytes_sended;
    result.packets_recived = this->packets_recived - subtrahend.packets_recived;
    result.packets_sended = this->packets_sended - subtrahend.packets_sended;

    return result;
}
