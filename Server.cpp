#include "dependences.hpp"


int Server::sign = 1;

Server::Server()
{

}
Server::Server(std::string configName) 
{
	(void)configName;
}



Server::~Server()
{

	std::cout << "Server destructor called!" << std::endl;
}

void Server::set_data()
{
	std::cout << "Server set_data called!" << std::endl;
}
void Server::setKeyValue(const std::string& key, const std::string& value) 
{
	keyValue[key] = value;
}
std::string Server::getValue(const std::string& key) const 
{
	return keyValue.find(key) != keyValue.end() ? keyValue.at(key) : "";
}


