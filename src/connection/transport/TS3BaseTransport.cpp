
#include "TS3BaseTransport.hpp"


namespace ts3query::connection::transport {

TS3BaseTransport::TS3BaseTransport(const std::string& host, uint16_t port, const std::string& user, const std::string& passwd)
    : m_host(host), m_port(port), m_user(user), m_passwd(passwd) {}

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
