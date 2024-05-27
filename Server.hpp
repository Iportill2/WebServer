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

    public:

        Server(std::string configName);
        ~Server();
        
        
        void    respond(int i);
        void    my_select();

};
#endif