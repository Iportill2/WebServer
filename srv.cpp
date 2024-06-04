#include "dependences.hpp"

srv::srv(std::string serverBlock)
{
    //std::cout << "Default srv Constructor" << std::endl;
    parseServerBlock(serverBlock) ;
}
srv::~srv()
{
    //std::cout << "srv Destructor" << std::endl;
}


std::vector<Location> &  srv::getlocations()
{
    return(array_of_location);
}
void srv::parseServerBlock(const std::string& serverBlock) 
{
    size_t pos;

    // Find and extract host
    pos = serverBlock.find("listen");
    if (pos != std::string::npos) 
    {
        pos += 7; // Skip "listen "
        size_t endPos = serverBlock.find(':', pos);
        _host = serverBlock.substr(pos, endPos - pos);
        pos = endPos + 1; // Skip ":"
        endPos = serverBlock.find(';', pos);
        _port = serverBlock.substr(pos, endPos - pos);
    }

    // Find and extract server_name
    pos = serverBlock.find("server_name");
    if (pos != std::string::npos) 
    {
        pos += 12; // Skip "server_name "
        size_t endPos = serverBlock.find(';', pos);
        _server_name = serverBlock.substr(pos, endPos - pos);
    }

    // Find and extract body_size
    pos = serverBlock.find("body_size");
    if (pos != std::string::npos)
    {
        pos += 10; // Skip "body_size "
        size_t endPos = serverBlock.find(';', pos);
        _body = serverBlock.substr(pos, endPos - pos);
    }

    // Find and extract root
    pos = serverBlock.find("root");
    if (pos != std::string::npos) 
    {
        pos += 5; // Skip "root "
        size_t endPos = serverBlock.find(';', pos);
        _root = serverBlock.substr(pos, endPos - pos);
    }

        // Find and extract location

    pos = serverBlock.find("location");
    while (pos < serverBlock.size()) 
    {
        pos += 9; // Skip "location "
        size_t endPos = serverBlock.find('}', pos);
        if (endPos != std::string::npos) 
        {
            std::string locationBlock = serverBlock.substr(pos, endPos - pos);
            pos = endPos + 1; // Skip "}"
            Location newLocation(locationBlock);
            array_of_location.push_back(newLocation);
        }
        else 
        {
        // Handle error: '}' not found
        //std::cerr << RED << "} Not found" << WHITE << std::endl;
        break;
        }
    }
}
/*
    pos = serverBlock.find("location");
    while (pos != std::string::npos) 
        pos += (endPos - pos);
    {
        pos += 9; // Skip "root "
        size_t endPos = serverBlock.find('}', pos);
        std::string locationBlock = serverBlock.substr(pos, endPos - pos);
        //std::cout << MAGENTA << locationBlock << WHITE << std::endl;
    }
*/