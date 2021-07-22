#pragma once

#include "../../base/TS3Object.hpp"
#include <string>

namespace ts3query::connection::transport {

class TS3BaseTransport : public ts3query::base::TS3Object {
public:
    TS3BaseTransport(const std::string& host, uint16_t port);
    virtual ~TS3BaseTransport() = default;

    virtual auto writeString(const std::string&) -> void = 0;
    virtual auto readUntil(char c, bool blocking = true) -> std::string = 0;

    virtual auto start() -> void;
    virtual auto stop() -> void;

    virtual auto isStarted() const -> bool;

protected:
    std::string m_host      { "127.0.0.1" };
    uint16_t m_port         { 10011 };

private:
    bool m_isStarted = false;
};

}
