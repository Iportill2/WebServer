
# include "Respons.hpp"
# include "Error.hpp"
# include "Dinamic.hpp"

Respons::Respons(Request * request, srv & sv, int fDescriptor) : rq(request), server(sv), fd(fDescriptor){}

Respons::~Respons() {}

int		Respons::cgiResponse()
{
	Cgi c(rq, _url, fd, server);
	if (rq->getMethod() == "get")
		c.createGetEnv();
	else if((rq->getMethod() == "post"))
	{
		c.createPostEnv();
		c.setPost();
	}
	c.exec();
	return 0;
}

void	Respons::htmlRespond()
{
	if (Utils::isFile(_url.c_str()) == false)
	{
		Error (404, fd, server);
		return;
	}
	std::ifstream file(_url.c_str());  // Abre el archivo en modo lectura
  	if (!file.is_open())
	{  
  		std::cerr << "Can't open : " << _url << std::endl;
		Error (403, fd, server);
		return;
 	}

	std::string httpResponse = "HTTP/1.1 200 OK\r\n"; // Línea de estado
   	httpResponse += "Content-Type: text/html\r\n"; // Encabezado Content-Type
  	httpResponse += "\r\n"; // Línea en blanco

    std::stringstream buffer;
   	buffer << file.rdbuf();  // Lee el contenido del archivo en el buffer
    file.close(); 

	httpResponse += buffer.str();

	write(fd, httpResponse.c_str(), httpResponse.size());
}

bool	Respons::checkServerName()
{
	//std::cout << "rq->getHost():" << rq->getHost() << std::endl;
	//std::cout << "server._server_name:" << server._server_name << std::endl;
	
	if (rq->getHost() != server._server_name)
		return false;

	return true;
}

bool	Respons::checkAuthorized()
{
	std::cout << "url:" << _url << std::endl;
	size_t point = _url.find('.');//cuidao si no lo encuentra
	if (point != std::string::npos)
		_extension = _url.substr(point);
	//std::cout << "Extension = " << "\"" <<  _extension  << "\"" << std::endl;

	/* if(_extension != ".html" && _extension != ".jpg" && _extension != ".png" && _extension != ".ico" && _extension != ".out")
		return 0; */
	return true;
}
bool	Respons::checkMethod()
{
	for (size_t i = 0; i < server.arLoc[_loc].methods_vector.size(); i++)
	{
		if (rq->getMethod() == server.arLoc[_loc].methods_vector[i])
			return true;
	}
	if (server.arLoc[_loc]._redirect.empty() == false)
	return true;

	return false;
}

bool	Respons::checkBodySize()
{
	//std::cout << "Admitido:" << server._sizetBody << "Tamaño del archivo:" << rq->getContentLen() << std::endl;
	if (server._sizetBody < rq->getContentLen())
		return 0;
	return 1;
}

bool	Respons::manageData()
{
	std::map<std::string, std::string>::iterator it = rq->data.begin();
    while (it != rq->data.end())
	{
		if(it->first == "page" && it->second == "dinamic")
		{
			Dinamic p(_url, fd);
			p.createResponse();
			return true;
		}
		it++;
	}

	it = rq->data.begin();
	while (it != rq->data.end())
	{
		if(it->first == "page" && it->second == "download")
		{
			Download d(rq, _url, fd);
			d.sendForm();
			return true;
		}
		it++;
	}

	it = rq->data.begin();
	while (it != rq->data.end())
	{
		if(it->first == "page" && it->second == "setdownload")
		{
			Download d(rq, _url, fd);
			d.sendFile();
			return true;
		}
		it++;
	}

	it = rq->data.begin();
	while (it != rq->data.end())
	{
		if(it->first == "page" && it->second == "delete")
		{
			Dinamic d(_url, fd);
			d.createDeleteForm();
			return true;
		}
		it++;
	}

	it = rq->data.begin();
	while (it != rq->data.end())
	{
		if(it->first == "page" && it->second == "setDelete")
		{
			_url = _url + "/" + rq->data["file"];
			deleteResponse();
			return true;
		}
		it++;
	}

	if (rq->getBoundary().empty() == false)
	{
		Load l(rq, fd, _url, server);
		if (l.createFile() == true)
		{
			_url = "load/upOk.html";
			htmlRespond();
		}
		return true;
	}

	return false;
}

int	Respons::deleteResponse()
{
	Delete d(_url, fd, server);
	d.DeleteResource();
	return 0;
}

int	Respons::getResponse()
{
	if (manageData() == true)
		return 0;
	//std::cout << "URL:" << _url << std::endl;
	if(Utils::isDirectory(_url.c_str()) == true)
		return (Error (403, fd, server), 1);
	if(Utils::isFile(_url.c_str()) == false)
		return (Error (404, fd, server), 1);
	if (_extension == ".html")
		htmlRespond();
	else if(_extension == ".jpg")
		jpgRespond();
	else if(_extension == ".png")
		pngRespond();
	else if(_extension == ".out")
		cgiResponse();
	else
		Error(415, fd, server);
	return 0;
}

int	Respons::postResponse()
{
	if(checkBodySize() == false)
		return(Error(413, fd, server), 1);
	if (manageData() == true)
		return 0;
	if(Utils::isDirectory(_url.c_str()) == true)
		return (Error (403, fd, server), 1);
	if(Utils::isFile(_url.c_str()) == false)
		return (Error (404, fd, server), 1);
	std::cout << "Extension:" << _extension << std::endl;
	if (_extension == ".html")
		htmlRespond();
	else if(_extension == ".jpg")
		jpgRespond();
	else if(_extension == ".png")
		pngRespond();
	else if(_extension == ".out")
		cgiResponse();
	else
		Error(415, fd, server);
	return 0;
}


void	Respons::redirect(std::string & url)
{
	std::string httpResponse = "HTTP/1.1 302 Found\r\n";
    httpResponse += "Location: " + url + "\r\n";
    httpResponse += "Content-Length: 0\r\n";
    httpResponse += "Connection: close\r\n";
    httpResponse += "\r\n";

	write (fd, httpResponse.c_str(), httpResponse.size());
}


void	Respons::setBestLocation()
{
	std::cout << "Uri:" <<  rq->getUri() << std::endl << std::endl;
	for (size_t i = 0; i < server.arLoc.size(); i++)
		std::cout << "loc " << i + 1 << " :" << server.arLoc[i].getLocation() << RED << " *" << WHITE << 
		" file:" << server.arLoc[i].getFile() << RED << " *" << WHITE <<" Root:"<< server.arLoc[i].getRoot() << std::endl;

	

	for (size_t i = 0; i < server.arLoc.size(); i++)
	{
		if(server.arLoc[i].getLocation() == "/")
		{
			_defaultRoot = server.arLoc[i].getRoot();
			_loc = i;
		}

		if(rq->getUri() == server.arLoc[i].getLocation())
		{
			if(!server.arLoc[i].getFile().empty())
				_url = server.arLoc[i].getRoot().substr(2) + "/" + server.arLoc[i].getFile();
			else
				_url = server.arLoc[i].getRoot().substr(2);
			_loc = i;//mirar si es necesario
			return;
		}
	} 
	size_t size = 0;
	for (size_t i = 0; i < server.arLoc.size(); i++)
	{
		if(rq->getUri().size() > server.arLoc[i].getLocation().size() && 
		rq->getUri()[server.arLoc[i].getLocation().size()] == '/' &&
		rq->getUri().substr(0, server.arLoc[i].getLocation().size()) == server.arLoc[i].getLocation())
		{
			if (server.arLoc[i].getLocation().size() > size)
			{
				size = server.arLoc[i].getLocation().size();
				_loc = i;
			}
		}
	}
	if (size)
		_url = server.arLoc[_loc].getRoot().substr(2) + rq->getUri().substr(server.arLoc[_loc].getLocation().size());
	else
		_url = _defaultRoot.substr(2) + rq->getUri();
}

int	Respons::createRespons() //ENTRADA------------------------
{
	setBestLocation();

	//std::cout << "url:" << _url << std::endl;

	if (checkServerName() == false)
		return (Error (400, fd, server), 1);

	if(checkMethod() == false)
		return (Error (405, fd, server), 1);

	if(server.arLoc[_loc]._redirect.empty() == false)
		return (redirect(server.arLoc[_loc]._redirect), 0);
	if(server.arLoc[_loc].getAutoindex() == "on" && Utils::isDirectory(_url.c_str()) == true)//igual meterle que sea directorio...
		return (Autoindex (server, fd, _loc), 0);

	/* if(Utils::isDirectory(_url.c_str()) == true)
		return (Error (403, fd), 1);
	if(Utils::isFile(_url.c_str()) == false)
		return (Error (404, fd), 1); */
	if(checkAuthorized() == false)
		return (Error (403, fd, server), 1);

	if(rq->getMethod() == "get")
		getResponse();
	else if(rq->getMethod() == "post")
		postResponse();
	else if(rq->getMethod() == "delete")
		deleteResponse();

	return 0;
}


void	Respons::jpgRespond()
{
	std::ifstream file(_url.c_str(), std::ios::binary);
    std::ostringstream oss;
    oss << file.rdbuf();
	std::string image = oss.str();

	std::string httpResponse = "HTTP/1.1 200 OK\r\n";
    httpResponse += "Content-Type: image/jpeg\r\n";
    httpResponse += "\r\n";
    httpResponse += image;

    write(fd, httpResponse.c_str(), httpResponse.size());
}
void	Respons::pngRespond()
{
	std::ifstream file(_url.c_str(), std::ios::binary);
    std::ostringstream oss;
    oss << file.rdbuf();
	std::string favi = oss.str();

	std::string httpResponse = "HTTP/1.1 200 OK\r\n";
    httpResponse += "Content-Type: image/png\r\n";
    httpResponse += "\r\n";
    httpResponse += favi;

    write(fd, httpResponse.c_str(), httpResponse.size());
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
    std::cout << "Body: " << "\"" << BLUE << rq->getBody()  << GREEN << "\"" << GREEN << std::endl;
	std::cout << "Boundary: " << "\"" << BLUE << rq->getBoundary()  << GREEN << "\"" << WHITE<< std::endl;
}

void Respons::printConf()
{
	std::cout << "-----CONF DESDE Respons-------" << std::endl;
	std::cout << GREEN << "Server name:: " << BLUE << server._server_name << std::endl;
	std::cout << GREEN << "ip_num : " << BLUE << server._ipNum << std::endl;
	std::cout << GREEN << "Port: " << BLUE << server._sizetPort << std::endl;
	std::cout << GREEN << "Body size: " << BLUE << server._sizetBody << WHITE << std::endl << std::endl;

	for(size_t j = 0; j < server.arLoc.size() ; j++)
    {
        std::cout << std::endl << "*LOCATION " << j + 1 << std::endl;
        std::cout << "Location: " << "\""  << server.arLoc[j]._location  << "\"" << std::endl;
        std::cout << "root: " << "\"" << GREEN << server.arLoc[j]._root << WHITE << "\"" << std::endl;
        std::cout << "file: " << "\"" << GREEN << server.arLoc[j]._file << WHITE << "\"" << std::endl;
		for (size_t k = 0; k < server.arLoc[j].methods_vector.size(); k++)
			std::cout << "Method " << k + 1 << ": " << "\"" << GREEN << server.arLoc[j].methods_vector[k] << WHITE << "\"" << std::endl;
        // std::cout << "methods: " << "\"" << GREEN << server.arLoc[j]._methods << WHITE << "\"" << std::endl;
        // std::cout << "autoindex: " << "\"" << GREEN << server.arLoc[j]._autoindex << WHITE << "\"" << std::endl;
        // std::cout << "cgi:" << "\"" << GREEN << server.arLoc[j]._cgi << WHITE << "\"" << std::endl;
        // std::cout << "redirect: " << "\"" << GREEN << server.arLoc[j]._redirect_302 << WHITE << "\"" << std::endl;
    }
    std::cout << "---------------------------------------------------------------------" << std::endl;
}