#include "dependences.hpp"

int main(int ac, char **av)
{
    if(ac== 1)
        return Server(), 1;
    else if(ac == 2)
    {
        std::string filename (av[1]);
        return Server(filename), 1;
    }
    else
        return std::cout << "Error: Ejecuta ./my_server o ./my_server server.conf" << std::endl, 0;
}