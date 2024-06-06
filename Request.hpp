
#pragma once

# include "dependences.hpp"

class Request
{
    private:
       
		std::string	buffer;

        std::string method;
        std::string uri;
        std::string host;
        std::string port;
        int         content_len;

        std::string body;

    public:
    
        Request(std::string buf);
        ~Request();
        
        void    parse();

        std::string getMethod();
        std::string getUri();
        std::string getHost();
        std::string getPort();
        std::string getBody();
        int         getContentLen();

        //FUNCIONES PARA PRUEBAS
        void printRequest();
};
