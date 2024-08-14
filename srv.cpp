#include "dependences.hpp"
#include "srv.hpp"
#include "Config.hpp"
#include "Utils.hpp"
srv::srv()
{
    srv_ok = 1;
}


srv::srv(std::string serverBlock)
{
    //std::cout << "Default srv Constructor" << std::endl;
    srv_ok = parseServerBlock(serverBlock);
    if(srv_ok == 0)
        return;
    if(!arErr.empty() && !arErr[0].error_page.empty() && !arLoc.empty())
    {
        size_t i =0;
        while(i < arLoc.size() )
        {
            std::map<int, std::string>::iterator it = arErr[0].error_page.begin();
            while (it != arErr[0].error_page.end())
            {
                if(arLoc[i]._location == it->second)
                {
                    if(arErr[0].error_page.find(it->first) != arErr[0].error_page.end())
                    {
                        ErrorRoot.insert(std::make_pair(it->first, arLoc[i]._root + arErr[0].error_page[it->first]));
                        std::cout << YELLOW << "Key: " << it->first << ", Value: " << it->second << WHITE << std::endl;
                    }
                }
                ++it;
            }
            i++;
        }
    }
    readErrorRoot();
}
srv::~srv()
{
}

void srv::readErrorRoot()
{
    if(!arErr.empty() && !arErr[0].defaultErMap.empty() && !ErrorRoot.empty())
    {
        for (std::map<int, std::string>::iterator it = ErrorRoot.begin(); it != ErrorRoot.end(); ++it) 
        {
            if (arErr[0].defaultErMap.find(it->first) != arErr[0].defaultErMap.end()) 
            {
                
                std::ifstream file(it->second.c_str());
                if (file) 
                {
                    std::string st;
                    std::stringstream buffer;
                    buffer << file.rdbuf();

                    if(it->first == 200)
                        st = "200 OK";
                    else if(it->first == 201)
                        st= "201 Created";
                    else if(it->first == 202) 
                        st = "202 Accepted";
                    else if(it->first == 204) 
                        st = "204 No Content";
                    else if(it->first == 301) 
                        st = "301 Moved Permanently";
                    else if(it->first == 302) 
                        st = "302 Found";
                    else if(it->first == 303) 
                        st = "303 See Other";
                    else if(it->first == 304) 
                        st = "304 Not Modified";
                    else if(it->first == 400) 
                        st = "400 Bad Request";
                    else if(it->first == 401) 
                        st = "401 Unauthorized";
                    else if(it->first == 403) 
                        st = "403 FORBIDDEN";
                    else if(it->first == 404) 
                        st = "404 Not Found POTOTO";
                    else if(it->first == 405) 
                        st = "405 Method Not Allowed";
                    else if(it->first == 406) 
                        st = "406 Not Acceptable";
                    else if(it->first == 408) 
                        st = "408 Request Timeout";
                    else if(it->first == 409) 
                        st = "409 Conflict";
                    else if(it->first == 411) 
                        st = "411 Length Required";
                    else if(it->first == 413) 
                        st = "413 Payload Too Large";
                    else if(it->first == 414) 
                        st = "414 URI Too Long";
                    else if(it->first == 415) 
                        st = "415 Unsupported Media Type";
                    else if(it->first == 500) 
                        st = "500 Internal Server Error";
                    else if(it->first == 501) 
                        st = "501 Not Implemented";
                    else if(it->first == 502) 
                        st = "502 Bad Gateway";
                    else if(it->first == 503) 
                        st = "503 Service Unavailable";
                    else if(it->first == 505) 
                        st = "505 HTTP Version Not Supported";
                    std::string httpResponse = "HTTP/1.1 " + st + "\r\n";
                    httpResponse += "\r\n";
                    httpResponse += buffer.str();
                    arErr[0].defaultErMap[it->first] = httpResponse;
                } 
                else 
                    std::cout << "Could not open file " << it->second << "\n";
            }
        }
    }
/*     for (std::map<int, std::string>::iterator it = arErr[0].defaultErMap.begin(); it != arErr[0].defaultErMap.end(); ++it) 
    {
        std::cout << GREEN << it->first << CYAN << it->second << RED << "*******************************************************************************************\n"<< WHITE << std::endl;
    } */
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
                //arErr.push_back(line);
                std::string errorstring;
                //std::cout << YELLOW << line << WHITE <<"\n";
                errorstring = line + '\n';
                while (1)
                {
                    if (!std::getline(stream, line))
                    {
                        // Llegamos al final del stream, rompemos el bucle
                        break;
                    }
                    errorstring += line + '\n';
                    if (line.find('l') != std::string::npos)
                    {
                    std::cout << BLUE << errorstring << WHITE << std::endl;
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
    if(arErr.empty())//para evitar el segfault en arErr
    {
        std::string s = "";
        arErr.push_back(s);
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