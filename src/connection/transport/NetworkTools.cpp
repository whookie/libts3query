#include "NetworkTools.hpp"
#include <memory.h>

namespace ts3query::connection::transport::networktools {

std::vector<in_addr_t> getIpAddress(const std::string& host)
{
    std::vector<in_addr_t> addresslist;
    struct addrinfo* result;
    struct addrinfo hints;
    
    memset(&hints, 0, sizeof(hints));
    hints = {
        .ai_family = AF_INET,
        .ai_socktype = SOCK_STREAM,
        .ai_protocol = 0,
        .ai_addr = NULL,
        .ai_canonname = NULL,
        .ai_next = NULL
    };

    if (getaddrinfo(host.c_str(), NULL, &hints, &result) == 0)
    {
        for (struct addrinfo* addr = result; addr != NULL; addr = addr->ai_next)
        {
            in_addr_t ipv4 = ((struct sockaddr_in*)addr->ai_addr)->sin_addr.s_addr;
            addresslist.push_back(ipv4);
        }

        freeaddrinfo(result);
    }

    return addresslist;
}

}
