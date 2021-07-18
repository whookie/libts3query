
#include <gtest/gtest.h>
#include "../../src/communication/TS3Command.hpp"

TEST(TS3Command, addParameters) {
    ts3query::communication::TS3Command command("clientinfo");
    command.addParameter("clid", 1);
    command.addParameter("cid", "64");
    EXPECT_EQ(command.to_string(), "clientinfo clid=1 cid=64");
}

TEST(TS3Command, addFlags) {
    ts3query::communication::TS3Command command("clientlist");
    command.addFlag("country");
    command.addFlag("ids");
    EXPECT_EQ(command.to_string(), "clientlist -country -ids");
}

TEST(TS3Command, addPipe) {
    ts3query::communication::TS3Command command("clientinfo");
    command.addParameter("clid", 4);
    command.pipe();
    command.addParameter("clid", 5);
    EXPECT_EQ(command.to_string(), "clientinfo clid=4|clid=5");
}

TEST(TS3Command, addParamtersWithEscape) {
    ts3query::communication::TS3Command command("serveredit");
    command.addParameter("virtualserver_name", "TeamSpeak ]|[ Server");
    EXPECT_EQ(command.to_string(), "serveredit virtualserver_name=TeamSpeak\\s]\\p[\\sServer");
}

TEST(TS3Command, addParametersWithBackslashEscape) {
    ts3query::communication::TS3Command command("serveredit");
    command.addParameter("virtualserver_name", "TeamSpeak\\Server\n");
    EXPECT_EQ(command.to_string(), "serveredit virtualserver_name=TeamSpeak\\\\Server\\n");
}

TEST(TS3Command, addPositionalString) {
    ts3query::communication::TS3Command command("login");
    command.addPositional("serveradmin");
    command.addPositional("abc123");
    EXPECT_EQ(command.to_string(), "login serveradmin abc123");
}

TEST(TS3Command, addPositionalInt) {
    ts3query::communication::TS3Command command("use");
    command.addPositional(1);
}
