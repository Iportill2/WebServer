#ifndef CONFIG_HPP
# define CONFIG_HPP
#include "dependences.hpp"
#include "srv.hpp"
#include "Location.hpp"
class srv;
class Location;

class Config
{
    protected:
    std::ifstream file;
    std::string file_content;

    int srvCount;
    int locationCount;
    std::vector<srv > array_of_srv;
    
    int server_id ;
public:
    Config();
    Config(std::string configName);
    ~Config();

    void setValues();
    bool openFile(std::string Configname);
    bool config_routine(std::string configName);
    bool getServerCount();
    
    int countSubstring(const std::string& str, const std::string& sub);
	size_t size(const char *s);
    void createSrv();

    void printArrayOfSrv() const;
    /////
    bool validatePort();

    std::vector<srv> & getArrayOfServers();
};

#endif