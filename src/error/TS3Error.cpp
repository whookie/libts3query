#include "TS3Error.hpp"


namespace ts3query::error {

TS3Error::TS3Error(const std::string& message)
    : m_message(message) {};


TS3Error::TS3Error()
    : m_message("") {};


const char* TS3Error::what() const throw()
{
    return m_message.c_str();
}

const std::string& TS3Error::message() const
{
    return m_message;
}

}
