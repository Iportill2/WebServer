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

        if(confs.ok == 0)
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
/* int main()
{
    std::string s = "0.0.0.0:8080;";
    size_t i =0;
    while(s[i])
    {
        std::cout<< i <<"="<< s[i] << std::endl; 
        i++;
    }
        std::cout << "************************************\n";
        std::cout<< s.size() <<"="<< s[s.size()] << std::endl; 

} */