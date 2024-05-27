/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TestServer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoikoet <jgoikoet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:54:05 by jgoikoet          #+#    #+#             */
/*   Updated: 2024/05/16 17:29:47 by jgoikoet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTSERVER_HPP
# define TESTSERVER_HPP

#include "SimpleServer.hpp"

class TestServer : public SimpleServer
{
    private :

		char buffer[30000];
		int	 new_socket;
		
		void accepter();
		void handler();
		void responder();

	public:

		TestServer();
		void launch();
};


#endif