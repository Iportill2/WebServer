/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConnectingSocket.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoikoet <jgoikoet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 17:29:21 by jgoikoet          #+#    #+#             */
/*   Updated: 2024/05/13 16:48:34 by jgoikoet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "SimpleSocket.hpp"

namespace HDE
{
    class ConnectingSocket: public SimpleSocket
    {
        public:

            ConnectingSocket(int domain, int service, int protocol, int port, u_long interface);

            void connect_to_network(int sock, struct sockaddr_in address);
    };
}