/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoikoet <jgoikoet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:08:45 by jgoikoet          #+#    #+#             */
/*   Updated: 2024/05/21 15:53:38 by jgoikoet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dependences.hpp"


class Socket;

class Server
{
    private:

        int     sock;
        int     port;
        int     new_socket;
        char    buffer[30000];

    public:

        Server(int prt);
        ~Server();
        
        void respond();
};