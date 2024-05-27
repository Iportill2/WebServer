/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ListeningSocket.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoikoet <jgoikoet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:57:46 by jgoikoet          #+#    #+#             */
/*   Updated: 2024/05/17 18:49:01 by jgoikoet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ListeningSocket.hpp"

ListeningSocket::ListeningSocket(int domain, int service, int protocol, int port, u_long interface, int bklg)
: BindingSocket (domain, service, protocol, port, interface)
{
    std::cout << "---------ListeningSocket CONSTRUCTOR---------" << std::endl;
    
    backlog = bklg;
    start_listening();
}

void ListeningSocket::start_listening()
{
    int listening = listen(get_sock(), backlog);
    test_connection(listening, "ListeningSocket test connection");
}
