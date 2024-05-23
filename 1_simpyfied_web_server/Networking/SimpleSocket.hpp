/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SimpleSocket.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoikoet <jgoikoet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 15:28:43 by jgoikoet          #+#    #+#             */
/*   Updated: 2024/05/17 18:04:34 by jgoikoet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SimpleSocket_HPP
# define SimpleSocket_HPP

# include <stdio.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <iostream>
# include <cstdlib>


    class SimpleSocket
    {
        private:
            
            struct sockaddr_in address;
            int sock;
            
        public:
        
            SimpleSocket(int domain, int service, int protocol, int port, u_long interface);
            ~SimpleSocket();

            void                test_connection(int item_to_test, std::string who);

            struct sockaddr_in  get_address();
            int                 get_sock();
    };


#endif