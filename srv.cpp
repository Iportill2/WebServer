#include "dependences.hpp"
#include "srv.hpp"
#include "Config.hpp"
srv::srv(std::string serverBlock)
{
    //std::cout << "Default srv Constructor" << std::endl;
    nullstrings();
    parseServerBlock(serverBlock) ;
}
srv::~srv()
{
    //std::cout << "srv Destructor" << std::endl;
}

void srv::nullstrings()
{
    _host = "";
    _port = "";
    _server_name = "";
    _body = "";
    _root = "";

}
std::vector<Location> &  srv::getlocations()
{
    return(array_of_location);
}
void srv::parseServerBlock(const std::string& serverBlock) 
{
    size_t pos;
    std::string temp;
    // Find and extract host
/*     pos = serverBlock.find("listen");
    if (pos != std::string::npos) 
    {
        pos += std::string("listen").size();  // Skip "listen "
        size_t endPos = serverBlock.find(':', pos);
        _host = serverBlock.substr(pos, endPos - pos);
        pos = endPos + 1; // Skip ":"
        endPos = serverBlock.find(';', pos);
        _port = serverBlock.substr(pos, endPos - pos);
    } */

    pos = serverBlock.find("listen");
    while (pos != std::string::npos) 
    {
        pos += std::string("listen").size(); // Skip "server_name "
        size_t endPos = serverBlock.find(':', pos);
        temp = serverBlock.substr(pos, endPos - pos);
        if(_host == "")
            _host = temp;
        else
            std::cout << "ERROR al conseguir HOST valor ya inicializado" << std::endl;
        
        pos = serverBlock.find("listen", endPos);
    }

    pos = serverBlock.find(_host);
    while(pos)


    // Find and extract server_name
    pos = serverBlock.find("server_name");
    while (pos != std::string::npos) 
    {
        pos += std::string("server_name").size(); // Skip "server_name "
        size_t endPos = serverBlock.find(';', pos);
        temp = serverBlock.substr(pos, endPos - pos);
        if(_server_name == "")
            _server_name = temp;
        else
            std::cout << "ERROR al conseguir SERVER_NAME valor ya inicializado" << std::endl;

        // Update pos to start searching after the last occurrence of "server_name"
        pos = serverBlock.find("server_name", endPos);
    }

    pos = serverBlock.find("body_size");
    while (pos != std::string::npos) 
    {
        pos += std::string("body_size").size(); // Skip "server_name "
        size_t endPos = serverBlock.find(';', pos);
        temp = serverBlock.substr(pos, endPos - pos);
        if(_body == "")
            _body = temp;
        else
            std::cout << "ERROR al conseguir BODY_SIZE valor ya inicializado" << std::endl;

        // Update pos to start searching after the last occurrence of "server_name"
        pos = serverBlock.find("body_size", endPos);
    }


    // Find and extract root
    pos = serverBlock.find("root");
    while (pos != std::string::npos) 
    {
        pos += std::string("root").size(); // Skip "server_name "
        size_t endPos = serverBlock.find(';', pos);
        temp = serverBlock.substr(pos, endPos - pos);
        if(_root == "")
            _root = temp;
        else
            std::cout << "ERROR al conseguir ROOT valor ya inicializado" << std::endl;

        // Update pos to start searching after the last occurrence of "server_name"
        pos = serverBlock.find("root", endPos);
    }
        // Find and extract location
    pos = serverBlock.find("location");
    while (pos < serverBlock.size()) 
    {
        pos += std::string("location").size(); // Skip "location "
        size_t endPos = serverBlock.find('}', pos);
        if (endPos != std::string::npos) 
        {
            std::string locationBlock = serverBlock.substr(pos, endPos - pos);
            pos = endPos + 1; // Skip "}"
            Location newLocation(locationBlock);
            array_of_location.push_back(newLocation);
        }
        else 
            break;
    }
}
