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
    uint32_t _ipNum;

    size_t _sizetPort;
    size_t _sizetBody;

    int locationCount;
    std::vector<Location> arLoc;

    std::map<std::string, std::string> result;

    srv(){};
    srv(std::string serverBlock);
    ~srv();

    void nullstrings();
    //void parseServerBlock(const std::string& serverBlock) ;


    std::string getHost() const { return _host; }
    std::string getPort() const { return _port; }
    std::string getServerName() const { return _server_name; }
    std::string getBodySize() const { return _body; }
    std::string getRoot() const { return _Root; }

	///locations
	std::vector<Location> & getlocations();

    /// 
    unsigned long ipToDecimal(const std::string& ip);
    bool checkstring();
    void deletespaces(std::string &s);
    bool ipAddressToipNum(std::string IpAddress);
    bool stringToSizeT(const std::string& s, size_t &n);

    void findAndExtractRoot(const std::string& serverBlock, size_t pos); 



    bool parseServerBlock(const std::string& s) ;
    int countSubstring(const std::string& str, const std::string& sub);
    void setServerBlockValues(std::string s);
};
#endif
