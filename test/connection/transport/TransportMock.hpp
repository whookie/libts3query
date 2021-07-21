#pragma once

#include <gmock/gmock.h>
#include "../../../src/connection/transport/TS3BaseTransport.hpp"


class TransportMock : public ts3query::connection::transport::TS3BaseTransport
{
public:
    using TS3BaseTransport::TS3BaseTransport;

    MOCK_METHOD(void,           writeString,    (const std::string&), (override));
    MOCK_METHOD(std::string,    readUntil,      (char c, bool blocking), (override));
    MOCK_METHOD(void,           start,          (), (override));
    MOCK_METHOD(void,           stop,           (), (override));
    MOCK_METHOD(bool,           isStarted,      (), (const, override));
};
