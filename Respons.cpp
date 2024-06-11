
# include "Respons.hpp"
#include "Error.hpp"

Respons::Respons(Request * request, srv & sv, int fDescriptor) : rq(request), server(sv), fd(fDescriptor) {}

Respons::~Respons() {}

bool	Respons::checkLocation()
{
	for(size_t i = 0; i < server.arLoc.size(); i++)
	{
		if(rq->getUri() == server.arLoc[i]._location)
		{
			std::string url = server.arLoc[i]._root.substr(2) + "/" + server.arLoc[i]._file;
			std::cout << "url1 = " << url << std::endl;
			if (Utils::isFile(url.c_str()))
				return (_url = url, 1);
			else
				return (0);
			break;
		}
	}

	size_t pos = rq->getUri().find('/', 1);
	std::string str = "/";

	for(size_t i = 0; i< server.arLoc.size(); i++)
	{
		if (rq->getUri().substr(0, pos) == server.arLoc[i]._location)
		{
			std::string url = server.arLoc[i]._root.substr(2) + rq->getUri().substr(pos);
			std::cout << "url2 = " << url << std::endl;
			if (Utils::isFile(url.c_str()))
				return (_url = url, 1);
			else
				return (0);
			break;
		}
	}
	for(size_t i = 0; i< server.arLoc.size(); i++)
	{
		if (server.arLoc[i]._location == "/")
		{
			std::string url = server.arLoc[i]._root.substr(2) + rq->getUri();
			std::cout << "url3 = " << url << std::endl;
			if (Utils::isFile(url.c_str()))
				return (_url = url, 1);
		}	
}
	
	return (0);
}

bool	Respons::checkServerName()
{
	if (rq->getHost() != server._server_name.substr(1))// CUIDAO!! quitar substring
		return 0;
	else
		return 1;
	return 66;
}

bool	Respons::checkAuthorized()
{
	size_t point = _url.find('.');//cuidao si no lo encuentra

	std::cout << "url point =" << &_url[point] << std::endl;
	std::string extension = _url.substr(point);
	if(extension != ".html" && extension != ".jpg" && extension != ".png")
		return 0;
	return 1;
}

int Respons::createRespons()
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
		return 1;
	}
	std::cout << "---FINAL url = " << _url << std::endl;
	if (!checkAuthorized())
	{
		std::cout << "PAGE NOT FOUND" << std::endl;
		Error r(403, fd);
	}
	return 0;
}

//FUNCIONES PARA PRUEBAS---------------------------------------------------


void Respons::printRequest()
{
	std::cout  << std::endl << "-----REQUEST DESDE Respons-------" << std::endl << std::endl;
	std::cout << GREEN << "method: " << "\"" << BLUE << rq->getMethod() << GREEN << "\"" << std::endl;
    std::cout << "uri:" << "\"" << BLUE << rq->getUri() << GREEN << "\"" << std::endl;
    std::cout << "host: " << "\"" << BLUE << rq->getHost() << GREEN << "\"" <<std::endl;
    std::cout << "port: " << "\"" << BLUE << rq->getPort() << GREEN << "\"" <<std::endl;
    std::cout << "Content Lenght: " << "\"" << BLUE << rq->getContentLen() << GREEN << "\"" <<std::endl;
    std::cout << "Body: " << "\"" << BLUE << rq->getBody() << WHITE << std::endl << GREEN << "\"" << std::endl;
}

void Respons::printConf()
{
	std::cout << "-----CONF DESDE Respons-------" << std::endl;
	std::cout << std::endl << GREEN << "Host: " << BLUE << server._host << std::endl;
	std::cout << GREEN << "Port: " << BLUE << server._port << std::endl;
	std::cout << GREEN << "Server name:: " << BLUE << server._server_name << std::endl;
	std::cout << GREEN << "Body size: " << BLUE << server._body << WHITE << std::endl << std::endl;

	for(size_t j = 0; j < server.arLoc.size() ; j++)
    {
        std::cout << std::endl << "*LOCATION " << j + 1 << std::endl;
        std::cout << "Location: " << "\"" << GREEN << server.arLoc[j]._location << WHITE << "\"" << std::endl;
        std::cout << "root: " << "\"" << GREEN << server.arLoc[j]._root << WHITE << "\"" << std::endl;
        std::cout << "file: " << "\"" << GREEN << server.arLoc[j]._file << WHITE << "\"" << std::endl;
        std::cout << "methods: " << "\"" << GREEN << server.arLoc[j]._methods << WHITE << "\"" << std::endl;
        std::cout << "autoindex: " << "\"" << GREEN << server.arLoc[j]._autoindex << WHITE << "\"" << std::endl;
        std::cout << "cgi:" << "\"" << GREEN << server.arLoc[j]._cgi << WHITE << "\"" << std::endl;
        std::cout << "redirect: " << "\"" << GREEN << server.arLoc[j]._redirect_302 << WHITE << "\"" << std::endl;
    }
    std::cout << "---------------------------------------------------------------------" << std::endl;
}