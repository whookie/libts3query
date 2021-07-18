#pragma once

#include "../base/TS3Object.hpp"
#include <string>
#include <sstream>
#include <list>


namespace ts3query::communication {

class TS3Command : public ts3query::base::TS3Object
{
// NOTE: NO idea why, but for some reason I had to explicitly declare the copy and move constructors
public:
    TS3Command(const TS3Command&);
    TS3Command(const TS3Command&&);
    TS3Command(const std::string& command);
    ~TS3Command() = default;

    void addParameter(const std::string& parameter, const std::string& value);
    void addParameter(const std::string& parameter, int value);
    void addFlag(const std::string& flag);
    void addPositional(const std::string& parameter);
    void addPositional(int parameter);
    void pipe();
    std::string to_string() const;
    
private:
    static std::string _escapeString(const std::string& s);

    std::stringstream m_commandBuilder;
    bool m_lastWasPipe{false};
};

}

