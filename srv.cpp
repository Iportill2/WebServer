#include "dependences.hpp"
#include "srv.hpp"
#include "Config.hpp"
srv::srv(std::string serverBlock)
{
    //std::cout << "Default srv Constructor" << std::endl;
    //nullstrings();
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
int srv::countSubstring(const std::string& str, const std::string& sub)
{
    if (sub.length() == 0) 
        return 0;
    int count = 0;
    for (size_t offset = str.find(sub); offset != std::string::npos; offset = str.find(sub, offset + sub.length()))
    {
        ++count;
    }
    return count;
}
//void Config::createSrv()
void srv::setServerBlockValues(std::string s)
{
	size_t i =0;
	size_t Pos;
	size_t end;
	size_t count = 0;
	std::string HOST ="listen ";
    std::string NAME ="server_name ";
    std::string BODY = "body_size ";
    std::string ROOT ="root ";
	while(i < s.size())
	{
		if(_host.empty()) 
        {
            Pos = s.find(HOST, i); // Use a different variable for find
            Pos += HOST.size();
            end = s.find(":", Pos);
            _host = s.substr(Pos, end - Pos);
			//std::cout << _host << std::endl;
            i = end ;
            count++;
        }
        else if(_port.empty() && !_host.empty()) 
        {
        Pos += HOST.size() + 1;
    	end = s.find(";", Pos);
        _port = s.substr(Pos, end - Pos);
        i = end;
        count++;
        }
        else if(!_port.empty() && !_host.empty() && _server_name.empty()) 
        {
        Pos = s.find(NAME, i);
        Pos += NAME.size() ;
        end = s.find(";", Pos);
    	_server_name = s.substr(Pos, end - Pos);
        i = end;
        count++;
        }
        else if(!_port.empty() && !_host.empty() && !_server_name.empty() && _body.empty()) 
        {
        Pos = s.find(BODY, i);
        Pos += BODY.size() ;
    	end = s.find(";", Pos);
        _body = s.substr(Pos, end - Pos);
    	i = end  ;
        count++;
        }
        else if(!_port.empty() && !_host.empty() && !_server_name.empty() && !_body.empty() && _Root.empty())
        {
        Pos = s.find(ROOT, i);
        Pos += ROOT.size() ;
        end = s.find(";", Pos);
        _Root = s.substr(Pos, end - Pos);
        i = end ;
        count++;
        }

		i++;
	}
}
void srv::parseServerBlock(const std::string& serverBlock)
{
    size_t tmp;
    (void) tmp;
    std::istringstream f(serverBlock);
    std::string line;    
    size_t i = 0;
    std::stack<char> stak;

 /*    int count = 0; 
    size_t Pos;
    size_t end;

 */
    size_t abre;
    (void) abre;
    size_t cierra = 0;

	size_t abre2;
	std::string serverconfig;
    //(void) cierra;
/*     std::string llaves;

    size_t length;
    std::string sub; */
    
    while(i < serverBlock.size())
    {
        tmp = i;
        while(i < serverBlock.size() && serverBlock[i] != '{' && serverBlock[i] != '}')
            i++;

       /*  if(i == serverBlock.size())
            break; */

        if(serverBlock[i] == '{')
        {
            stak.push('{');
            //std::cout << RED<< "stak.size():" << stak.size() << std::endl;
            if(stak.size() == 1)
            {
                abre = i;
                std::cout << RED<< "abre:" << abre << std::endl;
            }
			else if( stak.size() == 2)
			{
				abre2 =i;
				std::cout << RED<< "abre2:" << abre2 << std::endl;
			}

        }
        else if (serverBlock[i] == '}')
        {
            std::cout << RED<< "stak.size():" << stak.size() << WHITE << std::endl;
            if(stak.size() == 1 )
            {
                cierra = i;
                std::cout << RED << "cierra:" << cierra << WHITE << std::endl;
            }
            stak.pop();
        }
		 //_host = serverBlock.substr(Pos, end - Pos);

                              /* 
            //break;
        i++;
        while (i < serverBlock.size() && !stak.empty())
        {
            if(serverBlock[i] == '{')
                stak.push(serverBlock[i]);
            else if(serverBlock[i] == '}')
                stak.pop();
                                sub = serverBlock.substr(end, end- Pos);
            else
            {
                while(stak.size() == 1 && count != 5)
                {
                    if(_host.empty()) 
                    {
                        Pos = serverBlock.find(HOST, i); // Use a different variable for find
                        Pos += HOST.size();
                        end = serverBlock.find(":", Pos);
                        _host = serverBlock.substr(Pos, end - Pos);
                        i = end ;
                        count++;
                    }
                    if(_port.empty() && !_host.empty()) 
                    {
                        Pos += HOST.size() + 1;
                        end = serverBlock.find(";", Pos);
                        _port = serverBlock.substr(Pos, end - Pos);
                        i = end + 1  ;
                        count++;
                    }
                    if(!_port.empty() && !_host.empty() && _server_name.empty()) 
                    {
                        Pos = serverBlock.find(NAME, i);
                        Pos += NAME.size() ;
                        end = serverBlock.find(";", Pos);
                        _server_name = serverBlock.substr(Pos, end - Pos);
                        i = end + 1  ;
                        count++;
                    }
                    if(!_port.empty() && !_host.empty() && !_server_name.empty() && _body.empty()) 
                    {
                        Pos = serverBlock.find(BODY, i);
                        Pos += BODY.size() ;
                        end = serverBlock.find(";", Pos);
                        _body = serverBlock.substr(Pos, end - Pos);
                        i = end + 1  ;
                        count++;
                    }
                    if(!_port.empty() && !_host.empty() && !_server_name.empty() && !_body.empty() && _Root.empty())
                    {
                        Pos = serverBlock.find(ROOT, i);
                        Pos += ROOT.size() ;
                        end = serverBlock.find(";", Pos);
                        _Root = serverBlock.substr(Pos, end - Pos);
                        i = end + 1  ;
                        count++;
                    }
                    if(stak.size() == 1)
                    {
                        Pos = serverBlock.find("location /");
    		            while (Pos < serverBlock.size()) 
    		            {
                            if(serverBlock[i] == '{')
                                stak.push('{');
                            else if (serverBlock[i] == '}')
                                stak.pop();
        		            Pos += std::string("location /").size(); // Skip "location "
        		            size_t endPos = serverBlock.find('}', Pos);

        		            if (endPos != std::string::npos) 
        		            {
            		            //std::string locationBlock = serverBlock.substr(Pos, endPos - Pos);
                                length = i - tmp;
                                if (tmp + length > serverBlock.size())
                                {
                                    length = serverBlock.size() - tmp;
                                }
                                Pos = serverBlock.find("location /");
                                end = serverBlock.find ("}");
                                Location newLocation(sub);
                                locationCount = countSubstring(serverBlock.substr(tmp, i - tmp), "location");
                                std::cout << CYAN << sub << std::endl;
                                array_of_location.push_back(newLocation);

            		            Pos = endPos + 1; // Skip "}"
                            }
                            //i = endPos;
                            std::cout << "i= " << i << std::endl;

                                std::cout << YELLOW << "XXXX" << WHITE << std::endl;
                                std::cout << YELLOW << "stak.size():" << stak.size() << WHITE << std::endl;

                                */ 
                        

    i++;
    }
			serverconfig = serverBlock.substr(abre,abre2+1 - abre);
			setServerBlockValues(serverconfig);
			std::cout << CYAN <<"serverconfig=" << serverconfig <<WHITE  <<std::endl;
			locationCount = countSubstring(serverBlock.substr(0,tmp), "location /");
			std::string locationblock = serverBlock.substr(abre2, serverBlock.size() - abre2);

			std::cout << "location= " << locationCount << std::endl;
			int e = 0;
			int start= 0;
			int ended = 0;
			std::string location;
			//Pos = serverBlock.find("location /");
			//Pos = serverBlock.find("location /");
			while(e < locationCount)//************************************************
			{
				start = locationblock.find("location /");
				ended = start + locationblock.find("}");
				location = locationblock.substr(start, ended - start);
				std::cout << "LOCATION->" << location << std::endl;
				e++;
			}
/*     if(checkstring() == 0)
		return; */
        std::cout << "host |" << _host << "|"<< std::endl;
    std::cout << "port |" << _port << "|"<< std::endl;
    std::cout << "server_name |" <<  _server_name <<"|"<< std::endl;
    std::cout << "body |" << _body << "|"<< std::endl;
    std::cout << "Root |" << _Root << "|"<< std::endl;
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
			return(0);
	}
    if(!_body.empty())
	{
        deletespaces(_body);
		if(stringToSizeT(_body,_sizetBody) == 0)
			return(0);
	}
    if(!_server_name.empty() )
        deletespaces(_server_name);
    if(!_Root.empty())
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