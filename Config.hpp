#ifndef CONFIG_HPP
# define CONFIG_HPP
#include "dependences.hpp"

class srv;


class Config
{
    protected:
    std::ifstream file;
    std::string file_content;

    int srvCount;
    int locationCount;
    std::vector<srv> array_of_srv;

    int server_id ;
public:
    Config();
    Config(std::string configName);
    ~Config();

    void setValues();
    bool openFile(std::string Configname);
    void config_routine(std::string configName);
    bool getServerCount();
    
    int countSubstring(const std::string& str, const std::string& sub);
	size_t size(const char *s);
    void createLocations(const srv& newServer); 
    void createSrv();
};

#endif