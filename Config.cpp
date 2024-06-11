#include "Config.hpp"
Config::Config()
{
    //std::cout << "Default Config Constructor" << std::endl;
}
Config::Config(std::string configName)
{
    //std::cout << "Config Constructor" << std::endl;
    setValues();
    if(config_routine(configName) == 1)
    {
        if(validatePort() == 1)
            printArrayOfSrv();
        std::cout << "";
         //para printear los server y locations
    }
    //std::cout << BLUE << array_of_srv[0].array_of_location[0].getFile() << "|" << WHITE << std::endl;
}
Config::~Config()
{
    //std::cout << "Config Destructor" << std::endl;
}
void Config::printArrayOfSrv() const
{
    std::cout << "Number of srv: " << array_of_srv.size() << std::endl;
    for (size_t i = 0; i < array_of_srv.size(); ++i)
    {
        std::cout << BLUE << "srv:" << RED << "\"" << (i + 1) << "\"" << std::endl;
        std::cout << BLUE << "Host:" << RED << "\""<< array_of_srv[i].getHost() << "\""<< std::endl;
        std::cout << BLUE << "Port:" << RED << "\""<< array_of_srv[i].getPort() << "\""<< std::endl;
        std::cout << BLUE << ""<< RED  << "\""<< array_of_srv[i].getServerName() << "\""<< std::endl;
        std::cout << BLUE << "Body Size:" << RED << "\""<< array_of_srv[i].getBodySize() << "\""<< std::endl;
        std::cout << BLUE << "Root:" << RED << "\""<< array_of_srv[i].getRoot() << "\""<<  std::endl;
        std::cout << std::endl << BLUE << "ipNum:" << RED << "\""<< array_of_srv[i]._ipNum << "\""<<  std::endl;
        std::cout << BLUE << "sizetPort:" << RED << "\""<< array_of_srv[i]._sizetPort << "\""<<  std::endl;
        std::cout << BLUE << "sizetBody:" << RED << "\""<< array_of_srv[i]._sizetBody << "\""<<  std::endl;
       // Add more print statements for other srv data as needed
        for(size_t e = 0 ; e < array_of_srv[i].array_of_location.size(); ++e)
        {
            std::cout << GREEN   << "location num:" << RED << "\""<< e << "\""<< std::endl;
            std::cout << MAGENTA << "location:" << YELLOW << "\""<< array_of_srv[i].array_of_location[e].getLocation() << "\"" << std::endl;
            std::cout << MAGENTA << "root:" << YELLOW << "\""<< array_of_srv[i].array_of_location[e].getRoot() << "\""<< std::endl;
            std::cout << MAGENTA << "file:"<< YELLOW << "\""<< array_of_srv[i].array_of_location[e].getFile() << "\""<< std::endl;
            std::cout << MAGENTA << "methods:"<< YELLOW << "\""<< array_of_srv[i].array_of_location[e].getMethods() << "\""<< std::endl;
            std::cout << MAGENTA << "autoindex:"<< YELLOW << "\""<< array_of_srv[i].array_of_location[e].getAutoindex() << "\""<< std::endl;
            std::cout << MAGENTA << "cgi:"<< YELLOW << "\""<< array_of_srv[i].array_of_location[e]._cgi << "\""<< std::endl;
            std::cout << MAGENTA << "redirect 302:"<< YELLOW  << "\""<< array_of_srv[i].array_of_location[e]._redirect_302 << "\""<< WHITE << std::endl << std::endl; 
            for(size_t u = 0 ; u < array_of_srv[i].array_of_location[e].methods_vector.size() ; ++u)
            {
                std::cout << CYAN << "Methods[" << u << "]" << MAGENTA << array_of_srv[i].array_of_location[e].methods_vector[u] << WHITE << std::endl;
            }
        }
    }
}
void Config::setValues()
{
    server_id = 0;
    srvCount = 0;
    locationCount = 0;
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
int Config::countSubstring(const std::string& str, const std::string& sub)
{
    if (sub.length() == 0) return 0;
    int count = 0;
    for (size_t offset = str.find(sub); offset != std::string::npos;
     offset = str.find(sub, offset + sub.length()))
    {
        ++count;
    }
    return count;
}

bool  Config::config_routine(std::string configName)
{
    if(openFile(configName) == true)
    {
        std::cout << "Archivo abierto" << std::endl;
        if(getServerCount()  == 0)
            return 0;
        std::cout << BLUE << "Cantidad de servidores: " << YELLOW <<this->srvCount << WHITE << std::endl;
        createSrv();
        return(1);
    } 
    else
    {
        std::cout << "Archivo no abierto" << std::endl;
        return 0;
    }
}


void Config::createSrv()
{
    size_t tmp;
    std::istringstream f(this->file_content);
    std::string line;    
    std::string serverBlock;
    size_t i =0;
    std::stack<char> stak;
    
    while(i < file_content.size())
    {
        tmp = i;
        while(i < file_content.size() && file_content[i] != '{' && file_content[i] != '}')
            i++;

        if(i == file_content.size())
            break;

        if(file_content[i] == '{')
            stak.push('{');
        else if (file_content[i] == '}')
            break;
        i++;
        while (i < file_content.size() && !stak.empty())
        {
            if(file_content[i] == '{')
                stak.push(file_content[i]);
            else if(file_content[i] == '}')
                stak.pop();
            i++;
        }
        size_t length = i - tmp;
        if (tmp + length > file_content.size())
            length = file_content.size() - tmp;
        std::string sub = file_content.substr(tmp, length);
/*         std::cout << RED << "tmp:" << tmp << " lenght:" << length << WHITE <<std::endl;
        std::cout << CYAN << sub << WHITE <<std::endl; */
        srv newServer(sub);
        newServer.locationCount = countSubstring(file_content.substr(tmp, i - tmp), "location");
        array_of_srv.push_back(newServer);
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
    this->srvCount = server - server_name;

    if (this->srvCount > 0) 
        return 1;
    else
        return std::cout << RED << "Server count is less than 0" << WHITE << std::endl,0;
}
///////////////////////
/*
El rango de puertos válidos en Nginx, y en general en cualquier sistema que siga las 
convenciones de red estándar, es de 1 a 65535. Sin embargo, los puertos del 1 al 1023 
son conocidos como puertos bien conocidos y están reservados para servicios específicos 
(por ejemplo, el puerto 80 para HTTP, el puerto 443 para HTTPS). Por lo tanto, a menos 
que estés ejecutando Nginx como root (lo cual no se recomienda por razones de seguridad),
 deberías usar un puerto en el rango de 1024 a 65535.
*/
bool Config::validatePort()
{
    int tmp;
    size_t i = 0;
    while(i < array_of_srv.size())
    {
        tmp = std::atoi(array_of_srv[i].getPort().c_str());
        //std::cout << CYAN << "tmp="<< tmp << WHITE << std::endl;

        if(tmp > 1023 && tmp < 65535)
            std::cout << BLUE << "Port: " << RED << array_of_srv[i].getPort() << " OK!" << WHITE << std::endl;
        else
        {

            std::cout << CYAN << "validatePort() error the value of port is "<< RED << tmp << CYAN <<" should be betwen 1023 to 65535"<< WHITE << std::endl;
            return 0;
        }
        ++i;
    }
    return 1;
}
std::vector<srv> & Config::getArrayOfServers()
{
    return array_of_srv;
}


