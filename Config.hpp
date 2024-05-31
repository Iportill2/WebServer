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
    std::vector<std::map<std::string, std::string> > servers; // Vector de servidores
    struct location 
    {
        std::string name;

        std::string root;
        std::string file;
        std::string methods;
        std::string autoindex;
        std::string cgi;
        std::string redirect_302;
    }; 

    int server_id ;
public:
    Config();
    Config(std::string configName);
    ~Config();

    bool openFile(std::string Configname);
    void config_routine(std::string configName);
    bool getServerCount();
    void createvector(std::vector<std::map<std::string, std::string> > servers, const std::map<std::string, std::string>& new_content);
    void setKeyValue(const std::string& key, const std::string& value) ;
    std::map<std::string, std::string> setHostFromContent(const std::string& file_content) ;

	size_t size(const char *s);
};

#endif