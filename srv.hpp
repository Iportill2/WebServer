#ifndef SRV_HPP
# define SRV_HPP
#include "dependences.hpp"
#include "Location.hpp"
#include "ErrorPage.hpp"

class Location;
class ErrorPage;

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

    int locationCount;/// esto no esta ya en config???
    std::vector<Location> arLoc;

    //ErrorPage ErrPag;
    std::vector<ErrorPage> arErr;// podemos usar una  variable en vez de un vector
    //ErrorPage arErr; 
    std::map<std::string, std::string> result;

    bool srv_ok;

    srv();
    srv(std::string serverBlock);
    //srv(const srv& other);
    ~srv();


   


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
    bool ipAddressToipNum(std::string ipAddress);
    void findAndExtractRoot(const std::string& serverBlock, size_t pos); 


    void deletespaces(std::string &s);
    bool parseServerBlock(const std::string& s) ;
    bool stringToSizeT(const std::string& s, size_t &n);     

};
#endif
