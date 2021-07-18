
#include "TS3TransportError.hpp"
#include <string.h>
#include <sstream>


namespace ts3query::error {

TS3TransportError::TS3TransportError(int socketErrorCode)
    : TS3Error()
{
    m_socketError = socketErrorCode;
    m_message = std::string(strerror(socketErrorCode));
};

TS3TransportError::TS3TransportError(const std::string& message) {
    m_socketError = 0;
    m_message = message;
}

TS3TransportError::TS3TransportError(int socketErrorCode, const char* file, int line) {
    m_socketError = socketErrorCode;
    std::stringstream ss;
    ss << strerror(socketErrorCode) << " [" << file << " : " << line << "]";
    m_message = ss.str();
}

}
