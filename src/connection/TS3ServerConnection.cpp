
#include "TS3ServerConnection.hpp"
#include "transport/TelnetTransport.hpp"
#include "../error/TS3LogicError.hpp"

namespace ts3query::connection {


TS3ServerConnection::TS3ServerConnection(std::unique_ptr<transport::TS3BaseTransport> transport)
    : ts3query::base::TS3Object() {
        m_transport = std::move(transport);
}


void TS3ServerConnection::connect()
{
    m_transport->start();

    // Swallow the welcome message
    m_transport->readUntil('\r');
    m_transport->readUntil('\r');
}


void TS3ServerConnection::disconnect()
{
    m_transport->stop();
}


ts3query::communication::TS3Response
TS3ServerConnection::exec(const ts3query::communication::TS3Command& command) {
    if (! m_transport->isStarted())
        throw ts3query::error::TS3LogicError("Attempted to use a command while not connected");
    
    m_transport->writeString(command.to_string() + "\n\r");
    
    std::stringstream ss;
    ss << m_transport->readUntil('\r') << m_transport->readUntil('\r', false);

    return ts3query::communication::TS3Response(ss.str());
}


TS3ServerConnection
TS3ServerConnection::telnet(const std::string& host, uint16_t port)
{
    auto transport = new ts3query::connection::transport::TelnetTransport(host, port);
    auto transport_ptr = std::unique_ptr<ts3query::connection::transport::TelnetTransport>(transport);
    return TS3ServerConnection(std::move(transport_ptr));
}

}
