#ifndef CONFIG_HPP
# define CONFIG_HPP
#include "dependences.hpp"
#include "Server.hpp"


class Server;

class Config
{

protected:
  std::string _file;
  std::vector<Server> _servers;

  	int port;
	  unsigned long decimalIp;
public:
	  Config();
  	Config(const std::string &file);
  	~Config();

  bool parse();
  void load();
  void validate() const;

  const Server& getServer(int port) const;
  int serverCount();
  std::vector<int> serverSockets();


  unsigned long ipToDecimal(const std::string& ip);
};

#endif