
#include "dependences.hpp"
#include "Server.hpp"
#include "location.hpp"


Config::Config()
{
    std::cout << "Default Config Constructor" << std::endl;
}

Config::Config(std::string configName)
{
    std::cout << "Config Constructor" << std::endl;
    setValues();
    config_routine(configName);
}

Config::~Config()
{
    std::cout << "Config Destructor" << std::endl;
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

void Config::config_routine(std::string configName)
{
    if(openFile(configName) == true)
    {
        std::cout << "Archivo abierto" << std::endl;
        if(getServerCount()  == 0)
            return;
        std::cout << RED << "Cantidad de servidores: " << YELLOW <<this->srvCount << WHITE << std::endl;
        std::cout << RED << "Cantidad de locations: " << YELLOW <<this->locationCount << WHITE << std::endl;
        createSrv();
    } 
    else
    {
        std::cout << "Archivo no abierto" << std::endl;
        return;
    }
}



/* void Config::createLocations(const srv& newServer) 
{
	std::vector<location> array_of_location;
	//array_of_location.push_back(location());
    for(int i = 0; i < newServer.locationCount; ++i) 
    {
        //std::cout << "X" << std::endl;
        array_of_location.push_back(location());
        std::cout << MAGENTA << "Location: " << YELLOW << i << WHITE << std::endl;
    }
} */

void Config::createSrv()
{
    //int i = 0;
    std::istringstream f(this->file_content);
    std::string line;    

	std::string serverBlock;

    while(std::getline(f, line)) 
    {
        serverBlock = "";
        if(line.find("server") != std::string::npos) 
        {
			 while(std::getline(f, line) && line.find("}}")  == std::string::npos) 
            {
                serverBlock += line;

            }
                //std::cout << MAGENTA << serverBlock << WHITE << std::endl;
				srv newServer(serverBlock);
                newServer.locationCount = countSubstring(serverBlock, "location");
				array_of_srv.push_back(newServer);
            
/*             srv *newServer = new srv();
            std::string serverBlock;
            while(std::getline(f, line) && line.find("}}")  == std::string::npos) 
            {
                serverBlock += line;
            }
			
            createLocations(*newServer);
            array_of_srv.push_back(*newServer);
            std::cout << GREEN << "Server: " << RED << i << GREEN << ", Locations: " << RED << newServer->locationCount << WHITE << std::endl;
            i++; */
        }
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

/*     std::cout << "server: " << server << std::endl;
    std::cout << "server_name: " << server_name << std::endl;  */  
    this->srvCount = server - server_name;

    if (this->srvCount > 0) 
        return 1;
    else
        return std::cout << RED << "Server count is less than 0" << WHITE << std::endl,0;
}
