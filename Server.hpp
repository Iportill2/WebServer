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
        Server();//constructor por defecto
        Server(std::string configName);//constructor con parametro
        ~Server();//destructor
        
        
        void    respond(int i);
        void    my_select();

        int get_maxfd();
		static void	signalHandler(int i);

};
#endif
