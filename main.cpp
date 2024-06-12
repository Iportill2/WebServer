/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoikoet <jgoikoet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:00:00 by jgoikoet          #+#    #+#             */
/*   Updated: 2024/06/11 15:49:38 by jgoikoet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Server.hpp"
# include "dependences.hpp"
# include "Config.hpp"



int main(int argc, char **argv)
{
    if (argc == 1)
    {
        std::cout << std::endl << BLUE << "Configuration file not provided" << std::endl;
        std::cout << GREEN <<"Loading default configuration..."<< WHITE << std::endl << std::endl;
        Server  server;
    }
    
    else if(argc == 2)
    {
        Config confs(argv[1]);
    
        if (confs.getArrayOfServers().empty())
        {
            std::cout << std::endl << RED <<"Invalid configuration file" << std::endl;
            std::cout << GREEN << "Loading default configuration..." << WHITE << std::endl << std::endl;
            Server server;
        }
        else
            Server server(confs.getArrayOfServers());
    }
    return (0);
}

/* int main(int ac, char **av)
{
    if(ac== 1)
        return Config(), 1;
    else if(ac == 2)
    {
        std::string filename (av[1]);
        return Config(filename), 1;
    }
    else
        return std::cout << "Error: Ejecuta ./my_server o ./my_server server.conf" << std::endl, 0;
} */