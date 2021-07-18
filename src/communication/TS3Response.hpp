#pragma once

#include "../base/TS3Object.hpp"
#include "TS3ResponseValue.hpp"

#include <string>
#include <vector>
#include <map>


namespace ts3query::communication {

class TS3Response : ts3query::base::TS3Object
{
public:
    TS3Response(const std::string& s);

    auto raw() const -> const std::string&;
    auto data() const -> const std::vector<std::map<std::string, TS3ResponseValue>>&;
    auto code() const -> int;
    auto message() const -> const std::string&;

private:
    void _parse(const std::string& s);
    std::string _unescapeString(const std::string& s);

    std::string m_raw;
    std::vector<std::map<std::string, TS3ResponseValue>> m_parsedData;
    int m_errorCode;
    std::string m_errorMessage;
};

}
