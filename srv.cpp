#include "dependences.hpp"
#include "srv.hpp"
#include "Config.hpp"
#include "Utils.hpp"
srv::srv(const srv& other)
{
    this->locationCount = other.locationCount;
    this->srv_ok = other.srv_ok;


    this->_host = other._host;
    this-> _port = other._port;
    this->_server_name = other._server_name;
    this-> _body = other._body;
    this-> _Root = other._Root;
    this-> _ipNum = other._ipNum;

    this-> _sizetPort = other._sizetPort;
    this-> _sizetBody = other._sizetBody;

    this->locationCount = other.locationCount;
    this-> arLoc = other.arLoc;

    this-> arErr = other.arErr;

    this-> result = other.result;

    this->srv_ok = other.srv_ok;
}
srv::srv(std::string serverBlock)
{
    //std::cout << "Default srv Constructor" << std::endl;
    srv_ok = parseServerBlock(serverBlock);   
  
    //std::cout << "srv_ok:"<< srv_ok << std::endl;
        return;

}
srv::~srv()
{
    //std::cout << "srv Destructor" << std::endl;
}


std::vector<Location> &  srv::getlocations()
{
    return(arLoc);
}


bool srv::parseServerBlock(const std::string& s)
{
    std::string line;
    std::istringstream stream(s);
    //vars v;
    std::string listen ;
    size_t i = 0;
    while (std::getline(stream, line)) 
	{

		std::istringstream lineStream(line);
		std::string key;

		lineStream >> key;

        if (key == "listen")
        {
            lineStream >> listen;
            if (listen[listen.size() - 1] == ';')
            {
                listen = listen.substr(0, listen.size() - 1);
                //std::cout << "listen:" << listen << std::endl;
                while(listen[i]!= ':')
                {
                    i++;
                }
                if(_host.empty())
                    _host = listen.substr(0, i - 0);
                else
                    return(std::cout << RED << "twice host in server" << WHITE << std::endl,0);
                i++;
                if(_port.empty())
                    _port = listen.substr(i, listen.size() - i);
                else
                    return(std::cout << RED << "twice port in server" << WHITE << std::endl,0);

            }
            
        }
        if (key == "server_name")
        {
            lineStream >> _server_name;
            if (_server_name[_server_name.size() - 1] == ';')
                _server_name = _server_name.substr(0, _server_name.size() - 1);
        }

        if (key == "body_size")
        {
            lineStream >> _body;
            if (_body[_body.size() - 1] == ';')
                _body = _body.substr(0, _body.size() - 1);
        }
        if (key == "root")
        {
            lineStream >> _Root;
            if (_Root[_Root.size() - 1] == ';')
                _Root = _Root.substr(0, _Root.size() - 1);
        }
        if( key == "error_page")
        {
            {
                //std::cout << RED << "key:"<< key << WHITE << std::endl;
                
                std::string errorstring;
                errorstring = line + '\n';
                while (1)
                {
                    if (!std::getline(stream, line))
                    {
                        // Llegamos al final del stream, rompemos el bucle
                        break;
                    }
                    errorstring += line + '\n';
                    if (line.find('}') != std::string::npos)
                    {
                        arErr.push_back(errorstring);
                        break;
                    }
                }
            }
        }
        if (key == "location")
        {
            std::string loc;
            loc = line + '\n';
            while (1)
            {
                if (!std::getline(stream, line))
                    break;
                loc += line + '\n';
                if (line.find('}') != std::string::npos)
                {
                    Location newlocation(loc);
                    if(newlocation.lock_ok == 1)
                        arLoc.push_back(loc);
                    else
                        return(0);
                    break;
                }
            }
        }
	}
    if(_host.empty() && _port.empty() && _body.empty() && _Root.empty())
    {
        std::cout << "|" << _host << "|" << _port << "|" << _body << "|" << _Root << "|"<< std::endl;
        return(0);
    }
        
	if(checkstring() == 0)
        return 0;

    return(1);
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
    if(!_host.empty() )
	{
        deletespaces(_host);
		if(ipAddressToipNum(_host) == 0)
			return (0);
	}
    if(!_port.empty() )
	{
        deletespaces(_port);
		if(stringToSizeT(_port, _sizetPort) == 0)
			return(std::cout << "Error doing the conversion from _port to __sizetport" << std::endl,0);
	}
    if(!_body.empty())
	{
        deletespaces(_body);
		if(stringToSizeT(_body,_sizetBody) == 0)
			return(std::cout << "Error doing the conversion from _body to __sizetBody" << std::endl,0);
	}
    if(!_server_name.empty() )
        deletespaces(_server_name);
    if(!_Root.empty())
        deletespaces(_Root);

    
return(1);
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
}