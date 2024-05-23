/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SimpleSocket.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoikoet <jgoikoet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 15:29:15 by jgoikoet          #+#    #+#             */
/*   Updated: 2024/05/20 13:26:50 by jgoikoet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SimpleSocket.hpp"

SimpleSocket::SimpleSocket(int domain, int service, int protocol, int port, u_long interface)
{
    std::cout << "---------SimpleSocket CONSTRUCTOR---------" << std::endl;
    
    //define address structure
    address.sin_family = domain;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = htonl(interface);

    //establish socket
    sock = socket(domain, service, protocol);
    test_connection(sock, "SimpleSocket test connection");
}

SimpleSocket::~SimpleSocket(){}

void SimpleSocket::test_connection(int item_to_test, std::string who)
{
    std::cout << who << ", item: " << item_to_test << std::endl;
    if (item_to_test < 0)
    {
        perror("Failed to connect Payaso...");
        exit (EXIT_FAILURE);
    }
}

sockaddr_in SimpleSocket::get_address()
{
    return address;
}

int SimpleSocket::get_sock()
{
    return sock;
}

/* void SimpleSocket::set_connection(int con)
{
    connection = con;
} */
