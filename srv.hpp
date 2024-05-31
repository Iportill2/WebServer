#ifndef SRV_HPP
# define SRV_HPP
#include "dependences.hpp"
#include "Config.hpp"

class location;

class srv
{
    public:
    std::string _host;
    std::string _port;
    std::string _server_name;
    std::string _body;
    std::string _root;

    int locationCount;
    std::vector<location> array_of_location;


    srv(std::string serverBlock);
    ~srv();

   void instanceLocations();
   void parseServer(std::string serverBlock);
};
#endif
