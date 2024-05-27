/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ListeningSocket.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoikoet <jgoikoet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:57:40 by jgoikoet          #+#    #+#             */
/*   Updated: 2024/05/13 16:22:31 by jgoikoet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LISTENINGSOCKET_HPP
# define LISTENINGSOCKET_HPP

#include "BindingSocket.hpp"

namespace HDE
{
    class ListeningSocket : public BindingSocket
    {
        private:

            int backlog;
            int listening;

        public:

            ListeningSocket(int domain, int service, int protocol, int port, u_long interface, int bklg);
            
            void	start_listening();
            int		get_listening();
			int		get_backlog();
    };
}


#endif