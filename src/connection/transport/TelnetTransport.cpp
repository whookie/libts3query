
#include "TelnetTransport.hpp"
#include "NetworkTools.hpp"
#include "../../error/TS3TransportError.hpp"

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <sstream>

namespace ts3query::connection::transport {

void TelnetTransport::start()
{
    if (isStarted())
        throw ts3query::error::TS3TransportError("Socket still active");

    m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (m_socket < 0)
        throw ts3query::error::TS3TransportError(errno, __FILE__, __LINE__);
    
    std::vector<in_addr_t> addresses = networktools::getIpAddress(m_host);
    if (addresses.size() == 0)
        throw ts3query::error::TS3TransportError("Unable to find IP address associated with domain");

    struct sockaddr_in sa;
    sa.sin_addr.s_addr = addresses.at(0);
    sa.sin_port = htons(m_port);
    sa.sin_family = AF_INET;

    if (connect(m_socket, (struct sockaddr*)&sa, sizeof(sa)) < 0)
        throw ts3query::error::TS3TransportError(errno, __FILE__, __LINE__);
    
    TS3BaseTransport::start();
}


void TelnetTransport::stop()
{
    TS3BaseTransport::stop();
    close(m_socket);
}

void TelnetTransport::writeString(const std::string& s)
{
    send(m_socket, s.c_str(), s.length(), 0);
}

std::string TelnetTransport::readUntil(char c, bool blocking)
{
    std::stringstream ss;

    int recv_flags = blocking ? 0 : MSG_DONTWAIT;

    char buffer;
    do {
        int errc = recv(m_socket, &buffer, 1, recv_flags);

        if (errc == -1 && errno == EWOULDBLOCK)
            break;
        else if (errc == -1 && errno != EWOULDBLOCK)
            throw ts3query::error::TS3TransportError(errno, __FILE__, __LINE__);

        ss << buffer;
    } while (buffer != c);

    return ss.str();
}

}
