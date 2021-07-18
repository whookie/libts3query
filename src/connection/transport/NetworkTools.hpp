#pragma once

#include <string>
#include <vector>

#include <sys/socket.h>
#include <netdb.h>


namespace ts3query::connection::transport::networktools {

std::vector<in_addr_t> getIpAddress(const std::string& host);

}
