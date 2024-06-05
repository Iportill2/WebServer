#include "dependences.hpp"
# include "Config.hpp"
# include "srv.hpp"
# include "Location.hpp"
int main(int ac, char **av)
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
}