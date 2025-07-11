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
        //std::cout << "if(checksrvloc() == false)";
		return;
	}
	if(checkduplicateports() == false)
	{
        //std::cout << "if(checkduplicateports() == false)";
		return;
	}
    if(checkduplicateports_server_name() == false)
        return;
    if(validatePort() == false)
	{
        //std::cout << "if(validatePort() == false)";
		return;
	}
	if(getServerCount() == false)
	{
        //std::cout << "if(getServerCount() == false)";
		return;
	}
    if(getArrayOfServers().empty())
    {
        //std::cout << "getArrayOfServers().empty())";
		return;
    }
    ok = 1;
    //std::cout << BLUE << array_of_srv[0].arLoc[0].getFile() << "|" << WHITE << std::endl;
}
Config::~Config()
{
    //std::cout << "Config Destructor" << std::endl;
}

bool Config::checkduplicateports_server_name()
{
    size_t i = 1;
    size_t e = 0;
    while(i < array_of_srv.size())
    {
        e = 0;
        while(e < i)
        {
            if ((array_of_srv[i]._port == array_of_srv[e]._port) && (array_of_srv[i]._server_name == array_of_srv[e]._server_name))
            {
                std::cout << "i=" << i <<"/" << "e=" << e << std::endl;
                std::cout << array_of_srv[i]._port << "=" <<array_of_srv[e]._port << std::endl;
                std::cout << array_of_srv[i]._server_name << "=" <<array_of_srv[e]._server_name << std::endl;
                return std::cout << RED << "checkduplicateports_server_name()" << WHITE << std::endl,false;
            }
            e++;
        }
        i++;
    }
    return true;
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
        if(array_of_srv[i].srv_ok == false)
            return(std::cout << RED << "array_of_srv[" << i << "].srv_ok="<< array_of_srv[i].srv_ok << WHITE << std::endl,false);
        size_t e = 0;
        while (e < array_of_srv[i].arLoc.size())
        {
            size_t u = 0;
            while (u < array_of_srv[i].arLoc[e].methods_vector.size())
                ++u;
            ++e;
        }
        ++i;
    }
    return true;
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
        return(true);
    return false;
}


bool Config::openFile(std::string Configname)
{
    this->file.open(Configname.c_str(), std::ios::in);
    if (this->file.is_open() == false) 
        return false;
    std::stringstream buffer;
    buffer << file.rdbuf();

    // Convertir el contenido del stringstream en un string
    this->file_content = buffer.str();
    //std::cout << this->Config_data << std::endl;//para printear el contenido del archivo
    file.close();
    return true;
}


bool  Config::config_routine(std::string configName)
{
    if(openFile(configName) == true)
    {
        if(file_content.empty())
            return(std::cout << RED << "File is Empty!"<< WHITE << std::endl ,false);
        if(pairbrackets(file_content) == false)
            return(std::cout << RED << "Bad brackets configuration, please check your config file" << WHITE << std::endl,false);
        if(createSrv() == false)
            return(false);
        return(true);
    } 
    else
        return std::cout << "Archivo no abierto" << std::endl,false;
}


bool Config::createSrv()
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
    return(true);
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
        return true;
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
            return(std::cout << array_of_srv[i]._sizetPort << std::endl,false);
        if(array_of_srv[i]._sizetPort > 1023 && array_of_srv[i]._sizetPort < 65535)
            std::cout << BLUE << "Port: " << RED << array_of_srv[i]._sizetPort << " OK!" << WHITE << std::endl;
        else
            return std::cout << CYAN << "validatePort() error the value of port is "<< RED << array_of_srv[i]._sizetPort << CYAN <<" should be betwen 1023 to 65535"<< WHITE << std::endl,false;
        ++i;
    }
    return true;
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


