#ifndef CONFIG_HPP
# define CONFIG_HPP
#include "dependences.hpp"
#include "srv.hpp"
#include "Location.hpp"
#include "Utils.hpp"
class srv;
class Location;

class Config :public Utils
{
    protected:
    std::ifstream file;
    std::string file_content;

    int srvCount;
    int locationCount;
    std::vector<srv > array_of_srv;
    int server_id ;
    public:
    int ok;
    Config();
    Config(std::string configName);
    ~Config();

    bool openFile(std::string Configname);
    bool config_routine(std::string configName);
    bool getServerCount();
    
    // int countSubstring(const std::string& str, const std::string& sub);
	// size_t size(const char *s);
    bool createSrv();

    bool validatePort();

    std::vector<srv> & getArrayOfServers();
    bool pairbrackets(const std::string s);

    bool checksrvloc();
    std::string &  skip_p_t_esp(std::string &s);
    bool checkduplicateports();
    bool checkduplicateports_server_name();
    
};

#endif