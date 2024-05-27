/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TestServer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoikoet <jgoikoet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:54:13 by jgoikoet          #+#    #+#             */
/*   Updated: 2024/05/14 12:33:31 by jgoikoet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "TestServer.hpp"

HDE::TestServer::TestServer()
: SimpleServer (AF_INET, SOCK_STREAM, 0, 8080, INADDR_ANY, 10)
{
    launch();
}

void HDE::TestServer::accepter()
{
    struct sockaddr_in address = get_socket()->get_address();

    int addrlen = sizeof(address);
    new_socket= accept(get_socket()->get_sock(), (struct sockaddr *)&address, (socklen_t *)&addrlen);

    read(new_socket, buffer, 30000);
}

void HDE::TestServer::handler()
{
    std::cout << buffer << std::endl;
}

void HDE::TestServer::responder()
{
    std::string hello = "Hello from server motherfuckers";
    
    write(new_socket, &hello, hello.size());
}

void HDE::TestServer::launch()
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