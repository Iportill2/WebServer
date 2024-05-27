/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoikoet <jgoikoet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:08:45 by jgoikoet          #+#    #+#             */
/*   Updated: 2024/05/24 17:49:15 by jgoikoet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dependences.hpp"

class Socket;

class Server
{
    private:

        typedef struct s_client
        {
            int fd;
        }   t_client;
        
        int     id;
        int     sock;
        int     new_socket;
        int     port;
        char    buffer[30000];

    public:

        Server(int prt);
        ~Server();
        
        
        void			respond(int i);
        void			my_select();

        int get_maxfd();
		static int sign;
		static void	signalHandler(int i);
};