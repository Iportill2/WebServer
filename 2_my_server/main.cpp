/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoikoet <jgoikoet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:00:00 by jgoikoet          #+#    #+#             */
/*   Updated: 2024/05/21 15:54:21 by jgoikoet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "dependences.hpp"

int main()
{
    //./webserv [configuration file]  //de ejecutarse con esta linea de comandos
    Server  server(8080);

    //std::cout << s.get_fd() << std::endl;
}