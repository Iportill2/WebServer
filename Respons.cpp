
# include "Respons.hpp"
#include "Error.hpp"

Respons::Respons(Request * request, srv & sv, int fDescriptor) : rq(request), server(sv), fd(fDescriptor) {}

Respons::~Respons() {}

int	Respons::checkLocation()
{

	for(size_t i = 0; i < server.arLoc.size(); i++)
	{
		if(rq->getUri() == server.arLoc[i]._location)
		{
			if (server.arLoc[i]._location == "/redirect")
			{
				//std::cout << std::endl << "Gaby, fofo y miliki" << std::endl << std::endl;
				return(_url = server.arLoc[i]._redirect, 2);
			}
			if (server.arLoc[i]._autoindex == "on;")
				autoindex(server.arLoc[i]._root);
			_loc = i;
			std::string url = server.arLoc[i]._root.substr(2) + "/" + server.arLoc[i]._file;
			//std::cout << "url1 = " << url << std::endl;
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
			_loc = i;
			std::string url = server.arLoc[i]._root.substr(2) + rq->getUri().substr(pos);
			//std::cout << "url2 = " << url << std::endl;
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
			_loc = i;
			std::string url = server.arLoc[i]._root.substr(2) + rq->getUri();
			//std::cout << "url3 = " << url << std::endl;
			if (Utils::isFile(url.c_str()))
				return (_url = url, 1);
		}	
}
	
	return (0);
}

bool	Respons::checkServerName()
{
	if (server._server_name.empty())
		return 1;
	if (rq->getHost() != server._server_name)// CUIDAO!! quitar substring
		return 0;
	else
		return 1;
}

bool	Respons::checkAuthorized()
{
	size_t point = _url.find('.');//cuidao si no lo encuentra

	_extension = _url.substr(point);
	//std::cout << "Extension = " << "\"" <<  _extension  << "\"" << std::endl;

	if(_extension != ".html" && _extension != ".jpg" && _extension != ".png" && _extension != ".ico")
		return 0;
	return 1;
}
bool	Respons::checkMethod()
{
	for (size_t i = 0; i < server.arLoc[_loc].methods_vector.size(); i++)
	{
		if (rq->getMethod() == server.arLoc[_loc].methods_vector[i])
			return 1;
	}
	return 0;
}

int Respons::createRespons()
{
	if (!checkServerName())
	{
		//std::cout << "SERVERNAME ERROR" << std::endl;
		Error r(400, fd);
		return 1;
	}
	int locat = checkLocation();
	if (!locat)
	{
		//std::cout << "PAGE NOT FOUND" << std::endl;
		Error r(404, fd);
		return 1;
	}
	//std::cout << "---FINAL url = " << _url << std::endl;
	//std::cout << "location = " << locat << std::endl;

	if (locat != 2 && !checkAuthorized())
	{
		//std::cout << "PAGE FORBIDDEN" << std::endl;
		Error r(403, fd);
		return 1;
	}
	if (locat != 2 && !checkMethod())
	{
		//std::cout << "METHOD NOT ALLOWED" << std::endl;
		Error r(405, fd);
		return 1;
	}

	//std::cout <<  "Extension en createResponse: " << _extension << std::endl;
	if (locat == 2)
	{
		std::string httpResponse = "HTTP/1.1 302 Found\r\n";
        httpResponse += "Location: " + _url + "\r\n";
        httpResponse += "Content-Length: 0\r\n";
        httpResponse += "Connection: close\r\n";
        httpResponse += "\r\n";

		write (fd, httpResponse.c_str(), httpResponse.size());
	}
	else if (_extension == ".html")
		htmlRespond();
	else if (_extension == ".jpg")
		jpgRespond();
	else if (_extension == ".png")
		pngRespond();

	return 0;
}

void	Respons::htmlRespond()
{
	//std::cout << "*********************************************" << std::endl;
	std::string httpResponse = "HTTP/1.1 200 OK\r\n"; // Línea de estado
   	httpResponse += "Content-Type: text/html\r\n"; // Encabezado Content-Type
    httpResponse += "\r\n"; // Línea en blanco

	std::ifstream file(_url.c_str());  // Abre el archivo en modo lectura
    if (!file.is_open()) {  // Verifica si el archivo se abrió correctamente
        std::cerr << "Can't open : " << _url << std::endl;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();  // Lee el contenido del archivo en el buffer
    file.close(); 

	httpResponse += buffer.str();

	write(fd, httpResponse.c_str(), httpResponse.size());
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
    std::cout << "Body: " << "\"" << BLUE << rq->getBody() << WHITE << std::endl << GREEN << "\"" << std::endl;
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