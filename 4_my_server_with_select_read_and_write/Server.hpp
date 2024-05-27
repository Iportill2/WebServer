/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoikoet <jgoikoet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:08:45 by jgoikoet          #+#    #+#             */
/*   Updated: 2024/05/22 17:34:30 by jgoikoet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dependences.hpp"
#include "Config.hpp"

class Socket;

class Server : public Config
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

        Server(std::string configName);
        ~Server();
        
        
        void    respond(int i);
        void    my_select();

};