/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoikoet <jgoikoet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:00:00 by jgoikoet          #+#    #+#             */
/*   Updated: 2024/06/06 11:52:20 by jgoikoet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Server.hpp"
# include "dependences.hpp"
# include "Config.hpp"


void printArrayOfServers(std::vector<srv> & a)
{
    for (size_t i = 0; i < a.size(); i++)
    {
        std::cout << "---------SERVER " << i + 1 << "------------------------------------------" << std::endl;
        std::cout << "host:" << "\"" << GREEN << a[i]._host << WHITE << "\"" << std::endl;
        std::cout << "port:" << "\"" << GREEN << a[i]._port << WHITE << "\"" << std::endl;
        std::cout << "server name:" "\"" << GREEN << a[i]._server_name << WHITE << "\"" << std::endl;
        std::cout << "root:" << "\"" << GREEN << a[i]._root<< WHITE << "\"" <<std::endl;

        for(size_t j = 0; j < a[i].arLoc.size() ; j++)
        {
            std::cout << std::endl << "*LOCATION " << j + 1 << std::endl;
            std::cout << "Location: " << "\"" << GREEN << a[i].arLoc[j]._location << WHITE << "\"" << std::endl;
            std::cout << "root: " << "\"" << GREEN << a[i].arLoc[j]._root << WHITE << "\"" << std::endl;
            std::cout << "file: " << "\"" << GREEN << a[i].arLoc[j]._file << WHITE << "\"" << std::endl;
            std::cout << "methods: " << "\"" << GREEN << a[i].arLoc[j]._methods << WHITE << "\"" << std::endl;
            std::cout << "autoindex: " << "\"" << GREEN << a[i].arLoc[j]._autoindex << WHITE << "\"" << std::endl;
            std::cout << "cgi:" << "\"" << GREEN << a[i].arLoc[j]._cgi << WHITE << "\"" << std::endl;
            std::cout << "redirect: " << "\"" << GREEN << a[i].arLoc[j]._redirect_302 << WHITE << "\"" << std::endl;
        }
        std::cout << "---------------------------------------------------------------------" << std::endl;
    }
}

int main(int argc, char **argv)
{
    if (argc == 1)
        Server  server;
    
    else if(argc == 2)
    {
        Config confs(argv[1]);
    
        if (confs.getArrayOfServers().empty())
            std::cout << "TA VACIO" << std::endl;
        else
        {
            //printArrayOfServers(confs.getArrayOfServers());
            Server server(confs.getArrayOfServers());
        }
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