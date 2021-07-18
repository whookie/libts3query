#pragma once

#include "../base/TS3Object.hpp"
#include <string>


namespace ts3query::communication {

class TS3ResponseValue : public ts3query::base::TS3Object
{
public:
    TS3ResponseValue(const std::string& s);

    auto asString() const -> std::string;
    auto asInt() const -> int;
    auto asBool() const -> bool;

    auto isInt() const -> bool;

private:
    const std::string m_value;
};

}
