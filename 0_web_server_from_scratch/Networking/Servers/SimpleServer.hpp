/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SimpleServer.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoikoet <jgoikoet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:16:40 by jgoikoet          #+#    #+#             */
/*   Updated: 2024/05/13 18:17:51 by jgoikoet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdelibc-networking.hpp"
#include <unistd.h>

namespace HDE
{
	//class ListeningSocket;
    class SimpleServer
    {
        private:

            ListeningSocket * socket;

            virtual void    accepter() = 0;
            virtual void    handler() = 0;
            virtual void    responder() = 0;

        public:

            SimpleServer(int domain, int service, int protocol, int port, u_long interface, int bklg);
            ~SimpleServer();
			
			ListeningSocket *	get_socket();
            virtual void		launch() = 0;
			
    };
}