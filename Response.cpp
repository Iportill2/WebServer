
# include "Response.hpp"
#include "Error.hpp"

Response::Response(Request * request, Confs & cnf, int fDescriptor) : rq(request), conf(cnf), fd(fDescriptor) {}

Response::~Response() {}

bool	Response::checkLocation()
{
	std::map<std::string, loc>::iterator  in = conf.location.begin();
	std::map<std::string, loc>::iterator  out = conf.location.end(); 

	while (in != out)
	{
		if(rq->getUri() == in->first)
		{
			std::string url = in->second.root.substr(2) + "/" + in->second.file;
			std::cout << "url1 = " << url << std::endl;
			if (Utils::isFile(url.c_str()))
				return (_url = url, 1);
			else
				return (0);
			break;
		}
		in++;
	}

	size_t pos = rq->getUri().find('/', 1);
	std::string str = "/";
	in = conf.location.begin();
	while (in != out)
	{
		if (in->first == rq->getUri().substr(0, pos))
		{
			std::string url = in->second.root.substr(2) + rq->getUri().substr(pos);
			std::cout << "url2 = " << url << std::endl;
			if (Utils::isFile(url.c_str()))
				return (_url = url, 1);
			else
				return (0);
			break;
		}
		in++;
	}
	std::string url = conf.location["/"].root.substr(2) + rq->getUri();	
	std::cout << "url3 = " << url << std::endl;
	if (Utils::isFile(url.c_str()))
				return (_url = url, 1);
	return (0);
}

bool Response::checkServerName()
{
	if (rq->getHost() != conf.server_name)
		return 0;
	else
		return 1;
}

int Response::createResponse()
{
	if (!checkServerName())
	{
		std::cout << "SERVERNAME ERROR" << std::endl;
		Error r(400, fd);
		return 1;
	}
	if (!checkLocation())
	{
		std::cout << "PAGE NOT FOUND" << std::endl;
		Error r(404, fd);
		//return 1;
	}
	std::cout << "FINAL url = " << _url << std::endl;
	return 0;
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