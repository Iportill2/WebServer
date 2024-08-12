#include "Config.hpp"
Config::Config()
{
    //std::cout << "Default Config Constructor" << std::endl;
}
Config::Config(std::string configName)
{
    ok = 0;
    //std::cout << "Config Constructor" << std::endl;
    if(config_routine(configName) == false)
	{
		std::cout << "if(config_routine(configName) == false)";    
        return;
	}
    if(checksrvloc() == false)
	{
        std::cout << "if(checksrvloc() == false)";
		return;
	}
	if(checkduplicateports() == false)
	{
        std::cout << "if(checkduplicateports() == false)";
		return;
	}
    if(validatePort() == false)
	{
        std::cout << "if(validatePort() == false)";
		return;
	}
	if(getServerCount() == false)
	{
        std::cout << "if(getServerCount() == false)";
		return;
	}
    if(getArrayOfServers().empty())
    {
        std::cout << "getArrayOfServers().empty())";
		return;
    }
    ok = 1;
    //printArrayOfSrv();
    //std::cout << BLUE << array_of_srv[0].arLoc[0].getFile() << "|" << WHITE << std::endl;
}
Config::~Config()
{
    //std::cout << "Config Destructor" << std::endl;
}
bool Config::checkduplicateports()
{
    size_t i = 1;
    size_t e = 0;
    //std::cout << RED << "@"<< array_of_srv[e]._port << WHITE << std::endl;
    while(i < array_of_srv.size())
    {
        e = 0;
        while(e < i)
        {
            if ((array_of_srv[i]._port == array_of_srv[e]._port) && (array_of_srv[i]._host == array_of_srv[e]._host))
            {
                std::cout << "i=" << i <<"/" << "e=" << e << std::endl;
                std::cout << array_of_srv[i]._port << "=" <<array_of_srv[e]._port << std::endl;
                std::cout << array_of_srv[i]._host << "=" <<array_of_srv[e]._host << std::endl;
                return std::cout << RED << "Dupicate port in config" << WHITE << std::endl,false;
            }
            e++;
        }
        i++;
    }
    return true;
}

bool Config::checksrvloc()
{
    size_t i = 0;
    while (i < array_of_srv.size())
    {
        if(array_of_srv[i].srv_ok == 0)
            return(std::cout << RED << "array_of_srv[" << i << "].srv_ok="<< array_of_srv[i].srv_ok << WHITE << std::endl,0);
        //std::cout << GREEN<< "array_of_srv[" << i << "].srv_ok="<< array_of_srv[i].srv_ok << WHITE<< std::endl;
        size_t e = 0;
        while (e < array_of_srv[i].arLoc.size())
        {
            size_t u = 0;
            while (u < array_of_srv[i].arLoc[e].methods_vector.size())
            {
               // std::cout << CYAN << "Methods[" << u << "]" << MAGENTA << array_of_srv[i].arLoc[e].methods_vector[u] << WHITE << std::endl;
                ++u;
            }
            ++e;
        }
        ++i;
    }
    //std::cout << YELLOW << array_of_srv[3].arLoc[0]._location << WHITE << std::endl;
    return 1;
}
bool Config::pairbrackets(const std::string s)
{
    std::stack<char> brackets;

    for (size_t i = 0; i < s.size(); i++)
    {
        if (s[i] == '{')
        {
            brackets.push('{');
        }
        else if (s[i] == '}')
        {
            if (brackets.empty())
            {
                return 0;
            }
            brackets.pop();
        }
    }
    if(brackets.empty())
        return(1);
    return 0;
}
void Config::printArrayOfSrv() const
{
/*     std::cout << "Number of srv: " << array_of_srv.size() << std::endl;
    for (size_t i = 0; i < array_of_srv.size(); ++i)
    {
        std::cout << BLUE << "srv:" << RED << "\"" << (i + 1) << "\"" << std::endl;
        std::cout << BLUE << "Host:" << RED << "\""<< array_of_srv[i].getHost() << "\""<< std::endl;
        std::cout << BLUE << "Port:" << RED << "\""<< array_of_srv[i].getPort() << "\""<< std::endl;
        std::cout << BLUE << "Server Name:"<< RED  << "\""<< array_of_srv[i].getServerName() << "\""<< std::endl;
        std::cout << BLUE << "Body Size:" << RED << "\""<< array_of_srv[i].getBodySize() << "\""<< std::endl;
        std::cout << BLUE << "Root:" << RED << "\""<< array_of_srv[i].getRoot() << "\""<<  std::endl;
        std::cout << std::endl << BLUE << "ipNum:" << RED << "\""<< array_of_srv[i]._ipNum << "\""<<  std::endl;
        std::cout << BLUE << "sizetPort:" << RED << "\""<< array_of_srv[i]._sizetPort << "\""<<  std::endl;
        std::cout << BLUE << "sizetBody:" << RED << "\""<< array_of_srv[i]._sizetBody << "\""<<  std::endl;
       // Add more print statements for other srv data as needed
        for(size_t e = 0 ; e < array_of_srv[i].arLoc.size(); ++e)
        {
            std::cout << GREEN   << "location num:" << RED << "\""<< e << "\""<< std::endl;
            std::cout << MAGENTA << "location:" << YELLOW << "\""<< array_of_srv[i].arLoc[e].getLocation() << "\"" << std::endl;
            std::cout << MAGENTA << "root:" << YELLOW << "\""<< array_of_srv[i].arLoc[e].getRoot() << "\""<< std::endl;
            std::cout << MAGENTA << "file:"<< YELLOW << "\""<< array_of_srv[i].arLoc[e].getFile() << "\""<< std::endl;
            std::cout << MAGENTA << "methods:"<< YELLOW << "\""<< array_of_srv[i].arLoc[e].getMethods() << "\""<< std::endl;
            std::cout << MAGENTA << "autoindex:"<< YELLOW << "\""<< array_of_srv[i].arLoc[e].getAutoindex() << "\""<< std::endl;
            std::cout << MAGENTA << "cgi:"<< YELLOW << "\""<< array_of_srv[i].arLoc[e]._cgi << "\""<< std::endl;
            std::cout << MAGENTA << "redirect 302:"<< YELLOW  << "\""<< array_of_srv[i].arLoc[e]._redirect << "\""<< WHITE << std::endl << std::endl; 
            for(size_t u = 0 ; u < array_of_srv[i].arLoc[e].methods_vector.size() ; ++u)
            {
                std::cout << CYAN << "Methods[" << u << "]" << MAGENTA << array_of_srv[i].arLoc[e].methods_vector[u] << WHITE << std::endl;
            }
        }
    } */
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


bool  Config::config_routine(std::string configName)
{
    if(openFile(configName) == true)
    {
        
/*         std::cout << file_content.size() << std::endl;
        std::cout << file_content << std::endl; */

        if(file_content.empty())
            return(std::cout << RED << "File is Empty!"<< WHITE << std::endl ,0);
        if(pairbrackets(file_content) == 0)
            return(std::cout << RED << "Bad brackets configuration, please check your config file" << WHITE << std::endl,0);
        //std::cout << "pepe" << std::endl;
        if(createSrv() == 0)
            return(0);
       // std::cout << "peep" << std::endl;
        return(1);
    } 
    else
    {
        std::cout << "Archivo no abierto" << std::endl;
        return 0;
    }
}


bool Config::createSrv()
{
    size_t tmp;
    std::istringstream f(this->file_content);
    std::string line;    
    std::string serverBlock;
    size_t i =0;
    std::stack<char> stak;

    srv Ser;
    
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
        size_t pos = sub.find("server");
        if (pos != std::string::npos) 
        {
            srv newServer(sub);
            newServer.locationCount = countSubstring(file_content.substr(tmp, i - tmp), "location");
            if(newServer.srv_ok == 1)
                array_of_srv.push_back(newServer);
        } 
        else 
            return(std::cout << "sub didnt contain the word server" << std::endl,0);
    
    }
    return(1);
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
    {
        std::cout << BLUE << "Cantidad de servidores: " << YELLOW <<this->srvCount << WHITE << std::endl;
        return 1;
    }
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
    size_t i = 0;
    while(i < array_of_srv.size())
    {
        if(array_of_srv[i]._sizetPort == 0)
            return(std::cout << array_of_srv[i]._sizetPort << std::endl,0);
        if(array_of_srv[i]._sizetPort > 1023 && array_of_srv[i]._sizetPort < 65535)
            std::cout << BLUE << "Port: " << RED << array_of_srv[i]._sizetPort << " OK!" << WHITE << std::endl;
        else
            return std::cout << CYAN << "validatePort() error the value of port is "<< RED << array_of_srv[i]._sizetPort << CYAN <<" should be betwen 1023 to 65535"<< WHITE << std::endl,0;
        ++i;
    }
    return 1;
}
std::vector<srv> & Config::getArrayOfServers()
{
    return array_of_srv;
}

std::string & Config::skip_p_t_esp(std::string &s)
{
    size_t start = 0;
    while (start < s.size() && (s[start] == ' ' || s[start] == '\n' || s[start] == '\t')) {
        ++start;
    }
    s = s.substr(start);
    return s;
}


