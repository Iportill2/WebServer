/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoikoet <jgoikoet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:17:56 by jgoikoet          #+#    #+#             */
/*   Updated: 2024/05/24 19:00:03 by jgoikoet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

int Server::sign = 1;

Server::Server(int prt): port (prt)
{
	
	id = 0;

	signal(SIGINT, signalHandler);
	//signal(SIGTERM, &signalHandler)
	
	sock = socket(AF_INET, SOCK_STREAM, 0);
	
	std::cout << "Server constructor called! PORT: " << port;
	std::cout << " sock:" << sock << std::endl;
	sockaddr_in	ad;
	ad.sin_family = AF_INET;
    ad.sin_port = htons(port);
    ad.sin_addr.s_addr = htonl(INADDR_ANY);

    while (bind (sock, (sockaddr *)&ad, sizeof(ad)) == -1)
	{
		std::cout << "Puerto ocupau atontau" << std::endl;
		exit(1);
	}
	
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

	while(sign)
	{
		//std::cout << "sign = " << sign << std::endl;
		readyfdsRead = activefdsRead;
		readyfdsWrite = activefdsWrite;

		int s = select(maxfd + 1, &readyfdsRead, &readyfdsWrite, NULL, NULL);

		std::cout << "select = " << s << std::endl;
		if (s == -1)
			exit(1);

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
					{
						maxfd = new_socket;
						//maxFD = new_socket;
					}
					
					clients[id++].fd = new_socket;
					std::cout  << std::endl << ">>>>>   New Client just arrived; " << "ID: " << id - 1 << "; FD: " << new_socket << std::endl; 
				}
				else
				{
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
	
}			

void	Server::respond(int i)
{
	std::string request(buffer);
	if (request.find("GET /fary.jpg") != std::string::npos)
	{
		std::ifstream file("rey.jpg", std::ios::binary);
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
		std::ifstream file("anarchy.png", std::ios::binary);
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
		std::string httpResponse = "HTTP/1.1 200 OK\r\n"; // Línea de estado
   		httpResponse += "Content-Type: text/html\r\n"; // Encabezado Content-Type
    	httpResponse += "\r\n"; // Línea en blanco

    	// Código HTML como cuerpo de la respuesta
   		httpResponse += "<!DOCTYPE html>\n";
    	httpResponse += "<html lang=\"es\">\n";
   		httpResponse += "<head>\n";
   		httpResponse += "    <meta charset=\"UTF-8\">\n";
    	httpResponse += "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n";
    	httpResponse += "    <title>Respuesta del Servidor</title>\n";
    	httpResponse += "</head>\n";
    	httpResponse += "<body>\n";
    	httpResponse += "    <header>\n";
    	httpResponse += "        <h1>Buenas tarde y biesvenido a mis pagina güe </h1>\n";
   		httpResponse += "    </header>\n";
    	httpResponse += "    <main>\n";
    	httpResponse += "        <section>\n";
    	httpResponse += "            <h2>Mensaje de Dios:</h2>\n";
    	httpResponse += "            <p>Hello, hijos de puta insinceros,</p>\n";
    	httpResponse += "            <p>me cago en todo lo que se menea.</p>\n";
		httpResponse += "            <img src=\"fary.jpg\" alt=\"Dios en la tierra\">\n";
    	httpResponse += "        </section>\n";
    	httpResponse += "    </main>\n";
    	httpResponse += "    <footer>\n";
    	httpResponse += "        <p>&copy; 2024. Todos los derechos reservados.</p>\n";
    	httpResponse += "    </footer>\n";
    	httpResponse += "</body>\n";
    	httpResponse += "</html>\n";
   
    	write(i, httpResponse.c_str(), httpResponse.size());
	}
}

Server::~Server()
{
	close (sock);
	std::cout << "Server destructor called!" << std::endl;
}

int  Server::get_maxfd()
{
	return id;
}

void	Server::signalHandler(int i)
{
	(void)i;
	std::cout << std::endl << "crtl + c pulsado. cerramos puerto italiano al pie de las montañas" << std::endl;
	close(3);
    //exit(1);
}