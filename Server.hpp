/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoikoet <jgoikoet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:08:45 by jgoikoet          #+#    #+#             */
/*   Updated: 2024/06/11 10:41:06 by jgoikoet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "dependences.hpp"
# include "Request.hpp"
# include "Response.hpp"
# include "Confs.hpp"
# include <map>
# include <netinet/in.h>

class Request;
class Response;
class Confs;

class Server
{
    private:

        typedef struct s_client
        {
            int fd;
        }   t_client;
        
        sockaddr_in	ad;
        int         id;
        int     	sock;
        int     	new_socket;
        int     	port;
        char    	buffer[30000];

		std::map <int, Request *> rq;

        Confs conf;

    public:

        Server(int prt);
        ~Server();
        
        
        void			respond(int i);
        void			my_select();

        int get_maxfd();
		static int sign;
		static void	signalHandler(int i);

        void        setRequest(std::string & buf);

		//FUNCIONES PARA PRUEBAS
		void printRequest();
        void setLoc();
        void printLoc();
};
