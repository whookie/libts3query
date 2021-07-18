
#include "TS3ServerConnection.hpp"
#include "transport/TelnetTransport.hpp"
#include "../error/TS3LogicError.hpp"

namespace ts3query::connection {

TS3ServerConnection::TS3ServerConnection(
    const std::string& host,
    uint16_t port,
    const std::string& user,
    const std::string& passwd,
    std::unique_ptr<transport::TS3BaseTransport> transport
    ) : ts3query::base::TS3Object()
{
    m_host = host;
    m_port = port;
    m_user = user;
    m_passwd = passwd;
    m_transport = std::move(transport);
}

std::unique_ptr<TS3ServerConnection> TS3ServerConnection::telnet(const std::string& host, uint16_t port)
{
    transport::TS3BaseTransport* transportMethod = new transport::TelnetTransport(host, port);
    std::unique_ptr<transport::TS3BaseTransport> transportPtr(transportMethod);
    TS3ServerConnection* serverConnection = new TS3ServerConnection(host, port, "", "", std::move(transportPtr));
    return std::unique_ptr<TS3ServerConnection>(serverConnection);
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

}
