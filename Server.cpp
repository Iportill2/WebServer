/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoikoet <jgoikoet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:17:56 by jgoikoet          #+#    #+#             */
/*   Updated: 2024/06/06 12:54:30 by jgoikoet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

int Server::sign = 1;

Server::Server(): port (8080)
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

	//std::cout << "size of address: " << sizeof(ad) << std::endl;

    if (bind (sock, (sockaddr *)&ad, sizeof(ad)) == -1)
		std::cout << "Puerto ocupau atontau" << std::endl;
	
	
	listen(sock, 10);
	
	my_select();
}

Server::Server(std::vector<srv> & srv) : servers(srv)
{
	signal(SIGINT, signalHandler);
	signal(SIGTERM, &signalHandler);
	serverSet();
	Mselect();
}

void	Server::serverSet()
{
	int option = 1;
	int puertoProvisional = 8080;
	
	std::cout << "servers size "  << servers.size() << std::endl;
	
	for(size_t i = 0; i < servers.size(); i++)
	{
		sockaddr_in	address;
		address.sin_family = AF_INET;
    	address.sin_port = htons(puertoProvisional++);
    	address.sin_addr.s_addr = htonl(INADDR_ANY);
	
		//std::cout << "size of address: " << sizeof(address) << std::endl;

		int	soc = socket(AF_INET, SOCK_STREAM, 0);
		setsockopt(soc, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &option, sizeof(option));
		
		if (bind (soc, (sockaddr *)&address, sizeof(address)) == -1)
			std::cout << "Puerto ocupau atontau" << std::endl;

		listen(soc, 10);
	
		serversMap[soc] = i;
		maxFD = sock;
		sizeOfAddress = sizeof(address);
	}
	std::map<int, int>::iterator i = serversMap.begin();
	std::map<int, int>::iterator o = serversMap.end();

	while (i != o)
	{
		std::cout << "socket: " << i->first << " -> Server: " << i->second << " -> server name: " << servers[i->second]._server_name << std::endl;
		i++;
	}
	
}

void	Server::Mselect()
{
	fd_set readyfdsRead, activefdsRead;
	fd_set readyfdsWrite, activefdsWrite;

	FD_ZERO(&readyfdsRead);
	FD_ZERO(&activefdsRead);
	FD_ZERO(&readyfdsWrite);
	FD_ZERO(&activefdsWrite);

	std::map<int, int>::iterator i = serversMap.begin();
	std::map<int, int>::iterator o = serversMap.end();

	while (i != o)
	{
		FD_SET (i->first, &activefdsRead);
		i++;
	}
	
	while(sign)
	{
		readyfdsRead = activefdsRead;
		readyfdsWrite = activefdsWrite;

		select(maxFD + 1, &readyfdsRead, &readyfdsWrite, NULL, NULL);

		if (!sign)
			break;
		for (int i = 0; i <= maxFD; i++)
		{
			if (!FD_ISSET(i, &readyfdsRead) && !FD_ISSET(i, &readyfdsWrite))
				continue;
			if (FD_ISSET(i, &readyfdsRead))
			{
				for
			}
		}
	}
}

void	Server::my_select()
{
	fd_set readyfdsRead, activefdsRead;
	fd_set readyfdsWrite, activefdsWrite;
	t_client clients[100];
	
	int addrlen = sizeof(ad);
	//std::cout << "size of address: " << sizeof(ad) << std::endl;
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
		close(i);
}			

void	Server::respond(int i)
{
	Response r(rq[i], conf, i);
	r.printRequest();
	r.printConf();
	r.createResponse();
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
	c.root = "./pagina/pagina2";
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

