#include "dependences.hpp"
#include "srv.hpp"
#include "Config.hpp"
srv::srv(std::string serverBlock)
{
    //std::cout << "Default srv Constructor" << std::endl;
    nullstrings();
    parseServerBlock(serverBlock) ;
}
srv::~srv()
{
    //std::cout << "srv Destructor" << std::endl;
}

void srv::nullstrings()
{
    _host = "";
    _port = "";
    _server_name = "";
    _body = "";
    _Root = "";

}
std::vector<Location> &  srv::getlocations()
{
    return(array_of_location);
}
void srv::parseServerBlock(const std::string& serverBlock) 
{
    size_t pos;
    std::string temp;
    pos = 0;

    pos = serverBlock.find("listen");
    while (pos != std::string::npos) 
    {
        pos += std::string("listen").size(); // Skip "server_name "
        size_t endPos = serverBlock.find(':', pos);
        temp = serverBlock.substr(pos, endPos - pos);
        if(_host == "")
            _host = temp;
        else
            std::cout << "ERROR al conseguir HOST valor ya inicializado" << std::endl;
        
        pos = serverBlock.find("listen", endPos);
    }

    pos = serverBlock.find(_host);

    while (pos != std::string::npos) 
    {
        pos += std::string(_host + ":").size(); // Skip "server_name "
        size_t endPos = serverBlock.find(';', pos);
        temp = serverBlock.substr(pos, endPos - pos);

        if(_port == "")
        {
            _port = temp;
        }
        else
            std::cout << "ERROR al conseguir PORT valor ya inicializado" << std::endl;
        
        pos = serverBlock.find(_host, endPos);
    }

    


    // Find and extract server_name
    pos = serverBlock.find("server_name");
    while (pos != std::string::npos) 
    {
        pos += std::string("server_name").size(); // Skip "server_name "
        size_t endPos = serverBlock.find(';', pos);
        temp = serverBlock.substr(pos, endPos - pos);
        if(_server_name == "")
            _server_name = temp;
        else
            std::cout << "ERROR al conseguir SERVER_NAME valor ya inicializado" << std::endl;

        // Update pos to start searching after the last occurrence of "server_name"
        pos = serverBlock.find("server_name", endPos);
    }

    pos = serverBlock.find("body_size");
    while (pos != std::string::npos) 
    {
        pos += std::string("body_size").size(); // Skip "server_name "
        size_t endPos = serverBlock.find(';', pos);
        temp = serverBlock.substr(pos, endPos - pos);
        if(_body == "")
            _body = temp;
        else
            std::cout << "ERROR al conseguir BODY_SIZE valor ya inicializado" << std::endl;

        // Update pos to start searching after the last occurrence of "server_name"
        pos = serverBlock.find("body_size", endPos);
    }


    // Find and extract root
    pos = serverBlock.find("server {");
    pos = pos + 9;
    while (pos < serverBlock.size() && serverBlock[pos] != '{')  
    {
        //pos += std::string("{").size(); // Skip "{"
        pos = serverBlock.find("root", pos); // Find "root" after "{"
        if (pos != std::string::npos)
        {
            pos += std::string("root").size(); // Skip "root "
            size_t endPos = serverBlock.find(';', pos);
            temp = serverBlock.substr(pos, endPos - pos);
            std::cout << "!" ;
            if(_Root == "")
                _Root = temp;
            else
            {
                std::cout << "ERROR al conseguir ROOT valor ya inicializado" << std::endl;
                //break;
            }
            //pos = serverBlock.find("{");
        }
    }
        // Find and extract location
    pos = serverBlock.find("location");
    while (pos < serverBlock.size()) 
    {
        pos += std::string("location").size(); // Skip "location "
        size_t endPos = serverBlock.find('}', pos);
        if (endPos != std::string::npos) 
        {
            std::string locationBlock = serverBlock.substr(pos, endPos - pos);
            pos = endPos + 1; // Skip "}"
			if(checkstring() == 0)
				return;
            Location newLocation(locationBlock);
            array_of_location.push_back(newLocation);
        }
        else 
            break;
    }

}



bool srv::ipAddressToipNum(std::string ipAddress) 
{
	//std::cout << "ipAddress:"<< "|" << ipAddress << "|" << std::endl;
    struct in_addr addr;
    // Convierte la dirección IP desde el formato de texto a la representación binaria en formato de red
    if (inet_pton(AF_INET, ipAddress.c_str(), &addr) != 1) 
	{
        std::cerr << "Error converting IP address." << std::endl;
        return 0;
    }
    // Convierte la dirección IP desde el formato de red a la representación numérica en formato de host
	_ipNum = ntohl(addr.s_addr);

    //std::cout << "The numeric representation of " << ipAddress << " is " << _ipNum << std::endl;
    return 1;
}

    
bool srv::checkstring()
{
    if(_host != "" )
	{
        deletespaces(_host);
		if(ipAddressToipNum(_host) == 0)
			return (0);
	}
    if(_port != "" )
	{
        deletespaces(_port);
		if(stringToSizeT(_port, _sizetPort) == 0)
			return(0);
	}
    if(_body != "" )
	{
        deletespaces(_body);
		if(stringToSizeT(_body,_sizetBody) == 0)
			return(0);
	}
    if(_server_name != "" )
        deletespaces(_server_name);
    if(_Root != "" )
        deletespaces(_Root);

return(1);
}
void srv::deletespaces(std::string &s)
{
    size_t i = 0;
    std::string temp;
    while(i < s.size())
    {
        while(s[i] == ' ')
            i++;
		if(s[i] != ' ')
		{
        	temp.push_back(s[i]);
        	i++;
		}
    }
	s = temp;
    //checker
	//std::cout << "s:"<< "|" << s << "|" << std::endl;
	//std::cout << "temp:"<< "|" << temp << "|" << std::endl;
	//return(s);
}

bool srv::stringToSizeT(const std::string& s, size_t &n) 
{
    std::istringstream iss(s);
    iss >> n;
    if (iss.fail()) 
	{
        // Lanzar una excepción si la conversión falla
        //throw std::runtime_error("Cannot convert string to size_t: " + s);
		return(0);
    }
	return(1);
}