
#include "TS3BaseTransport.hpp"


namespace ts3query::connection::transport {

TS3BaseTransport::TS3BaseTransport(const std::string& host, uint16_t port)
    : m_host(host), m_port(port) {}

bool
TS3BaseTransport::isStarted() const
{
    return m_isStarted;
}

void
TS3BaseTransport::start()
{
    m_isStarted = true;
}

void
TS3BaseTransport::stop()
{
    m_isStarted = false;
}

}
