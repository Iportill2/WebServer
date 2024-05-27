/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConnectingSocket.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoikoet <jgoikoet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 17:29:09 by jgoikoet          #+#    #+#             */
/*   Updated: 2024/05/16 17:30:58 by jgoikoet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ConnectingSocket.hpp"

ConnectingSocket::ConnectingSocket(int domain, int service, int protocol, int port, u_long interface)
: SimpleSocket(domain, service, protocol, port, interface)
{
    std::cout << "---------ConnectingSocket CONSTRUCTOR---------" << std::endl;
    
    connect_to_network(get_sock(), get_address());
    test_connection(123, "ConnectingSocket test connection");
}

void ConnectingSocket::connect_to_network(int sock, struct sockaddr_in address)
{
    connect(sock, (struct sockaddr *)&address, sizeof (address));
}