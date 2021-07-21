#pragma once

#include <gtest/gtest.h>
#include <memory>
#include "../../src/connection/TS3ServerConnection.hpp"
#include "../../src/error/TS3LogicError.hpp"
#include "transport/TransportMock.hpp"

using ::testing::Return;

TEST(TS3ServerConnection, error_execBeforeConnect)
{
    auto transport = std::unique_ptr<TransportMock>(new TransportMock("", 0, "", ""));
    auto transportMock = transport.get();
    auto server = ts3query::connection::TS3ServerConnection(std::move(transport));
    
    EXPECT_CALL(*transportMock, isStarted()).WillOnce(Return(false));
    EXPECT_THROW(server.exec(ts3query::communication::TS3Command("clientlist")), ts3query::error::TS3LogicError);
}

TEST(TS3ServerConnection, success_execAfterConnect)
{
    auto transport = std::unique_ptr<TransportMock>(new TransportMock("", 0, "", ""));
    auto transportMock = transport.get();
    auto server = ts3query::connection::TS3ServerConnection(std::move(transport));

    EXPECT_CALL(*transportMock, start()).WillOnce(Return());
    EXPECT_CALL(*transportMock, isStarted()).WillOnce(Return(true));
    EXPECT_CALL(*transportMock, writeString(testing::_)).WillOnce(Return());
    EXPECT_CALL(*transportMock, readUntil(testing::_, testing::_))
        .WillOnce(Return("hello\n\r"))
        .WillOnce(Return("Message\n\r"))
        .WillOnce(Return("test=0|test=1\n\r"))
        .WillOnce(Return("error id=0 msg=ok\n\r"));

    server.connect();
    auto response = server.exec(TS3Command("clientlist"));
    EXPECT_EQ(response.code(), 0);
    EXPECT_EQ(response.message(), "ok");
    EXPECT_EQ(response.data().size(), 2);
}
