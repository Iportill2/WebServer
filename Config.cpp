#include "dependences.hpp"

Config::Config(const std::string& file): _file(file) {}

Config::Config() {}
Config::~Config() {}

bool Config::parse() 
{
	std::ifstream file(_file.c_str());
	if (!file.is_open()) {
		std::cerr << "Failed to open file: " << _file << std::endl;
		return false;
	}

	std::string line;
	std::string serverBlock;
	int braceCount = 0;
	while (std::getline(file, line)) 
	{

		if (line.empty()) continue;

		if (line.find("server") != std::string::npos && braceCount == 0) 
		{
			if (!serverBlock.empty()) 
			{
				_servers.push_back(Server(serverBlock));
			}
			serverBlock.clear();
		}

		serverBlock += line + "\n";

		if (line.find('{') != std::string::npos) 
		{
			braceCount++;
		}
		if (line.find('}') != std::string::npos) 
		{
			braceCount--;
			if (braceCount == 0 && !serverBlock.empty()) 
			{
				_servers.push_back(Server(serverBlock));
				serverBlock.clear();
			}
		}
	}

	file.close();
	return true;
}

void Config::load() 
{
	for (size_t i = 0; i < _servers.size(); ++i)
		_servers[i].abind();
}

void Config::validate() const 
{
	for (size_t i = 0; i < _servers.size(); ++i)
		_servers[i].validate();
}


const Server& Config::getServer(int port) const
{
	size_t i;


	for (i = 0; i < _servers.size(); ++i)
		if (_servers[i].port() == port)
			return (_servers[i]);
	throw std::runtime_error("Server not found for the specified port");
}

int Config::serverCount() 
{
	return _servers.size();
}

std::vector<int> Config::serverSockets() 
{
	std::vector<int> sockets;
	for (size_t i = 0; i < _servers.size(); ++i)
		sockets.push_back(_servers[i].fd());
	return sockets;
}

unsigned long Config::ipToDecimal(const std::string& ip) 
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
}