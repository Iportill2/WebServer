#ifndef SERVER_HPP
# define SERVER_HPP
# include "dependences.hpp"


class Config;

class Server 
{
    private:

    std::string Host;
    std::string Port;
    std::string ServerName;
    int body_size;
    std::string root;
    std::string Location;
    std::string redirect_302;
    std::map<std::string, std::string> keyValue; // Variable de tipo clave-valor



    public:

		static int sign;
        Server();//constructor por defecto
        Server(std::string configName);//constructor con parametro
        ~Server();//destructor
      //std::string Host, std::string Port, std::string ServerName, int body_size, std::string root, std::string Location, std::string redirect_302
      void set_data();

        // Métodos para trabajar con la variable keyValue
        void setKeyValue(const std::string& key, const std::string& value);
        std::string getValue(const std::string& key) const ;
};
#endif
