
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
        std::string downfile;

        std::string boundary;
        std::string boundaryContent;
        std::string upfileContent;
        std::string upfileName;

    public:
    
        Request();
        ~Request();
        
        void    parse();

        std::string getMethod();
        std::string getUri();
        std::string getHost();
        std::string getPort();
        std::string getBody();
        std::string getBoundary();
        std::string getDownFile();

        std::string getUpFileContent();
        std::string getUpFileName();


        size_t		getContentLen();

		void        stractBoundary(std::string bound);

        void addBuffer(char * buf, int bytes);

        //FUNCIONES PARA PRUEBAS
        void printRequest();
};
