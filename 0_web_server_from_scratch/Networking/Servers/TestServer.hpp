/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TestServer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoikoet <jgoikoet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:54:05 by jgoikoet          #+#    #+#             */
/*   Updated: 2024/05/13 18:04:45 by jgoikoet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTSERVER_HPP
# define TESTSERVER_HPP

#include "SimpleServer.hpp"

namespace HDE
{
    class TestServer : public SimpleServer
    {
        private :

			char buffer[30000] = {0};
			int	 new_socket;
			
			void accepter();
			void handler();
			void responder();

		public:

			TestServer();
			void launch();
    };
}

#endif