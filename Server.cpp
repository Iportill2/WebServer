/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoikoet <jgoikoet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:17:56 by jgoikoet          #+#    #+#             */
/*   Updated: 2024/06/19 11:43:19 by jgoikoet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

int Server::sign = 1;


bool Server::checkdefaultsettings(std::string ip,srv &s)
{
	if(s.ipAddressToipNum(ip) == false)
		return(std::cout << "s.ipAddressToipNum(ip)\n", false);
	if( directoryExists(s._Root) == false)
		return(std::cout << "directoryExists(s._Root)\n", false);
	if(directoryExists(s.arLoc[0]._location) == false)
		return(std::cout << "directoryExists(l1._location)\n", false);
	if(directoryExists(s.arLoc[0]._root) == false)
		return(std::cout << "directoryExists(l1._root)\n", false);
	if(fileExists(s.arLoc[0]._file) == false)
		return(std::cout << "fileExists(l1._file)\n", false);
	if(s.arLoc[0].methods_vector.size() != 1)
		return(std::cout << "l1.methods_vector.size() == 1\n",false);
	//std::cout << s.arLoc[1]._location << "\n";
	if(directoryExists(s.arLoc[1]._location) == false)
		return(std::cout << "directoryExists(l2._location) \n", false);
	if(directoryExists(s.arLoc[1]._root) == false)
		return(std::cout << "directoryExists(l2._root)\n",false);
	if(fileExists(s.arLoc[1]._file) == false)
		return(std::cout << "fileExists(l2._file)\n", false);
	if(s.arLoc[1].methods_vector.size() != 2)
		return(std::cout << "l2.methods_vector.size() == 2\n",false);
	
	std::cout << RED << "bool Server::checkdefaultsettings(std::string ip,srv &s)" << GREEN <<  "OK!\n" << WHITE ;
	return(true);
}
bool Server::directoryExists(const std::string& dirName) 
{
    struct stat info;
    if (stat(dirName.c_str(), &info) != 0) 
        return false;// No se puede acceder al directorio
    else if (info.st_mode & S_IFDIR)
        return true;// Es un directorio
    else
    	return false;// Existe, pero no es un directorio
}
bool Server::fileExists(const std::string& filename) 
{
    std::ifstream file(filename.c_str());
    return file.good();
}

Server::Server()
{
	signal(SIGINT, signalHandler);
	signal(SIGTERM, &signalHandler);
	
	srv s;
	Location l1;
	Location l2;
	std::string ip = "0.0.0.0";
	s._server_name = "localhost";
	s.ipAddressToipNum(ip.c_str());
	s._sizetPort = 8080;
	s._sizetBody = 563218;
	s._Root = "./pagina";

	l1._location = "/";
	l1._root = "./pagina";
	l1._file = "index.html";
	l1.methods_vector.push_back("get");
	s.arLoc.push_back(l1);

	l2._location = "./pepe";//// estaba /pepe  y no funcionaba
	l2._root = "./pagina/pepe";
	l2._file = "index.html";
	l2.methods_vector.push_back("get");
	l2.methods_vector.push_back("post");
	s.arLoc.push_back(l2);
	
	servers.push_back(s);

	if(checkdefaultsettings(ip.c_str(),s) == 1)
	{
		printServers();
		serverSet();
		Mselect();
									
	}
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
		//fcntl(soc, F_SETFL, O_NONBLOCK);
		
		if (bind (soc, (sockaddr *)&address, sizeof(address)) == -1)
			std::cout << "Puerto ocupau atontau" << std::endl;

		listen(soc, 10);
	
		serversMap[soc] = i;
		maxFD = soc;
		sizeOfAddress = sizeof(address);
		
		//std::cout << "MONTAMOS  SERVER " << i + 1  << " PUERTO " << servers[i]._sizetPort << " fd " << soc << std::endl;
	}
	/* std::map<int, int>::iterator i = serversMap.begin();
	std::map<int, int>::iterator o = serversMap.end();

	while (i != o)
	{
		std::cout << "socket: " << i->first << " -> Server: " << i->second << " -> server name: " << servers[i->second]._server_name << std::endl;
		i++;
	} */
	//std::cout << std::endl;
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
	
	while(sign)
	{
		FD_ZERO(&readyfdsRead);
		FD_ZERO(&readyfdsWrite);
		readyfdsRead = activefdsRead;
		readyfdsWrite = activefdsWrite;

		std::cout << "------------------SELECT------------------" << std::endl;
		
    	timeout.tv_sec = 0;
    	timeout.tv_usec = 500000;
		int sel = select(maxFD + 1, &readyfdsRead, &readyfdsWrite, NULL, &timeout);

		//std::cout << "sel = " << sel << std::endl;
		if (sel == 0)
		{
			FD_ZERO(&activefdsRead);
			FD_ZERO(&activefdsWrite);
			
			//std::cout << "comfs size = " << comFds.size() << std::endl;
			for (size_t c = 0; c < comFds.size(); c++)
			{
				//std::cout << "c = " << comFds[c] << std::endl;
				close(comFds[c]);
			}
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
				std::cout << "Select selecciona fd de lectura " << i <<  std::endl;
				int isServerSock = 0;
				
				std::map<int, int>::iterator it = serversMap.begin();
				std::map<int, int>::iterator out = serversMap.end();
		
				while (it != out)
				{
					//std::cout << "Mira si el fd " << i << " es una llamada " << std::endl;
					//std::cout << "it->first = " << it->first << std::endl;
					if (i == it->first)
					{
						int newSocket = accept(i, (struct sockaddr *)&ad, (socklen_t*)&sizeOfAddress);
						//fcntl(newSocket, F_SETFL, O_NONBLOCK);
						FD_SET (newSocket, &activefdsRead);
						readMap[newSocket] = it->first;
						comFds.push_back(newSocket);
						if (newSocket > maxFD)
							maxFD = newSocket;
						isServerSock = 1;
						std::cout << "el fd " << i << " es una llamada, crea socket de comunicacion " << newSocket << std::endl;
						i = maxFD + 1;
						break;
					}
					it++;
				}
				if (!isServerSock)
				{
					std::cout << "No es llamada es comunicacion, lee la peticion del socket " << i << std::endl;
					memset(buffer, 0, sizeof(buffer));
					int bytes = read(i, buffer, sizeof(buffer));
					std::cout << std::endl << BLUE << buffer << WHITE << std::endl << std::endl;
					if (bytes <= 0)
					{
						std::cout << "fd " << i << " went \"a tomar por culo\"" << std::endl << std::endl;
						FD_CLR(i, &activefdsRead);
						readMap.erase(i);
            			close(i);
						i = maxFD + 1;
					}
					else
					{ 
						std::cout << "fd " << i << " pasa a la cola de WRITE!!!" << std::endl;
						Request * r = new Request(buffer);
						rq[i] = r;
						FD_SET(i, &activefdsWrite);
						FD_CLR(i, &activefdsRead);
						i = maxFD + 1;
					}
				}
			}
			else if (FD_ISSET(i, &readyfdsWrite))
			{
				std::cout << "Select selecciona fd de escritura " << i << " y es respondido!!!" << std::endl;
				Respond(i);
				close (i);
				readMap.erase(i);
				FD_CLR(i, &activefdsWrite);
				i = maxFD + 1;
			}
		}
	}
}
void	Server::Respond(int i)
{
	Respons r(rq[i], servers[serversMap[readMap[i]]], i);
	r.printRequest();
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
		//std::cout << "FD " << iti->first << std::endl;

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

