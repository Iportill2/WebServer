/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoikoet <jgoikoet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:17:56 by jgoikoet          #+#    #+#             */
/*   Updated: 2024/08/22 17:22:56 by jgoikoet         ###   ########.fr       */
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

	s._server_name = "localhost";
	s.ipAddressToipNum("0.0.0.0");
	s._sizetPort = 8090;
	s._sizetBody = 10000;
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
	serverSet();
	Mselect();
}

Server::Server(std::vector<srv> & srv) : servers(srv)
{
	signal(SIGINT, signalHandler);
	signal(SIGTERM, &signalHandler);
	printServers();
	serverSet();
	Mselect();
}

void	Server::serverSet()
{
	int option = 1;
	
	//std::cout << "servers size "  << servers.size() << std::endl;
	
	for(size_t i = 0; i < servers.size(); i++)
	{
		sockaddr_in	address;
		address.sin_family = AF_INET;
    	address.sin_port = htons(servers[i]._sizetPort);
    	address.sin_addr.s_addr = htonl(servers[i]._ipNum);
	
		int	soc = socket(AF_INET, SOCK_STREAM, 0);
		setsockopt(soc, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &option, sizeof(option));
		
		if (bind (soc, (sockaddr *)&address, sizeof(address)) == -1)
			std::cout << "Puerto ocupau atontau" << std::endl;

		listen(soc, 10);
	
		serversMap[soc] = i;
		maxFD = soc;
		
		sizeOfAddress = sizeof(address);
		
		//std::cout << "MONTAMOS  SERVER " << i + 1  << " PUERTO " << servers[i]._sizetPort << " fd " << soc << std::endl;
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
	
	struct timeval timeout;
	
	//------------------------------------
	
	while(sign)
	{
		FD_ZERO(&readyfdsRead);
		FD_ZERO(&readyfdsWrite);
		readyfdsRead = activefdsRead;
		readyfdsWrite = activefdsWrite;

		//std::cout  << "👾 " << std::flush;
		
    	timeout.tv_sec = 0;
    	timeout.tv_usec = 500000;
		int sel = select(maxFD + 1, &readyfdsRead, &readyfdsWrite, NULL, &timeout);

		if (sel == 0)
		{
			FD_ZERO(&activefdsRead);
			FD_ZERO(&activefdsWrite);
			
			for (size_t c = 0; c < comFds.size(); c++)
				close(comFds[c]);
			comFds.clear();
			std::map<int, int>::iterator i = serversMap.begin();
			std::map<int, int>::iterator o = serversMap.end();

			while (i != o)
			{
				FD_SET (i->first, &activefdsRead);
				i++;
			}
		}

		if (!sign)
			break;

		for (int i = 0; i <= maxFD; i++)
		{
			if (!FD_ISSET(i, &readyfdsRead) && !FD_ISSET(i, &readyfdsWrite))
				continue;
				
			if (FD_ISSET(i, &readyfdsRead))
			{
				std::cout << std::endl << "Select selecciona fd de lectura " << i <<  std::endl;
				isServerSock = 0;
				
				std::map<int, int>::iterator it = serversMap.begin();
				std::map<int, int>::iterator out = serversMap.end();
		
				while (it != out)
				{
					std::cout << std::endl << "Mira si el fd " << i << " es una llamada " << std::endl;
					if (i == it->first)
					{
						int newSocket = accept(i, (struct sockaddr *)&ad, (socklen_t*)&sizeOfAddress);
						//fcntl(newSocket, F_SETFL, O_NONBLOCK);
						
						Request * r = new Request;
						rq[newSocket] = r;
						
						FD_SET (newSocket, &activefdsRead);
						readMap[newSocket] = it->first;
						comFds.push_back(newSocket);
						if (newSocket > maxFD)
							maxFD = newSocket;
						isServerSock = 1;
						std::cout << std::endl << "el fd " << i << " es una llamada, crea socket de comunicacion " << newSocket << std::endl;
						i = maxFD + 1;
						
						break;
					}
					it++;
				}
				if (!isServerSock)
				{
					std::cout << std::endl << GREEN <<"No es llamada es comunicacion, LEE la peticion del socket " << i << WHITE << std::endl;
					
					memset(buffer, 0, sizeof(buffer));
                    int bytes = recv(i, buffer, sizeof(buffer) - 1, 0);
					fcntl(i, F_SETFL, O_NONBLOCK);
					std::cout << "bytes: " << bytes << std::endl;
					
					
					if (bytes > 0)
					{
						rq[i]->addBuffer(buffer, bytes);
						rq[i]->firstRead = false;
					}
					if (rq[i]->getBoundary().empty() || rq[i]->part.find(rq[i]->boundaryEnd) != std::string::npos)
					{
						std::cout << "LA BOLA ENTRO" << std::endl;
						rq[i]->parse();
						FD_SET(i, &activefdsWrite);
						FD_CLR(i, &activefdsRead);
						std::cout << std::endl << "fd " << i << " pasa a la cola de WRITE!!!" << std::endl;
					}
					i = maxFD + 1;
				}
			}
			else if (FD_ISSET(i, &readyfdsWrite))
			{
				std::cout << std::endl << GREEN << "Select selecciona fd de escritura " << i << " y es respondido!!!" << WHITE << std::endl;
				Respond(i);
				rq.erase(i);
				readMap.erase(i);
				FD_CLR(i, &activefdsWrite);
				close (i);
				i = maxFD + 1;
				std::cout << "......................................." << std::endl;
				std::cout << "......................................." << std::endl;
				//std::cout << "Requests activas: " << rq.size() << std::endl;
				std::cout << "......................................." << std::endl;
				std::cout << "......................................." << std::endl;
				std::cout << "......................................." << std::endl;
			}
		}
	}
}
void	Server::Respond(int i)
{
	Respons r(rq[i], servers[serversMap[readMap[i]]], i);
	//r.printRequest();
	//r.printConf();
	r.createRespons();
}

Server::~Server()
{
	//std::cout << "Server destructor called!" << std::endl;
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
		iti->second->printRequest();
		iti++;
	}
}

void Server::printServers()
{
	for (size_t i = 0; i < servers.size(); i++)
	{
		std::cout << GREEN << "----SERVER  " << i + 1 << "-------------------------" << WHITE << std::endl;
		std::cout << "server name : " << "\"" << servers[i]._server_name  << "\"" << std::endl;
		std::cout << "ip_num: " << "\"" << servers[i]._ipNum  << "\"" << std::endl;
		std::cout << "port: " << "\"" << servers[i]._sizetPort  << "\"" << std::endl;
		std::cout << "body size: " << "\"" << servers[i]._sizetBody  << "\"" << std::endl;
		std::cout << "root: " << "\"" << servers[i]._Root  << "\"" << std::endl;
		
		std::cout << std::endl;
		for (size_t j = 0; j < servers[i].arLoc.size(); j++)
		{
			std::cout << YELLOW << "-----Location  " << WHITE << "\"" << servers[i].arLoc[j]._location  << "\"" << std::endl;
			std::cout << "root " << "\"" << servers[i].arLoc[j]._root  << "\"" << std::endl;
			std::cout << "file " << "\"" << servers[i].arLoc[j]._file  << "\"" << std::endl;
			std::cout << "redirect " << "\"" << servers[i].arLoc[j]._redirect  << "\"" << std::endl;
			std::cout << "cgi " << "\"" << servers[i].arLoc[j]._cgi  << "\"" << std::endl;
			for (size_t k = 0; k < servers[i].arLoc[j].methods_vector.size(); k++)
				std::cout << "method " << k + 1 << " : " << "\"" <<servers[i].arLoc[j].methods_vector[k] << "\"" << std::endl;
			std::cout << std::endl;
		}
		//std::cout << MAGENTA << "--------------------------------------" << WHITE <<std::endl;
	}
}

