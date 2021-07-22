#pragma once

#include "../base/TS3Object.hpp"
#include "../communication/TS3Command.hpp"
#include "../communication/TS3Response.hpp"
#include "transport/TS3BaseTransport.hpp"

#include <memory>
#include <string>
#include <stdint.h>

namespace ts3query::connection
{

class TS3ServerConnection : public ts3query::base::TS3Object
{
public:
    TS3ServerConnection(std::unique_ptr<transport::TS3BaseTransport> transport);
    TS3ServerConnection(const TS3ServerConnection&);
    ~TS3ServerConnection() = default;

    // Connect
    void connect();
    void disconnect();
    
    // Execute
    ts3query::communication::TS3Response
    exec(const ts3query::communication::TS3Command& command);

    // Additional factory methods
    static TS3ServerConnection telnet(const std::string& host, uint16_t port);

private:
    std::unique_ptr<transport::TS3BaseTransport> m_transport = nullptr;

    std::string m_host      { "127.0.0.1" };
    std::string m_user      { "serveradmin" };
    std::string m_passwd    { "" };
    uint16_t    m_port      { 10011 };
};

} // namespace ts3query::connection

