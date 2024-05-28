#ifndef SERVER_HPP
# define SERVER_HPP
# include "dependences.hpp"


class Socket;

class Server : public Config
{
    private:

        typedef struct s_client
        {
            int fd;
        }   t_client;
        
        int     id;
        int     sock;
        int     new_socket;
        //int     port;
        char    buffer[30000];
        sockaddr_in	ad;

    public:

		static int sign;

        Server(std::string configName);
        ~Server();
        
        
        void    respond(int i);
        void    my_select();

        int get_maxfd();
		static void	signalHandler(int i);

};
#endif

/*
#include "dependences.hpp"

class Socket;

class Server
{
    private:

        typedef struct s_client
        {
            int fd;
        }   t_client;
        
        sockaddr_in	ad;
        int     id;
        int     sock;
        int     new_socket;
        int     port;
        char    buffer[30000];

    public:

        Server(int prt);
        ~Server();
        
        
        void			respond(int i);
        void			my_select();

		static int sign;
		static void	signalHandler(int i);
};
*/