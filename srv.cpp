#include "dependences.hpp"
#include "srv.hpp"
#include "Config.hpp"
srv::srv(std::string serverBlock)
{
    //std::cout << "Default srv Constructor" << std::endl;
    //nullstrings();
    if(parseServerBlock(serverBlock) == 0)
        return;

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

void srv::setServerBlockValues(std::string s)
{
	size_t i =0;
	size_t Pos;
	size_t end;

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
			std::cout <<"host="<<  _host << std::endl;
            i = end ;
            //std::cout <<"i="<<  i << std::endl;
        }
        else if(_port.empty() && !_host.empty()) 
        {
        //std::cout <<"i="<<  i << std::endl;
        Pos += HOST.size();
    	end = s.find(";", Pos);
        _port = s.substr(i, end - i);
        std::cout <<"port="<<  _port << std::endl;
        i = end;

        }
        else if(!_port.empty() && !_host.empty() && _server_name.empty()) 
        {
        Pos = s.find(NAME, i);
        Pos += NAME.size() ;
        end = s.find(";", Pos);
    	_server_name = s.substr(Pos, end - Pos);
        i = end;

        }
        else if(!_port.empty() && !_host.empty() && !_server_name.empty() && _body.empty()) 
        {
        Pos = s.find(BODY, i);
        Pos += BODY.size() ;
    	end = s.find(";", Pos);
        _body = s.substr(Pos, end - Pos);
    	i = end  ;

        }
        else if(!_port.empty() && !_host.empty() && !_server_name.empty() && !_body.empty() && _Root.empty())
        {
        Pos = s.find(ROOT, i);
        Pos += ROOT.size() ;
        end = s.find(";", Pos);
        _Root = s.substr(Pos, end - Pos);
        i = end ;

        }

		i++;
	}
}
bool srv::parseServerBlock(const std::string& serverBlock)
{
    size_t tmp;
    (void) tmp;
    std::istringstream f(serverBlock);
    std::string line;    
    size_t i = 0;
    std::stack<char> stak;

    size_t abre;
    (void) abre;
    size_t cierra = 0;

	size_t abre2;
    size_t locations;
	std::string serverconfig;

    
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
                //std::cout << RED<< "abre:" << abre << std::endl;//
            }
			else if( stak.size() == 2)
			{
				abre2 =i;
				//std::cout << RED<< "abre2:" << abre2 << std::endl;//
			}

        }
        else if (serverBlock[i] == '}')
        {
            //std::cout << RED<< "stak.size():" << stak.size() << WHITE << std::endl;//
            if(stak.size() == 1 )
            {
                cierra = i;
                //std::cout << RED << "cierra:" << cierra << WHITE << std::endl;//
                locations = serverBlock.find("location /");
                if(locations == std::numeric_limits<size_t>::max())
                {
                    std::cout << RED << "no locations in server" << WHITE << std::endl;
                    return 0;
                }
            }
            stak.pop();
        }
		
        i++;
    }
			serverconfig = serverBlock.substr(abre,abre2+1 - abre);
			setServerBlockValues(serverconfig);
            if(checkstring() == 0)
                return 0;
            
			//std::cout << CYAN <<"serverconfig=" << serverconfig <<WHITE  <<std::endl;
			locationCount = countSubstring(serverBlock.substr(0,tmp), "location /");
			std::string locationblock = serverBlock.substr(locations, cierra - locations);

			//std::cout <<  "location= " << locationCount << std::endl;
            //std::cout << RED <<  "locatioBlock= |" << locationblock << "|"<< WHITE << std::endl;

            int e = 0;
		 	while(e < locationCount) //  ************************************************
			{
                Location newLocation(locationblock);
                array_of_location.push_back(newLocation);
				e++;
            }
/*     
    std::cout << "host |" << _host << "|"<< std::endl;
    std::cout << "port |" << _port << "|"<< std::endl;
    std::cout << "server_name |" <<  _server_name <<"|"<< std::endl;
    std::cout << "body |" << _body << "|"<< std::endl;
    std::cout << "Root |" << _Root << "|"<< std::endl; */
    return 1;
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
        //std::cout << "host=" << _host << std::endl;
        deletespaces(_host);
		if(ipAddressToipNum(_host) == 0)
			return (0);
	}
    if(!_port.empty() )
	{
        //std::cout << "port=" << _port << std::endl;
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