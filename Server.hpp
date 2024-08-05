/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoikoet <jgoikoet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:08:45 by jgoikoet          #+#    #+#             */
/*   Updated: 2024/06/20 13:27:51 by jgoikoet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "dependences.hpp"
# include "Request.hpp"

# include "srv.hpp"
# include "Respons.hpp"

class Request;
class Respons;

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
        
        char		buffer[3000000];
        
        std::vector<int>    comFds;
        std::vector<srv>    servers;
		
        std::map<int, int>  serversMap; // clave = socket bindeado, valor = servidor
		std::map<int, int>  readMap; // clave = socket mensajero, valor = socket bindeado              
		std::map<int, int>  writeMap; // clave = socket mensajero, valor = servidor 

		std::map <int, Request *> rq;


    public:

        Server();
        Server(std::vector<srv> & srv);
        ~Server();
        
        void			respond(int i);
        void			Respond(int i);
        void			my_select();
        void            Mselect();
        void            serverSet();

		static int sign;
		static void	signalHandler(int i);

        void        setRequest(std::string & buf);

		//FUNCIONES PARA PRUEBAS
		void printRequest();
        void printServers();

        bool directoryExists(const std::string& dirName);
        bool fileExists(const std::string& filename);

        bool checkdefaultsettings(std::string ip, Location l1,Location l2,srv s);

};