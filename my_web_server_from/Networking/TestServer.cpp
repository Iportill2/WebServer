/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TestServer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoikoet <jgoikoet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:54:13 by jgoikoet          #+#    #+#             */
/*   Updated: 2024/05/17 16:11:17 by jgoikoet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "TestServer.hpp"
#include <fstream>
#include <sstream>

TestServer::TestServer()
: SimpleServer (AF_INET, SOCK_STREAM, 0, 8080, INADDR_ANY, 10)
{
    launch();
}

void TestServer::accepter()
{
    struct sockaddr_in address = get_socket()->get_address();

    int addrlen = sizeof(address);
    new_socket= accept(get_socket()->get_sock(), (struct sockaddr *)&address, (socklen_t *)&addrlen);

    read(new_socket, buffer, 30000);
}

void TestServer::handler()
{
    std::cout << buffer << std::endl;
}

void TestServer::responder()
{   
    /* std::string httpResponse = "HTTP/1.1 200 OK\r\n"; // Línea de estado
    httpResponse += "Content-Type: text/plain\r\n"; // Encabezado Content-Type
    //httpResponse += "Content-Length: \r\n20"; // Encabezado Content-Length
    httpResponse += "\r\n"; // Línea en blanco
    httpResponse += "Hello, hijos de puta insinceros"; // Cuerpo de la respuesta (opcional)
    httpResponse += "\nMe cago en todo lo ke se menea";*/

	std::string request(buffer);
	if (request.find("GET /fary.jpg") != std::string::npos)
	{
		std::ifstream file("borat.jpg", std::ios::binary);
    	std::ostringstream oss;
    	oss << file.rdbuf();
		std::string fary = oss.str();
	
		std::string httpResponse = "HTTP/1.1 200 OK\r\n";
        httpResponse += "Content-Type: image/jpeg\r\n";
        //httpResponse += "Content-Length: " + std::to_string(fary.size()) + "\r\n";
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
	//std::string response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello from server";
}

void TestServer::launch()
{
    while(true)
    {
        std::cout << "==== WAITING ====" << std::endl;
            
        accepter();
        handler();
        responder();

        std::cout << "==== DONE ====" << std::endl;
    }
}