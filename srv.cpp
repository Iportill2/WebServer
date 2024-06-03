#include "dependences.hpp"

srv::srv(std::string serverBlock)
{
    std::cout << "Default srv Constructor" << std::endl;
    parseServerBlock(serverBlock) ;
    //std::cout << GREEN << "void srv::printValues() const" << WHITE << std::endl;
    //printValues();
    printArrayOfLocation();
}
srv::~srv()
{
    std::cout << "srv Destructor" << std::endl;
}
/* void srv::printValues() const
{
    std::cout << "Host: " << _host << std::endl;
    std::cout << "Port: " << _port << std::endl;
    std::cout << "Server Name: " << _server_name << std::endl;
    std::cout << "Body Size: " << _body << std::endl;
    std::cout << "root: " << _root << std::endl;
    
} */
void srv::printArrayOfLocation() const
{
    std::cout << "Number of locations: " << array_of_location.size() << std::endl;

    for (size_t i = 0; i < array_of_location.size(); ++i)
    {
    std::cout << "location " << (i + 1) << ":" << std::endl;
    std::cout << "Num of Location: " << i << std::endl;
    std::cout << "Location: " << array_of_location[i].getLocation() << std::endl;
    std::cout << "Root: " << array_of_location[i].getRoot() << std::endl;
    std::cout << "File: " << array_of_location[i].getFile() << std::endl;
    std::cout << "Methods: " << array_of_location[i].getMethods() << std::endl;
    std::cout << "Autoindex: " << array_of_location[i].getAutoindex() << std::endl;
    std::cout << "CGI: " << array_of_location[i].getCgi() << std::endl;
    std::cout << "Redirect 302: " << array_of_location[i].getRedirect302() << std::endl;
    }
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
    while (pos != std::string::npos) 
    {
        pos += 9; // Skip "root "
        size_t endPos = serverBlock.find('}', pos);
        std::string locationBlock = serverBlock.substr(pos, endPos - pos);
        //std::cout << MAGENTA << locationBlock << WHITE << std::endl;
        Location newLocation(locationBlock);
        pos += (endPos - pos);
        array_of_location.push_back(newLocation);
    }
}
