#pragma once

#include "../../src/communication/TS3Response.hpp"
#include <gtest/gtest.h>

using namespace ts3query::communication;


TEST(TS3Response, parseCorrectly_withoutData)
{
    TS3Response response("error id=1024 msg=invalid\\sserverID\n\r");
    EXPECT_EQ(response.code(), 1024);
    EXPECT_EQ(response.message(), "invalid serverID");
    EXPECT_EQ(response.data().size(), 0);
}

TEST(TS3Response, parseCorrectly_withData)
{
    TS3Response response("virtualserver_status=unknown virtualserver_port=0 virtualserver_id=0 client_id=0 client_channel_id=0 client_nickname client_database_id=0 client_login_name client_origin_server_id=0\n\rerror id=0 msg=ok\n\r");
    EXPECT_EQ(response.code(), 0);
    EXPECT_EQ(response.message(), "ok");
    EXPECT_EQ(response.data().size(), 1);
    
    EXPECT_EQ(response.data().at(0).at("virtualserver_status").asString(), "unknown");
    EXPECT_EQ(response.data().at(0).at("virtualserver_port").asInt(), 0);
    EXPECT_EQ(response.data().at(0).at("virtualserver_id").asInt(), 0);
    EXPECT_EQ(response.data().at(0).at("client_id").asInt(), 0);
    EXPECT_EQ(response.data().at(0).at("client_channel_id").asInt(), 0);
    EXPECT_EQ(response.data().at(0).at("client_nickname").asString(), "");
    EXPECT_EQ(response.data().at(0).at("client_database_id").asInt(), 0);
    EXPECT_EQ(response.data().at(0).at("client_login_name").asString(), "");
    EXPECT_EQ(response.data().at(0).at("client_origin_server_id").asInt(), 0);
}

TEST(TS3Response, parseCorrectly_withDataArray)
{
    TS3Response response("clid=14768 cid=12 client_database_id=5 client_type=1 client_nickname|clid=14751 cid=26 client_database_id=1030 client_nickname=Saltfarm\\sFacility client_type=0|clid=14570 cid=26 client_database_id=4 client_nickname=Whookie client_type=0|clid=14529 cid=4 client_database_id=143 client_nickname=you\\slot\\sare\\sshit client_type=0|clid=9937 cid=51 client_database_id=1304 client_nickname=rikard03 client_type=0\n\rerror id=0 msg=ok\n\r");
    EXPECT_EQ(response.code(), 0);
    EXPECT_EQ(response.message(), "ok");
    EXPECT_EQ(response.data().size(), 5);

    EXPECT_EQ(response.data().at(0).at("clid").asInt(), 14768);
    EXPECT_EQ(response.data().at(0).at("client_type").asInt(), 1);
    EXPECT_EQ(response.data().at(0).at("client_nickname").asString(), "");
    EXPECT_EQ(response.data().at(1).at("clid").asInt(), 14751);
    EXPECT_EQ(response.data().at(1).at("client_nickname").asString(), "Saltfarm Facility");
}