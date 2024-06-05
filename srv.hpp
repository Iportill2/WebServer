#ifndef SRV_HPP
# define SRV_HPP
#include "dependences.hpp"
#include "Location.hpp"

class Location;

class srv
{
    public:
    std::string _host;
    std::string _port;
    std::string _server_name;
    std::string _body;
    std::string _Root;

    //unsigned long decimalIp;

    int locationCount;
    std::vector<Location> array_of_location;


    srv(std::string serverBlock);
    ~srv();

    void nullstrings();
    void parseServerBlock(const std::string& serverBlock) ;


    std::string getHost() const { return _host; }
    std::string getPort() const { return _port; }
    std::string getServerName() const { return _server_name; }
    std::string getBodySize() const { return _body; }
    std::string getRoot() const { return _Root; }

	///locations
	std::vector<Location> & getlocations();
    unsigned long ipToDecimal(const std::string& ip);
};
#endif
