#include "Server.hpp"

Server::Server(std::string configName) : Config (configName)
{
	std::cout << "Server constructor called!" << std::endl;

	id = 0; 

	sock = socket(AF_INET, SOCK_STREAM, 0);
	
	sockaddr_in	ad;
	ad.sin_family = AF_INET;
    ad.sin_port = htons(Config::getPort());
    ad.sin_addr.s_addr = htonl(Config::getdecimalIp());//servaddr.sin_addr.s_addr = htonl(2130706433); //127.0.0.1

    int binding = bind (sock, (sockaddr *)&ad, sizeof(ad));
	std::cout << "bind = " << binding << std::endl;
	
	//int addrlen = sizeof(ad);
	
	listen(sock, 10);
	
	my_select();
}

void	Server::my_select()
{
	fd_set readyfdsRead, activefdsRead;
	fd_set readyfdsWrite, activefdsWrite;
	t_client clients[100];

	FD_ZERO(&readyfdsRead);
	FD_ZERO(&activefdsRead);
	FD_ZERO(&readyfdsWrite);
	FD_ZERO(&activefdsWrite);

	
	(void) clients;
	int	maxfd = sock;

	FD_SET (sock, &activefdsRead);

	while(1)
	{
		readyfdsRead = activefdsRead;
		readyfdsWrite = activefdsWrite;

		select(maxfd + 1, &readyfdsRead, &readyfdsWrite, NULL, NULL);

		for (int i = 0; i <= maxfd; i++)
		{
			if (!FD_ISSET(i, &readyfdsRead) && !FD_ISSET(i, &readyfdsWrite))
				continue;
			else if (FD_ISSET(i, &readyfdsRead))
			{
				if (i == sock)
				{
					new_socket = accept(sock, NULL,NULL);
					FD_SET (new_socket, &activefdsRead);
				
					if (new_socket > maxfd)
						maxfd = new_socket;
					
					clients[id++].fd = new_socket;
					std::cout  << std::endl << ">>>>>   New Client just arrived; " << "ID: " << id - 1 << "; FD: " << new_socket << std::endl; 
				}
				else
				{
					//int bytes = read(i, buffer, sizeof(buffer));
					read(i, buffer, sizeof(buffer));
					std::cout << std::endl;
					std::cout << "---BUFFER---" << std::endl;
					std::cout << buffer << std::endl;
					std::cout << "---BUFFER END ---" << std::endl << std::endl;
					/* if (bytes <= 0)
					{
						std::cout << "Client ID: " << id - 1 << " went \"a tomar por culo\"" << std::endl << std::endl;
						FD_CLR(i, &activefdsRead);
            			close(i);
					}
					else
					{ */
						std::cout << "Client ID: " << id - 1 << " pasa a la cola de WRITE!!!" << std::endl;
						FD_SET(i, &activefdsWrite);
						FD_CLR(i, &activefdsRead);
					//}
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
}			

void	Server::respond(int i)
{
	std::string request(buffer);
	if (request.find("GET /rey.jpg") != std::string::npos)
	//if (request.find("GET /rey.jpg") != std::string::npos)
	{
		std::ifstream file("pagina2/rey.jpg", std::ios::binary);
		//std::ifstream file("pagina2/rey.jpg", std::ios::binary);
    	if (!file.is_open()) 
		{
			std::cout << RED <<"goat.jpg NOT FOUND" << WHITE <<std::endl; 
       // Manejar el error, por ejemplo, enviar una respuesta 404 Not Found
   		} 
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
		std::ifstream file("anarchy.png", std::ios::binary);
		//std::ifstream file("pagina2/anarchy.png", std::ios::binary);
    	if (!file.is_open()) 
		{
			std::cout << RED <<"favicon.ico NOT FOUND" << WHITE <<std::endl; 
       // Manejar el error, por ejemplo, enviar una respuesta 404 Not Found
   		} 
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
		}
	}
    else
	{
		std::string httpResponse = "HTTP/1.1 200 OK\r\n"; // Línea de estado
   		httpResponse += "Content-Type: text/html\r\n"; // Encabezado Content-Type
    	httpResponse += "\r\n"; // Línea en blanco

    	// Código HTML como cuerpo de la respuesta
		std::cout << "Config::DirectoryIndex:" << Config::DirectoryIndex << std::endl;
    	file.open(Config::DirectoryIndex.c_str(), std::ios::in); ///LE METEMOS EL HTML...
    	if (!file.is_open()) 
		{
			std::cout << RED << Config::DirectoryIndex <<" NOT FOUND" << WHITE <<std::endl; 
       // Manejar el error, por ejemplo, enviar una respuesta 404 Not Found
   		} 
   		else 
		{
		std::stringstream buffer;
    	buffer << file.rdbuf();

    	// Convertir el contenido del stringstream en un string
    	httpResponse += buffer.str();
    	//std::cout << this->Config_data << std::endl;//para printear el contenido del archivo
    	file.close();
   
    	write(i, httpResponse.c_str(), httpResponse.size());
		}
	}
}

Server::~Server()
{
	close (sock);
	std::cout << "Server destructor called!" << std::endl;
}

