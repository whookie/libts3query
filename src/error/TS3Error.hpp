#pragma once

#include <exception>
#include <string>


namespace ts3query::error {

class TS3Error : public std::exception
{
public:
    TS3Error();
    TS3Error(const std::string& message);
    virtual const char* what() const throw ();

    virtual const std::string& message() const;

protected:
    std::string m_message;
};

}
