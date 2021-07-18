#pragma once

#include "TS3Error.hpp"


namespace ts3query::error {

class TS3TransportError : public TS3Error
{
public:
    TS3TransportError(int socketErrorCode);
    TS3TransportError(int socketErrorCode, const char* file, int line);
    TS3TransportError(const std::string& message);

private:
    int m_socketError;
};

}
