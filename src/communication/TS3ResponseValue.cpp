
#include "TS3ResponseValue.hpp"
#include <stdexcept>


namespace ts3query::communication {

TS3ResponseValue::TS3ResponseValue(const std::string& s)
    : ts3query::base::TS3Object(), m_value(s) {}


std::string TS3ResponseValue::asString() const {
    return m_value;
}

int TS3ResponseValue::asInt() const {
    return std::stoi(m_value);
}

bool TS3ResponseValue::asBool() const {
    return ((isInt() && asInt() != 0) || (! isInt() && m_value.length() > 0));
}

bool TS3ResponseValue::isInt() const {
    try {
        std::stoi(m_value);
        return true;
    }
    catch (std::invalid_argument) { return false; }
}

}
