//#include "dependences.hpp"
#include "Server.hpp"

int Server::sign = 1;
void validate()
{
	std::cout << "validate" << std::endl;
}



Server::Server() : Config()
{
	std::cout << "Default Server constructor called!" << std::endl;
	this->def_or_conf = "def";
	id = 0; 

	signal(SIGINT, signalHandler);
	signal(SIGTERM, &signalHandler);

	sock = socket(AF_INET, SOCK_STREAM, 0);

	int option = 1;
	
	//(setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option)) == -1); // el de iban
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &option, sizeof(option));

	ad.sin_family = AF_INET;
    ad.sin_port = htons(this->getPort());
    ad.sin_addr.s_addr = htonl(this->getdecimalIp());//servaddr.sin_addr.s_addr = htonl(2130706433); //127.0.0.1

	if (bind (sock, (sockaddr *)&ad, sizeof(ad)) == -1)
		std::cout << "Puerto ocupau atontau" << std::endl;

	listen(sock, 10);
	
	my_select();
}
Server::Server(std::string configName) : Config (configName)
{
	std::cout << "Server constructor called!" << std::endl;
	this->def_or_conf = "conf";
	id = 0; 

	signal(SIGINT, signalHandler);
	signal(SIGTERM, &signalHandler);

	sock = socket(AF_INET, SOCK_STREAM, 0);

	int option = 1;
	
	//(setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option)) == -1); // el de iban
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &option, sizeof(option));

	ad.sin_family = AF_INET;
    ad.sin_port = htons(this->getPort());
    ad.sin_addr.s_addr = htonl(this->getdecimalIp());//servaddr.sin_addr.s_addr = htonl(2130706433); //127.0.0.1

	if (bind (sock, (sockaddr *)&ad, sizeof(ad)) == -1)
		std::cout << "Puerto ocupau atontau" << std::endl;

	listen(sock, 10);
	
	my_select();
}

void	Server::my_select()
{
	fd_set readyfdsRead, activefdsRead;
	fd_set readyfdsWrite, activefdsWrite;
	t_client clients[100];

	int addrlen = sizeof(ad);

	FD_ZERO(&readyfdsRead);
	FD_ZERO(&activefdsRead);
	FD_ZERO(&readyfdsWrite);
	FD_ZERO(&activefdsWrite);

	
	(void) clients;
	int	maxfd = sock;

	FD_SET (sock, &activefdsRead);

	while(sign)
	{
		readyfdsRead = activefdsRead;
		readyfdsWrite = activefdsWrite;
		//int s = select(maxfd + 1, &readyfdsRead, &readyfdsWrite, NULL, NULL);
		select(maxfd + 1, &readyfdsRead, &readyfdsWrite, NULL, NULL);
		if (!sign)
			break;
		for (int i = 0; i <= maxfd; i++)
		{
			if (!FD_ISSET(i, &readyfdsRead) && !FD_ISSET(i, &readyfdsWrite))
				continue;
			else if (FD_ISSET(i, &readyfdsRead))
			{
				if (i == sock)
				{
					new_socket = accept(sock, (struct sockaddr *)&ad, (socklen_t*)&addrlen);
					//new_socket = accept(sock, NULL,NULL);
					FD_SET (new_socket, &activefdsRead);
				
					if (new_socket > maxfd)
						maxfd = new_socket;
					
					clients[id++].fd = new_socket;
					std::cout  << std::endl << ">>>>>   New Client just arrived; " << "ID: " << id - 1 << "; FD: " << new_socket << std::endl; 
				}
				else
				{
					//int bytes = read(i, buffer, sizeof(buffer));
					int bytes = read(i, buffer, sizeof(buffer));
					std::cout << std::endl;
					std::cout << "---BUFFER---" << std::endl;
					std::cout << buffer << std::endl;
					std::cout << "---BUFFER END ---" << std::endl << std::endl;
					if (bytes <= 0)
					{
						std::cout << "Client ID: " << id - 1 << " went \"a tomar por culo\"" << std::endl << std::endl;
						FD_CLR(i, &activefdsRead);
            			close(i);
					}
					else
					{ 
						std::cout << "Client ID: " << id - 1 << " pasa a la cola de WRITE!!!" << std::endl;
						FD_SET(i, &activefdsWrite);
						FD_CLR(i, &activefdsRead);
					}
				}
			}	
			else if (FD_ISSET(i, &readyfdsWrite))
			{
				std::cout << "Client ID: " << id - 1 << " es RESPONDIDO!!!" << std::endl;
				respond(i);
				close (i);
				FD_CLR(i, &activefdsWrite);
			}
		}
	}
	for (int i = 3; i <= maxfd; ++i)
	{
		std::cout << "cerrando fd: " << i << std::endl;
		int  stat = close(i);

		std::cout << "status fd " << i << " = " <<  stat << std::endl;
	}	
}			

void	Server::respond(int i)
{
	(void)i;
	/* std::string temp = "GET /"; //temporal para buscar el GET
	std::string request(buffer);//buffer es 30000
	if (request.find(temp + this->Imagen) != std::string::npos)
	{
		std::ifstream file;
			file.open(this->Ruta_imagen.c_str(), std::ios::binary);
    	if (!file.is_open()) 
		{
			std::ifstream error;
			error.open(this->ErrorDocument_404.c_str(), std::ios::binary);
			std::cout << RED <<"jpg NOT FOUND" << WHITE <<std::endl; 
			std::ostringstream oss;
    		oss << error.rdbuf();
			std::string ERROR = oss.str();
	
			std::string httpResponse = "HTTP/1.1 200 OK\r\n";
        	httpResponse += "Content-Type: image/jpg\r\n";
        	httpResponse += "\r\n";
        	httpResponse += ERROR;
        	write(i, httpResponse.c_str(), httpResponse.size());
		}
       // Manejar el error, por ejemplo, enviar una respuesta 404 Not Found
   		else 
		{
       // Proceder con la lectura del archivo y la creación de la respuesta HTTP
			std::ostringstream oss;
    		oss << file.rdbuf();
			std::string foto = oss.str();
	
			std::string httpResponse = "HTTP/1.1 200 OK\r\n";
        	httpResponse += "Content-Type: image/jpg\r\n";
        	httpResponse += "\r\n";
        	httpResponse += foto;
        	write(i, httpResponse.c_str(), httpResponse.size());
		//close(file);
   		}
	}
	else if (request.find("GET /favicon.ico") != std::string::npos)
	{
		std::ifstream file; // Declare file outside the if-else blocks

		file.open(this->Ruta_favicon.c_str(), std::ios::binary); // Open file inside the if block
	 	if (!file.is_open()) 
	 		std::cout << RED <<"favicon.ico NOT FOUND" << WHITE <<std::endl; 
   	    // Manejar el error, por ejemplo, enviar una respuesta 404 Not Found
   	 	else 
	 	{
			std::ostringstream oss;
    		oss << file.rdbuf();
			std::string favi = oss.str();
			std::string httpResponse = "HTTP/1.1 200 OK\r\n";
        	httpResponse += "Content-Type: image/png\r\n";
        	httpResponse += "\r\n";
        	httpResponse += favi;
        	write(i, httpResponse.c_str(), httpResponse.size());
		//close(file);
		}
	}
    else
	{
    	std::string httpResponse;
    	std::ifstream file(Config::DirectoryIndex.c_str(), std::ios::in); // Intenta abrir el archivo HTML

    	if (!file.is_open()) 
    	{
        	std::cout << RED << Config::DirectoryIndex << " NOT FOUND" << WHITE << std::endl;
        	// Configurar la respuesta HTTP para 404 Not Found
        	httpResponse = "HTTP/1.1 404 Not Found\r\n";
        	httpResponse += "Content-Type: text/html\r\n";
        	httpResponse += "\r\n";

			const char *s404 = Config::ErrorDocument_404.c_str();
        	// Intentar abrir el archivo de error 404
        	std::ifstream errorFile(s404, std::ios::in);
        	if (!errorFile.is_open()) 
        	{
            	// Si el archivo 404.html tampoco se encuentra, enviar un mensaje de error simple
        		httpResponse += "<html><body><h1>404 Not Found</h1></body></html>";
        	} 
        	else 
        	{
            	// Si el archivo 404.html se encuentra, leer su contenido y enviarlo
            	std::stringstream buffer;
            	buffer << errorFile.rdbuf();
            	httpResponse += buffer.str();
            	errorFile.close();
        	}
    	} 
    	else 
    	{
        	// Si el archivo se abre correctamente, configurar la respuesta HTTP para 200 OK
        	httpResponse = "HTTP/1.1 200 OK\r\n";
        	httpResponse += "Content-Type: text/html\r\n";
        	httpResponse += "\r\n";

        // Leer el contenido del archivo y añadirlo a la respuesta
        	std::stringstream buffer;
        	buffer << file.rdbuf();
        	httpResponse += buffer.str();
        	file.close();
    	}

    	// Enviar la respuesta HTTP
    	write(i, httpResponse.c_str(), httpResponse.size());
	} */
}

Server::~Server()
{
	close (sock);
	std::cout << "Server destructor called!" << std::endl;
}



void	Server::signalHandler(int i)
{
	(void)i;
	std::cout << std::endl << "crtl + c pulsado. cerramos puerto italiano al pie de las montañas" << std::endl;
	sign = 0;
}

unsigned long Server::getdecimalIp()
{
	return this->Config::decimalIp;
}

int Server::getPort()
{
	return this->Config::port;
}


/* void Server::abind() {
	sockaddr_in servaddr = {};
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(custom_inet_addr(_address));

	if (_port <= 1024 || _port > 65535)
		throw std::runtime_error("Invalid port number on server " + _server_name);
	servaddr.sin_port = htons(_port);

	((_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		? throw std::runtime_error("Socket creation failed\n")
		: Logger::debug("Socket successfully created");

	// set socket as reusable
	int option = 1;
	((setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option)) == -1))
		? throw std::runtime_error("Setting to reusable failed\n")
		: Logger::debug("Socket options successfully setted");

	// https://man7.org/linux/man-pages/man2/bind.2.html
	(::bind(_fd, reinterpret_cast<struct sockaddr *>(&servaddr), sizeof(servaddr)) == -1)
		? throw std::runtime_error("Binding failed\n")
		: Logger::debug("Socket successfully binded");

	// https://man7.org/linux/man-pages/man2/listen.2.html
	listen(_fd, 256);
	Logger::info("Server listening on port " + Utils::toString(_port));

	// setting socket as non blocking
	(fcntl(_fd, F_SETFL, O_NONBLOCK, FD_CLOEXEC) == -1)
		? throw std::runtime_error("Setting to nonblocking failed")
		: Logger::debug("Socket setted to non blocking");

	Logger::info("Server " + _server_name + " listening in port " + Utils::toString(_port));
} */

