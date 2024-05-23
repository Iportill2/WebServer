/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ListeningSocket.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoikoet <jgoikoet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:57:46 by jgoikoet          #+#    #+#             */
/*   Updated: 2024/05/16 17:30:58 by jgoikoet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ListeningSocket.hpp"

ListeningSocket::ListeningSocket(int domain, int service, int protocol, int port, u_long interface, int bklg)
: BindingSocket (domain, service, protocol, port, interface)
{
    std::cout << "---------ListeningSocket CONSTRUCTOR---------" << std::endl;
    
    backlog = bklg;
    start_listening();
    test_connection(listening, "ListeningSocket test connection");
}

void ListeningSocket::start_listening()
{
    listening = listen(get_sock(), backlog);
}

int ListeningSocket::get_listening()
{
    return listening;
}

int ListeningSocket::get_backlog()
{
    return backlog;
}