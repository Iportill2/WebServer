
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
        size_t		content_len;

        std::string body;
        std::string boundary;

    public:
    
        Request(std::string buf);
        ~Request();
        
        void    parse();

        std::string getMethod();
        std::string getUri();
        std::string getHost();
        std::string getPort();
        std::string getBody();
        std::string getBoundary();

        size_t		getContentLen();

        //FUNCIONES PARA PRUEBAS
        void printRequest();
};
