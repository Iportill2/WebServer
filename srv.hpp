#ifndef SRV_HPP
# define SRV_HPP
#include "dependences.hpp"


class Location;

class srv
{
    public:
    std::string _host;
    std::string _port;
    std::string _server_name;
    std::string _body;
    std::string _root;

    int locationCount;
    std::vector<Location> array_of_location;


    srv(std::string serverBlock);
    ~srv();

   void instanceLocations();
   void parseServerBlock(const std::string& serverBlock) ;
   void printValues() const;
};
#endif
