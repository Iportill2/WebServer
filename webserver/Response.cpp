
# include "Response.hpp"
#include "Error.hpp"

Response::Response(Request * request, Confs & cnf, int fDescriptor) : rq(request), conf(cnf), fd(fDescriptor) {}

Response::~Response() {}


int Response::createResponse()
{
	if (!checkServerName())
	{
		std::cout << "SERVERNAME ERROR" << std::endl;
		Error r(400, fd);
	}
	return 1;
}
bool Response::checkServerName()
{
	if (rq->getHost() != conf.server_name)
		return 0;
	else
		return 1;
}

//FUNCIONES PARA PRUEBAS---------------------------------------------------


void Response::printRequest()
{
	std::cout  << std::endl << "-----REQUEST DESDE RESPONSE-------" << std::endl << std::endl;
	std::cout << GREEN << "method: " << BLUE << rq->getMethod() << std::endl << std::endl;
    std::cout << GREEN << "uri: " << BLUE << rq->getUri() << std::endl;
    std::cout << GREEN << "host: " << BLUE << rq->getHost() << std::endl;
    std::cout << GREEN << "port: " << BLUE << rq->getPort() << std::endl;
    std::cout << GREEN << "Content Lenght: " << BLUE << rq->getContentLen() << std::endl;
    std::cout << GREEN << "Body: " << BLUE << rq->getBody() << WHITE << std::endl << std::endl;
}

void Response::printConf()
{
	std::cout << "-----CONF DESDE RESPONSE-------" << std::endl;
	std::cout << std::endl << GREEN << "Host: " << BLUE << conf.host << std::endl;
	std::cout << GREEN << "Port: " << BLUE << conf.port << std::endl;
	std::cout << GREEN << "Server name:: " << BLUE << conf.server_name << std::endl;
	std::cout << GREEN << "Body size: " << BLUE << conf.body_size << WHITE << std::endl << std::endl;

	std::map<std::string, loc>::iterator iti;
	std::map<std::string, loc>::iterator ito;
	iti = conf.location.begin();
	ito = conf.location.end();
	int i = 1;
	
	while (iti != ito)
	{
		std::cout << GREEN << "LOCATION " << i << " " << YELLOW << iti->first << std::endl;
		std::cout << GREEN << "File: " << BLUE << iti->second.file << std::endl;
		std::cout << GREEN << "Root: " << BLUE << iti->second.root << std::endl;
		std::cout << GREEN << "Methods: " << BLUE;
		for (const auto& str : iti->second.methods)
         	std::cout << str << " ";
		std::cout << WHITE << std::endl << std::endl;
		iti++;
		i++;
	}
}