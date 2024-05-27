/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoikoet <jgoikoet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:00:00 by jgoikoet          #+#    #+#             */
/*   Updated: 2024/05/22 18:46:35 by jgoikoet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Config.hpp"
#include "dependences.hpp"
#include <string>

int main(int ac, char **av)
{
    (void)av;
    //Server  server(8080);
    //if(ac == 2 && av[1] == "server.conf")
    if(ac == 2 )
    {
    //std::cout << "patata" << std::endl;
    std::string filename (av[1]);
    std::cout << "El string es: " << filename << std::endl;
    //Config a(filename);
    Server c (filename);
    return(1);
    }
    else
    {
        std::cout << "Error: No se ha encontrado el archivo de configuración" << std::endl;
        return(0);
    }

    return(0);
}