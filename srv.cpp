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
            Location newLocation(locationBlock);
            array_of_location.push_back(newLocation);
        }
        else 
            break;
    }

}

/* unsigned long srv::ipToDecimal(const std::string& ip) 
{
    std::vector<int> octets;
    std::stringstream ss(ip);
    std::string item;

    // Separar la IP por los puntos
    while (std::getline(ss, item, '.')) 
    {
        int num;
        std::istringstream(item) >> num;
        octets.push_back(num);
    }

    // Verificar que tengamos exactamente cuatro octetos
    if (octets.size() != 4) {
        std::cerr << "Error: Dirección IP no válida." << std::endl;
        return 0;  // O alguna otra señal de error
    }

    // Combinar los octetos en un solo número
    this->decimalIp = 0;
    this->decimalIp += (octets[0] << 24);
    this->decimalIp += (octets[1] << 16);
    this->decimalIp += (octets[2] << 8);
    this->decimalIp += octets[3];
    return this->decimalIp;
} */
