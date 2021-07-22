
#include <libts3query/ts3query.hpp>
#include <iostream>
#include <string>

int main(int argc, char** args)
{
    if (argc < 2)
    {
        std::cout << "Wrong number of arguments provided." << std::endl;
        std::cout << "Usage: " << args[0] << " [host] [port = 10011] [serverid = 1]" << std::endl;
        exit(1);
    }

    std::string host = std::string(args[1]);
    uint16_t port = (argc >= 3 ? std::strtoul(args[2], NULL, 10) : 10011);
    int serverid = (argc >= 4 ? std::strtol(args[3], NULL, 10) : 1);

    auto server = ts3query::connection::TS3ServerConnection::telnet(host, port);
    server.connect();
    
    {
        auto command = ts3query::communication::TS3Command("use");
        command.addParameter("sid", serverid);
        auto response = server.exec(command);

        if (response.code() != 0)
        {
            std::cout << "Error selecting server " << serverid << ": " << response.message() << " [" << response.code()  << "]" << std::endl;
            server.disconnect();
            exit(1);
        }
    }

    {
        auto command = ts3query::communication::TS3Command("clientlist");
        command.addFlag("country");
        command.addFlag("uid");
        auto response = server.exec(command);

        if (response.code() != 0)
        {
            std::cout << "Error querying clientlist: " << response.message() << " [" << response.code()  << "]" << std::endl;
            server.disconnect();
            exit(1);
        }

        std::cout << "Received a total number of " << response.data().size() << " user as response" << std::endl;
        for (auto user : response.data())
        {
            std::cout
                << "Found user "
                << user.at("client_nickname").asString() << " ["
                << user.at("client_unique_identifier").asString() << "] from country "
                << user.at("client_country").asString()
                << std::endl;
        }
    }

    server.disconnect();
    exit(1);
}
