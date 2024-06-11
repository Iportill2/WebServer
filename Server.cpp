/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoikoet <jgoikoet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:17:56 by jgoikoet          #+#    #+#             */
/*   Updated: 2024/06/11 13:35:34 by jgoikoet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

int Server::sign = 1;

Server::Server()
{
	signal(SIGINT, signalHandler);
	signal(SIGTERM, &signalHandler);
	
	srv s;
	Location l1;
	Location l2;

	s.ipAddressToipNum("0.0.0.0");
	s._sizetPort = 8080;
	s._sizetBody = 100000;
	s._Root = "./pagina";

	l1._location = "/";
	l1._root = "./pagina";
	l1._file = "index.html";
	l1.methods_vector.push_back("get");
	s.arLoc.push_back(l1);

	l2._location = "/pepe";
	l2._root = "./pagina/pepe";
	l2._file = "index.html";
	l2.methods_vector.push_back("get");
	l2.methods_vector.push_back("post");
	s.arLoc.push_back(l2);
	
	servers.push_back(s);

	printServers();
	//my_select();
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
	

		int	soc = socket(AF_INET, SOCK_STREAM, 0);
		setsockopt(soc, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &option, sizeof(option));
		
		if (bind (soc, (sockaddr *)&address, sizeof(address)) == -1)
			std::cout << "Puerto ocupau atontau" << std::endl;

		listen(soc, 10);
	
		serversMap[soc] = i;
		maxFD = soc;
		sizeOfAddress = sizeof(address);
		
		std::cout << "MONTAMOS  SERVER " << i + 1  << " PUERTO " << puertoProvisional - 1 << " fd " << soc << std::endl;
	}
	std::map<int, int>::iterator i = serversMap.begin();
	std::map<int, int>::iterator o = serversMap.end();

	while (i != o)
	{
		std::cout << "socket: " << i->first << " -> Server: " << i->second << " -> server name: " << servers[i->second]._server_name << std::endl;
		i++;
	}
	std::cout << std::endl;
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
		//std::cout << "MAX FD " << maxFD << std::endl;
		for (int i = 0; i <= maxFD; i++)
		{
			if (!FD_ISSET(i, &readyfdsRead) && !FD_ISSET(i, &readyfdsWrite))
				continue;
				
			if (FD_ISSET(i, &readyfdsRead))
			{
				std::cout << "Select selecciona fd de lectura " << i <<  std::endl;
				int isServerSock = 0;
				
				std::map<int, int>::iterator it = serversMap.begin();
				std::map<int, int>::iterator out = serversMap.end();
				while (it != out)
				{
					std::cout << "it->first " << it->first << " it->second " << it->second << std::endl;
					it++;
				}
				it = serversMap.begin();
				while (it != out)
				{
					std::cout << "Mira si el fd " << i << " es una llamada " << std::endl;
					//std::cout << "it->first = " << it->first << std::endl;
					if (i == it->first)
					{
						int newSocket = accept(i, (struct sockaddr *)&ad, (socklen_t*)&sizeOfAddress);
						FD_SET (newSocket, &activefdsRead);
						readMap[newSocket] = it->first;
						if (new_socket > maxFD)
							maxFD = newSocket;
						isServerSock = 1;
						std::cout << "el fd " << i << " es una llamada, crea socket de comunicacion " << newSocket << std::endl;
						break;
					}
					it++;
				}
				if (!isServerSock)
				{
					std::cout << "No es llamada es comunicacion, lee la peticion del socket " << i << std::endl;
					memset(buffer, 0, sizeof(buffer));
					int bytes = read(i, buffer, sizeof(buffer));
					//std::cout << "i = " << i <<  std::endl;
					//exit(1);
					std::cout << "bytes leidos: " << bytes << std::endl;
					if (bytes <= 0)
					{
						std::cout << "Client ID: " << id - 1 << " went \"a tomar por culo\"" << std::endl << std::endl;
						FD_CLR(i, &activefdsRead);
						readMap.erase(i);
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
				std::cout << "Select selecciona fd de escritura " << i <<  std::endl;
				std::cout << "Se envia respuesta al socket " << i << std::endl << std::endl;
				Respond(i);
				close (i);
				readMap.erase(i);
				FD_CLR(i, &activefdsWrite);
			}
		}
	}
}

void	Server::Respond(int i)
{
	Respons r(rq[i], servers[serversMap[readMap[i]]], i);
	r.printRequest();
	r.printConf();
	r.createRespons();
}

void	Server::respond(int i)
{
	Response r(rq[i], conf, i);
	//r.printRequest();
	//r.printConf();
	r.createResponse();
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

void Server::printServers()
{
	for (size_t i = 0; i < servers.size(); i++)
	{
		std::cout << "----SERVER  " << i + 1 << "-------" << std::endl;
		std::cout << "ip_num: " << "\"" << servers[i]._ipNum  << "\"" << std::endl;
		std::cout << "port: " << "\"" << servers[i]._sizetPort  << "\"" << std::endl;
		std::cout << "body size: " << "\"" << servers[i]._sizetBody  << "\"" << std::endl;
		std::cout << "root: " << "\"" << servers[i]._Root  << "\"" << std::endl;
		
		std::cout << std::endl;
		for (size_t j = 0; j < servers[i].arLoc.size(); j++)
		{
			std::cout << "-----Location  " << "\"" << servers[i].arLoc[j]._location  << "\"" << std::endl;
			std::cout << "root " << "\"" << servers[i].arLoc[j]._root  << "\"" << std::endl;
			std::cout << "file " << "\"" << servers[i].arLoc[j]._file  << "\"" << std::endl;
			for (size_t k = 0; k < servers[i].arLoc[j].methods_vector.size(); k++)
				std::cout << "method " << k + 1 << " : " << "\"" <<servers[i].arLoc[j].methods_vector[k] << "\"" <<std::endl;
			std::cout << std::endl;
		}
		
	}
}

