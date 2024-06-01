/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BindingSocket.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoikoet <jgoikoet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:53:06 by jgoikoet          #+#    #+#             */
/*   Updated: 2024/05/16 17:30:58 by jgoikoet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BindingSocket.hpp"


BindingSocket::BindingSocket(int domain, int service, int protocol, int port, u_long interface)
: SimpleSocket(domain, service, protocol, port, interface)
{
    std::cout << "---------BindingSocket CONSTRUCTOR---------" << std::endl;
    
    connect_to_network(get_sock(), get_address());
    test_connection(binding, "BindingSocket test connection");
}

void BindingSocket::connect_to_network(int sock, struct sockaddr_in address)
{
    binding = bind(sock, (struct sockaddr *)&address, sizeof(address));
}

int BindingSocket::get_binding()
{
    return binding;
}