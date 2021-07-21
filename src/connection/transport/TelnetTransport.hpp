#pragma once

#include "TS3BaseTransport.hpp"


namespace ts3query::connection::transport {

class TelnetTransport : public ts3query::connection::transport::TS3BaseTransport
{
public:
    using TS3BaseTransport::TS3BaseTransport;
    ~TelnetTransport();

    auto writeString(const std::string&) -> void;
    auto readUntil(char c, bool blocking = true) -> std::string;

    auto start() -> void override;
    auto stop() -> void override;

private:
    int m_socket = -1;
};

}
