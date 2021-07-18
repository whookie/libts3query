
#include "TS3Command.hpp"
#include <regex>

namespace ts3query::communication {

TS3Command::TS3Command(const std::string& command)
    : ts3query::base::TS3Object()
{
    m_commandBuilder << command;
}

void TS3Command::addParameter(const std::string& parameter, const std::string& value)
{
    m_commandBuilder << (m_lastWasPipe ? "" : " ") << parameter << "=" << _escapeString(value);
    m_lastWasPipe = false;
}

void TS3Command::addParameter(const std::string& parameter, int value)
{
    m_commandBuilder << (m_lastWasPipe ? "" : " ") << parameter << "=" << std::to_string(value);
    m_lastWasPipe = false;
}

void TS3Command::addFlag(const std::string& flag)
{
    m_commandBuilder << (m_lastWasPipe ? "" : " ") << "-" << flag;
    m_lastWasPipe = false;
}

void TS3Command::addPositional(const std::string& parameter)
{
    m_commandBuilder << (m_lastWasPipe ? "" : " ") << _escapeString(parameter);
}

void TS3Command::addPositional(int value)
{
    m_commandBuilder << (m_lastWasPipe ? "" : " ") << std::to_string(value);
}

void TS3Command::pipe()
{
    m_commandBuilder << "|";
    m_lastWasPipe = true;
}

std::string TS3Command::to_string() const
{
    return m_commandBuilder.str();
}

std::string TS3Command::_escapeString(const std::string& s)
{
    std::string buffer(s);
    buffer = std::regex_replace(buffer, std::regex(R"(\\)"  ), R"(\\)" ); // \\ -> \\\\ must be replaced first, otherwise \\s will become \\\\s
    buffer = std::regex_replace(buffer, std::regex(R"(\/)"  ), R"(\/)" );
    buffer = std::regex_replace(buffer, std::regex(R"( )"   ), R"(\s)" );
    buffer = std::regex_replace(buffer, std::regex(R"(\|)"  ), R"(\p)" );
    buffer = std::regex_replace(buffer, std::regex(R"(\x07)"), R"(\a)" );
    buffer = std::regex_replace(buffer, std::regex(R"(\x08)"), R"(\b)" );
    buffer = std::regex_replace(buffer, std::regex(R"(\x0C)"), R"(\f)" );
    buffer = std::regex_replace(buffer, std::regex(R"(\x0A)"), R"(\n)" );
    buffer = std::regex_replace(buffer, std::regex(R"(\x0D)"), R"(\r)" );
    buffer = std::regex_replace(buffer, std::regex(R"(\x09)"), R"(\t)" );
    buffer = std::regex_replace(buffer, std::regex(R"(\x0B)"), R"(\v)" );
    return buffer;
}

}
