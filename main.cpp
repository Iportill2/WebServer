/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoikoet <jgoikoet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:00:00 by jgoikoet          #+#    #+#             */
/*   Updated: 2024/08/16 18:14:12 by jgoikoet         ###   ########.fr       */
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
        {
            Server server(confs.getArrayOfServers());
        }
    }
    return (0);
}

/* #include "Directory.hpp"

int main()
{
    Directory d("uploaded_files");

    return 0;
} */

/*
    ///config basica de cgi segun chatgpt
    
 # CGI configuration for C programs
    location /cgi-bin/ {
        fastcgi_pass 127.0.0.1:9000;  # Forward CGI requests to the FastCGI server running on port 9000
        fastcgi_param SCRIPT_FILENAME /var/www/cgi-bin/$fastcgi_script_name;  # Path to your CGI script
        include fastcgi_params;  # Include FastCGI parameters
    }
*/