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
void srv::parseServerBlock(const std::string& serverBlock)
{
    size_t tmp;
    std::istringstream f(serverBlock);
    std::string line;    
    size_t i =0;
    std::stack<char> stak;

    int count = 0; 
    size_t Pos;
    size_t end;
    std::string HOST ="listen ";
    std::string NAME ="server_name ";
    std::string BODY = "body_size ";
    std::string ROOT ="root ";

    size_t abre;

    std::string llaves;

    size_t length;
    std::string sub;
    
    while(i < serverBlock.size())
    {
        tmp = i;
        while(i < serverBlock.size() && serverBlock[i] != '{' && serverBlock[i] != '}')
            i++;

        if(i == serverBlock.size())
            break;

        if(serverBlock[i] == '{')
            stak.push('{');
        else if (serverBlock[i] == '}')
            break;
        if(stak.size() == 2 && serverBlock[i] == '{')
            abre = i;

        i++;
        while (i < serverBlock.size() && !stak.empty())
        {
            if(serverBlock[i] == '{')
                stak.push(serverBlock[i]);
            else if(serverBlock[i] == '}')
                stak.pop();
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
                                sub = serverBlock.substr(end, end- Pos);
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
/*                             if(stak.size() == 2 )
                            { */

                                /* i++; */
                            /* }   */ 
                        }	
        		    }
                }

            } 
            i++;
        }
        if(checkstring() == 0)
			return;
        std::cout << "host |" << _host << "|"<< std::endl;
        std::cout << "port |" << _port << "|"<< std::endl;
        std::cout << "server_name |" <<  _server_name <<"|"<< std::endl;
        std::cout << "body |" << _body << "|"<< std::endl;
        std::cout << "Root |" << _Root << "|"<< std::endl;
    }
}
/* void srv::parseServerBlock(const std::string& serverBlock)  
{
    //std::map<std::string, std::string> result;
    std::string keys[] = {"listen ", _host, "server_name ", "body_size ", "root "};
    size_t pos, end;
    int i = 0;
	//size_t temppos;
    while (i < 5) 
	{
		if(i == 1)
			pos = serverBlock.find(_host);
		else
        	pos = serverBlock.find(keys[i]);

            if (pos != std::string::npos) 
		{ 
			if(i == 0)//host
			{
				pos += keys[i].size();
            	end = serverBlock.find(":", pos);
				if (end != std::string::npos) 
				{
					if(_host.empty())
						_host = serverBlock.substr(pos, end - pos);
					else
						std::cout  << "host:"<< _host  << " is filled" << std::endl;
				}
			}
			else if(i == 1)//port
			{
				pos += _host.length() + 1 ;
            	end = serverBlock.find(";", pos);
				if (end != std::string::npos) 
				{
					if(_port.empty())
						_port = serverBlock.substr(pos, end - pos);
					else
						std::cout  << "port:"<< _port  << " is filled" << std::endl;
				}
			}
			else if(i == 2)//server name
			{
            	pos += keys[i].length();
            	end = serverBlock.find(";", pos);
            	if (end != std::string::npos) 
				{
					if(_server_name.empty())
						_server_name = serverBlock.substr(pos, end - pos);
					else
						std::cout  << "I=" << i <<result[keys[i]]  << " is filled" << std::endl;
				}
			}
			else if(i == 3)//body
			{
            	pos += keys[i].length();
            	end = serverBlock.find(";", pos);
            	if (end != std::string::npos) 
				{
					if(_body.empty())
						_body = serverBlock.substr(pos, end - pos);
					else
						std::cout  << "I=" << i <<result[keys[i]]  << " is filled" << std::endl;
				}
			}
			else if(i == 4)//Root
			{
            	pos += keys[i].length();
            	end = serverBlock.find(";", pos);
            	if (end != std::string::npos) 
				{
					if(_Root.empty())
						_Root = serverBlock.substr(pos, end - pos);
					else
						std::cout  << "I=" << i <<result[keys[i]]  << " is filled" << std::endl;
				}
			}
			//pos = end;

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
        ++i;
    }
		std::cout << "host |" << _host << "|"<< std::endl;
		std::cout << "port |" << _port << "|"<< std::endl;
		std::cout << "server_name |" <<  _server_name <<"|"<< std::endl;
		std::cout << "body |" << _body << "|"<< std::endl;
		std::cout << "Root |" << _Root << "|"<< std::endl;
} */
/* void srv::parseServerBlock(const std::string& serverBlock) 
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

} */



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