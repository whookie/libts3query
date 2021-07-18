
#include <gtest/gtest.h>
#include "../../../src/connection/transport/NetworkTools.hpp"


TEST(NetworkTools, getIpAddress_usingDomain)
{
    std::vector<in_addr_t> addrs = ts3query::connection::transport::networktools::getIpAddress("dns.google.com");
    EXPECT_TRUE(addrs.at(0) == 0x08080808 || addrs.at(0) == 0x04040808);
    EXPECT_TRUE(addrs.at(1) == 0x08080808 || addrs.at(1) == 0x04040808);
}

TEST(NetworkTools, getIpAddress_usingIP) {
    std::vector<in_addr_t> addrs = ts3query::connection::transport::networktools::getIpAddress("1.1.1.1");
    EXPECT_EQ(addrs.at(0), 0x01010101);
}
