/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BindingSocket.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoikoet <jgoikoet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:53:14 by jgoikoet          #+#    #+#             */
/*   Updated: 2024/05/13 16:47:54 by jgoikoet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINDINGSOCKET_HPP
# define BINDINGSOCKET_HPP

# include <stdio.h>
# include "SimpleSocket.hpp"

namespace HDE
{
    class BindingSocket: public SimpleSocket
    {
        private:

            int		binding;
            void	connect_to_network(int sock, struct sockaddr_in address);
        
        public:
        
            BindingSocket(int domain, int service, int protocol, int port, u_long interface);
            
            int get_binding();
    };
}
#endif