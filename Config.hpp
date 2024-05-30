#ifndef CONFIG_HPP
# define CONFIG_HPP
#include "dependences.hpp"

class Server;

class Config
{
    protected:
    std::ifstream file;
    std::string file_content;

    int serverCount;

    int server_id ;
    std::vector<std::map<std::string, std::string> > servers; // Vector de servidores
public:
    Config();
    Config(std::string configName);
    ~Config();

    bool openFile(std::string Configname);
    void config_routine(std::string configName);
    int getServerCount();
    void createvector(std::vector<std::map<std::string, std::string> > servers, const std::map<std::string, std::string>& new_content);
    void setKeyValue(const std::string& key, const std::string& value) ;
    std::map<std::string, std::string> setHostFromContent(const std::string& file_content) ;
};

#endif