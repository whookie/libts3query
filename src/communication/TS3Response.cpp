
#include "TS3Response.hpp"
#include "../error/TS3LogicError.hpp"
#include <regex>


namespace ts3query::communication {

TS3Response::TS3Response(const std::string& s)
{
    m_raw = s;
    _parse(s);
}

const std::string&
TS3Response::raw() const { return m_raw; }

const std::vector<std::map<std::string, TS3ResponseValue>>&
TS3Response::data() const { return m_parsedData; }

const std::string&
TS3Response::message() const { return m_errorMessage; }

int
TS3Response::code() const { return m_errorCode; }

std::string TS3Response::_unescapeString(const std::string& s)
{
    if (s.length() == 0)
        return "";

    std::string buffer(s);
    buffer = std::regex_replace(buffer, std::regex(R"(\\\\)"), R"(\)" ); // \\ -> \\\\ must be replaced first, otherwise \\s will become \\\\s
    buffer = std::regex_replace(buffer, std::regex(R"(\\\/)"), R"(/)" );
    buffer = std::regex_replace(buffer, std::regex(R"(\\s)" ), R"( )" );
    buffer = std::regex_replace(buffer, std::regex(R"(\\p)" ), R"(|)" );
    buffer = std::regex_replace(buffer, std::regex(R"(\\a)" ), "\a"   );
    buffer = std::regex_replace(buffer, std::regex(R"(\\b)" ), "\b"   );
    buffer = std::regex_replace(buffer, std::regex(R"(\\b)" ), "\f"   );
    buffer = std::regex_replace(buffer, std::regex(R"(\\n)" ), "\n"   );
    buffer = std::regex_replace(buffer, std::regex(R"(\\r)" ), "\r"   );
    buffer = std::regex_replace(buffer, std::regex(R"(\\t)" ), "\t"   );
    buffer = std::regex_replace(buffer, std::regex(R"(\\v)" ), "\v"   );
    return buffer;
}

void TS3Response::_parse(const std::string& s)
{
    // https://regex101.com/r/Ys6IUj/1
    // Regex function to match "key=value"
    const std::regex parser(R"((?:([^\|\n\r\s=]+)(?:=([^\|\n\r\s]+))?(\s|\|)?))");

    std::string _s(s);
    std::smatch sm;
    
    std::map<std::string, TS3ResponseValue> parserMap;
    while (std::regex_search(_s, sm, parser))
    {
        std::string key = sm[1];
        std::string value = _unescapeString(sm[2]);

        parserMap.insert(std::pair<std::string, TS3ResponseValue>(key, TS3ResponseValue(value)));

        if (sm[3] == "|" || sm[3] == "\n" || sm[3] == "\r")
        {
            m_parsedData.insert(m_parsedData.end(), parserMap);
            parserMap = std::map<std::string, TS3ResponseValue>();
        }
        _s = sm.suffix().str();
    }

    // Remove last entry from the result buffer as that is the response status
    auto lastEntry = m_parsedData.back();
    m_errorCode = lastEntry.at("id").asInt();
    m_errorMessage = lastEntry.at("msg").asString();
    m_parsedData.pop_back();
}

}
