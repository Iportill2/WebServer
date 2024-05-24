/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoikoet <jgoikoet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:17:56 by jgoikoet          #+#    #+#             */
/*   Updated: 2024/05/21 15:59:46 by jgoikoet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
//cheackea el read y nbytes

Server::Server(int prt): port (prt)
{
	std::cout << "Server constructor called!" << std::endl;
	
	sock = socket(AF_INET, SOCK_STREAM, 0);
	
	sockaddr_in	ad;
	ad.sin_family = AF_INET;
    ad.sin_port = htons(port);
    ad.sin_addr.s_addr = htonl(INADDR_ANY);

    int binding = bind (sock, (sockaddr *)&ad, sizeof(ad));
	std::cout << "bind = " << binding << std::endl;
	
	int addrlen = sizeof(ad);
	
	listen(sock, 10);
	
	while (1)
	{
		std::cout << "Escuchandolooo" << std::endl;
		new_socket = accept(sock, (sockaddr *)&ad, (socklen_t *)&addrlen);
		std::cout << "----escuchao-----" << std::endl;
		read(new_socket, buffer, 30000);//
		std::cout << buffer << std::endl;
		respond();
	}
}

void Server::respond()
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

        write(new_socket, httpResponse.c_str(), httpResponse.size());
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
   
    	write(new_socket, httpResponse.c_str(), httpResponse.size());
	}
	
    close(new_socket);
}

Server::~Server()
{
	close (sock);
	std::cout << "Server destructor called!" << std::endl;
}