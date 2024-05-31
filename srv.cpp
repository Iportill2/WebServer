#include "dependences.hpp"

srv::srv(std::string serverBlock)
{
    std::cout << "Default srv Constructor" << std::endl;
}
srv::~srv()
{
    std::cout << "srv Destructor" << std::endl;
}

void parseServerBlock(const std::string& serverBlock, std::string& _host, std::string& _port, std::string& _server_name, std::string& _body_size, std::string& _root) {
    size_t pos;

    // Find and extract host
    pos = serverBlock.find("listen");
    if (pos != std::string::npos) {
        pos += 7; // Skip "listen "
        size_t endPos = serverBlock.find(':', pos);
        _host = serverBlock.substr(pos, endPos - pos);
        pos = endPos + 1; // Skip ":"
        endPos = serverBlock.find(';', pos);
        _port = serverBlock.substr(pos, endPos - pos);
    }

    // Find and extract server_name
    pos = serverBlock.find("server_name");
    if (pos != std::string::npos) {
        pos += 12; // Skip "server_name "
        size_t endPos = serverBlock.find(';', pos);
        _server_name = serverBlock.substr(pos, endPos - pos);
    }

    // Find and extract body_size
    pos = serverBlock.find("body_size");
    if (pos != std::string::npos) {
        pos += 10; // Skip "body_size "
        size_t endPos = serverBlock.find(';', pos);
        _body_size = serverBlock.substr(pos, endPos - pos);
    }

    // Find and extract root
    pos = serverBlock.find("root");
    if (pos != std::string::npos) {
        pos += 5; // Skip "root "
        size_t endPos = serverBlock.find(';', pos);
        _root = serverBlock.substr(pos, endPos - pos);
    }
}
//parse server date, server name body etc...
void srv::instanceLocations()
{

}
//instaciar locations...