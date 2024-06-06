/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoikoet <jgoikoet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:08:45 by jgoikoet          #+#    #+#             */
/*   Updated: 2024/06/06 13:00:34 by jgoikoet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "dependences.hpp"
# include "Request.hpp"
# include "Response.hpp"
# include "Confs.hpp"
# include "srv.hpp"

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
        int			id;
        int			sock;
        int			new_socket;
        int			port;
        
        int			maxFD;
        int         sizeOfAddress;           
        
        char		buffer[30000];
        

        std::vector<srv>    servers;
		
        std::map<int, int>  serversMap; // clave = socket bindeado, valor = servidor
		std::map<int, int>  readMap; // clave = socket mensajero, valor = servidor               
		std::map<int, int>  writeMap; // clave = socket mensajero, valor = servidor 

		std::map <int, Request *> rq;

        Confs conf;

    public:

        Server();
        Server(std::vector<srv> & srv);
        ~Server();
        
        void			respond(int i);
        void			my_select();
        void            Mselect();
        void            serverSet();

		static int sign;
		static void	signalHandler(int i);

        void        setRequest(std::string & buf);

		//FUNCIONES PARA PRUEBAS
		void printRequest();
        void setLoc();
        void printLoc();
};