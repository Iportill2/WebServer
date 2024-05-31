
#include "dependences.hpp"
#include "Server.hpp"



Config::Config()
{
    std::cout << "Default Config Constructor" << std::endl;
}

Config::Config(std::string configName)
{
    std::cout << "Config Constructor" << std::endl;
    server_id = 0;
    config_routine(configName);
}

Config::~Config()
{
    std::cout << "Config Destructor" << std::endl;
}


bool Config::openFile(std::string Configname)
{
    this->file.open(Configname.c_str(), std::ios::in);
    if (this->file.is_open() == false) 
        return 0;
    std::stringstream buffer;
    buffer << file.rdbuf();

    // Convertir el contenido del stringstream en un string
    this->file_content = buffer.str();
    //std::cout << this->Config_data << std::endl;//para printear el contenido del archivo
    file.close();
    return 1;
}
void Config::config_routine(std::string configName)
{

    if(openFile(configName) == true)
    {
        std::cout << "Archivo abierto" << std::endl;
        if(getServerCount()  == 0)
            return;
        std::cout << RED << "Cantidad de servidores: " << YELLOW <<this->serverCount << WHITE << std::endl;
        this->servers = std::vector<std::map<std::string, std::string> >(this->serverCount);
        std::map<std::string, std::string> new_content;
        new_content = setHostFromContent(file_content);
        createvector(this->servers, new_content);
    }
    else
    {
        std::cout << "Archivo no abierto" << std::endl;
        return;
    }
}

void Config::createvector(std::vector<std::map<std::string, std::string> > servers, const std::map<std::string, std::string>& new_content)
{
    servers.push_back(new_content);

    if (!servers.empty()) 
    {
        std::cout << "Server vector is not empty" << std::endl;
    }
    size_t Server_index = 0;
    while ( Server_index < servers.size()) 
    {
        std::cout << "Server index: " << Server_index << std::endl;
        std::map<std::string, std::string>::const_iterator it = servers[Server_index].begin();
        while (it != servers[Server_index].end()) 
        {
            std::cout << "Key: " << it->first << ", Value: " << it->second << std::endl;
            ++it;
        }
        ++Server_index;
    }
}

size_t Config::size(const char *s)
{
	size_t i = 0;
	if (s == NULL)
		return 0;
	while (s[i] != '\0')
		++i;
	return i;
}
std::map<std::string, std::string> Config::setHostFromContent(const std::string& file_content) 
{
/*
std::string::npos` es una constante estática de la clase `std::string` en C++. Se utiliza para
 representar una posición no encontrada en una cadena de texto.
Cuando usas la función `std::string::find`, esta devuelve la posición de la primera ocurrencia 
de la subcadena que estás buscando. Si la subcadena no se encuentra en la cadena de texto, `find`
 devuelve `std::string::npos`.
En tu código, `std::string::npos` se utiliza para comprobar si las cadenas "listen", "body_size"
 y "root" se encontraron en `file_content`. Si `find` devuelve `std::string::npos`, eso significa
  que la cadena no se encontró, y el código dentro del bloque `if` no se ejecuta.	
*/

    std::map<std::string, std::string> result;

    //std::string::size_type pos;
    size_t  pos;

    pos = file_content.find("listen");
    std::cout << GREEN << "NPOS:" << std::string::npos << WHITE << std::endl;
    std::cout << GREEN << "POS:" << pos << WHITE << std::endl;
    std::cout << "---------------------------------------" << std::endl;
    if (pos != std::string::npos) 
	{
        std::cout << GREEN << "NPOS:" << std::string::npos << WHITE << std::endl;
        std::cout << GREEN << "POS:" << pos << WHITE << std::endl;
        pos += size("listen");  // 7 Skip "listen "
        //std::string::size_type end = file_content.find(";", pos);
        size_t end = file_content.find(";", pos);
        std::string host_port = file_content.substr(pos, end - pos);
        //std::string::size_type colon = host_port.find(":");
        size_t colon = host_port.find(":");
        result["Host"] = host_port.substr(0, colon);
        result["Port"] = host_port.substr(colon + 1);
    }
    pos = file_content.find("body_size");
    if (pos != std::string::npos) 
	{
        pos += size("body_size");  //10 Skip "body_size "
        std::string::size_type end = file_content.find(";", pos);
        result["body_size"] = file_content.substr(pos, end - pos);
    }

    pos = file_content.find("root");
    if (pos != std::string::npos) 
	{
        pos += size("root");  //5 Skip "root "
        std::string::size_type end = file_content.find(";", pos);
        result["root"] = file_content.substr(pos, end - pos);
    }

    return result;

}

bool Config::getServerCount()
{
    int server = 0;
    int server_name = 0;
    size_t  pos = 0;
    //std::string::size_type pos = 0;

    while ((pos = file_content.find("server", pos)) != std::string::npos) 
    {
        ++server;
        pos += 6; // Longitud de la cadena "Server"
    }
    pos = 0;
    while ((pos = file_content.find("server_name", pos)) != std::string::npos) 
    {
        ++server_name;
        pos += 11; // Longitud de la cadena "Server"
    }
/*     std::cout << "server: " << server << std::endl;
    std::cout << "server_name: " << server_name << std::endl;  */  
    this->serverCount = server - server_name;

    if (this->serverCount > 0) 
        return 1;
    else
        return std::cout << RED << "Server count is less than 0" << WHITE << std::endl,0;
}
