/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoikoet <jgoikoet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:17:56 by jgoikoet          #+#    #+#             */
/*   Updated: 2024/06/05 12:19:11 by jgoikoet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

int Server::sign = 1;

Server::Server(int prt): port (prt)
{
	setLoc();
	printLoc();
	
	id = 0;

	signal(SIGINT, signalHandler);
	signal(SIGTERM, &signalHandler);
	
	sock = socket(AF_INET, SOCK_STREAM, 0);

	int option = 1;
	
	//(setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option)) == -1); // el de iban
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &option, sizeof(option));
	
	std::cout << "Server constructor called! PORT: " << port;
	std::cout << " sockfd: " << sock << std::endl;
	
	ad.sin_family = AF_INET;
    ad.sin_port = htons(port);
    ad.sin_addr.s_addr = htonl(INADDR_ANY);

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

		select(maxfd + 1, &readyfdsRead, &readyfdsWrite, NULL, NULL);
		//int s = select(maxfd + 1, &readyfdsRead, &readyfdsWrite, NULL, NULL);

		//std::cout << "sign = " << sign << std::endl;
		//std::cout << "select = " << s << std::endl;
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
					FD_SET (new_socket, &activefdsRead);
				
					if (new_socket > maxfd)
					{
						maxfd = new_socket;
						//maxFD = new_socket;
					}
					
					clients[id++].fd = new_socket;
					std::cout  << std::endl << ">>>>>   New Client just arrived; " << "ID: " << id - 1 << "; FD: " << new_socket << std::endl; 
				}
				else
				{
					memset(buffer, 0, sizeof(buffer));
					int bytes = read(i, buffer, sizeof(buffer));
					//read(i, buffer, sizeof(buffer));
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
						
						Request * r = new Request(buffer);
						rq[i] = r;
						//printRequest();
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
		//std::cout << "cerrando fd: " << i << std::endl;
		//int  stat = close(i);
		close(i);
		//std::cout << "status fd " << i << " = " <<  stat << std::endl;
	}
}			

void	Server::respond(int i)
{
	Response r(rq[i], conf, i);
	r.printRequest();
	r.printConf();
	r.createResponse();
	/* std::string request(buffer);
	if (request.find("GET /fary.jpg") != std::string::npos)
	{
		std::ifstream file("pagina/rey.jpg", std::ios::binary);
    	std::ostringstream oss;
    	oss << file.rdbuf();
		std::string fary = oss.str();
	
		std::string httpResponse = "HTTP/1.1 200 OK\r\n";
        httpResponse += "Content-Type: image/jpeg\r\n";
        httpResponse += "\r\n";
        httpResponse += fary;

        write(i, httpResponse.c_str(), httpResponse.size());
	}
	else if (request.find("GET /favicon.ico") != std::string::npos)
	{
		std::ifstream file("pagina/anarchy.png", std::ios::binary);
    	std::ostringstream oss;
    	oss << file.rdbuf();
		std::string favi = oss.str();
	
		std::string httpResponse = "HTTP/1.1 200 OK\r\n";
        httpResponse += "Content-Type: image/png\r\n";
        httpResponse += "\r\n";
        httpResponse += favi;

        write(i, httpResponse.c_str(), httpResponse.size());
	}
    else
	{
		std::string httpResponse = "HTTP/1.1 200 OK\r\n";
   		httpResponse += "Content-Type: text/html\r\n";
    	httpResponse += "\r\n";

		std::ifstream file;
		file.open("pagina/index.html", std::ios::in);
    	if (!file.is_open()) 
			std::cout << RED  <<" NOT FOUND" << WHITE <<std::endl; 
   		else 
		{
			std::stringstream buffer;
    		buffer << file.rdbuf();
    		httpResponse += buffer.str();
    		file.close();
		}
    	write(i, httpResponse.c_str(), httpResponse.size());
	} */
}

Server::~Server()
{
	std::cout << "Server destructor called!" << std::endl;
	close (sock);
	
	std::map<int, Request *>::iterator iti;
	std::map<int, Request *>::iterator ito;
	
	iti = rq.begin();
	ito = rq.end();

	while(iti != ito)
	{
		
		delete(iti->second);
		iti++;
	}
}

int  Server::get_maxfd()
{
	return id;
}

void	Server::signalHandler(int i)
{
	(void)i;
	std::cout << std::endl << "crtl + c pulsado. cerramos puerto italiano al pie de las montañas" << std::endl;
	sign = 0;
}

//FUNCIONES PARA PRUEBAS------------------------------------------

void Server::printRequest()
{
	std::map<int, Request *>::iterator iti;
	std::map<int, Request *>::iterator ito;
	
	iti = rq.begin();
	ito = rq.end();

	while(iti != ito)
	{
		std::cout << "FD " << iti->first << std::endl;
		iti->second->printRequest();
		iti++;
	}
}

void Server::setLoc()
{
	loc a;
	loc b;
	loc c;

	a.file = "index.html";
	a.root = "./pagina";
	a.methods.push_back("GET");
	a.methods.push_back("POST");

	b.file = "rey.jpg";
	b.root = "./pagina";
	b.methods.push_back("GET");

	c.file = "index.html";
	c.root = "./pagina2";
	c.methods.push_back("GET");

	conf.host = "0.0.0.0";
	conf.port = 8080;
	conf.server_name = "localhost";
	conf.body_size =10000;
	conf.location["/"] = a;
	conf.location["/fary.jpg"] = b;
	conf.location["/pagina2"] = c;
	
}

void Server::printLoc()
{
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

