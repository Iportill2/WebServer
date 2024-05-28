
#include "dependences.hpp"


//false 0
//true 1

/*
 open:

std::ios::in: Abre el archivo para lectura.

std::ios::out: Abre el archivo para escritura.

std::ios::binar<wbr>y: Abre el archivo en modo binario,
 sin realizar ninguna conversión de fin de línea.

std::ios::ate: Se posiciona al final del archivo 
inmediatamente después de abrirlo.

std::ios::app: Todos los datos escritos en el 
archivo se añadirán al final del archivo, 
preservando el contenido existente (append).

std::ios::trunc<wbr>: Si el archivo ya existe, 
su contenido se trunca antes de abrir el archivo 
(es decir, se borra el contenido existente)
*/

Config::Config()
{
    std::cout << "Default Config Constructor" << std::endl;
    this->Config_data = "";
    this->Port = 8080;
    this->Host = "127.0.0.1"; //0.0.0.0 //significa que el servidor es accesible en todas las interfaces de red
    this->DocumentRoot = "./pagina1";
    this->LogFile = "/var/log/myserver.log";
    this->MaxRequestSize = 1048576;
    this->Timeout = 30;
    this->DirectoryIndex = "./pagina1/index.html";
    this->ErrorDocument_404 = "./errors/404.html ";
    this->ErrorDocument_500 = "./errors/500.html";
    this->ServerSignature_Off = "Off";
    this->ServerTokens_Prod = "Prod";
    this->SSLEngine_on = "on";
    this->SSLCertificateFile = "/etc/ssl/certs/myserver.crt";
    this->SSLCertificateKeyFile = "/etc/ssl/private/myserver.key";
    this->decimalIp = ipToDecimal(this->Host);
	printData();
}

Config::Config(std::string configName)
{
    std::cout << "Config Constructor" << std::endl;
    this->Config_data = configName;
    std::cout << "Config_data: " << this->Config_data << std::endl;
    if(openFile() == true)
	{
        saveData();
	}
    else
    {
        return;
    }
	printData();
}

Config::~Config()
{
    std::cout << "Config Destructor" << std::endl;
}


bool Config::openFile()
{
    this->file.open(this->Config_data.c_str(), std::ios::in);
    if (this->file.is_open() == false) 
    {
        std::cerr << RED << "No se pudo abrir el archivo." << WHITE << std::endl;
        return 0;
    }
    std::cerr << RED << "Se pudo abrir el archivo." << WHITE << std::endl;
    std::stringstream buffer;
    buffer << file.rdbuf();

    // Convertir el contenido del stringstream en un string
    this->Config_data = buffer.str();
    //std::cout << this->Config_data << std::endl;//para printear el contenido del archivo
    file.close();
    return 1;
}
void Config::saveData()
{
    std::string line;
    std::istringstream file(this->Config_data);
    std::string a = "Port";
    while (std::getline(file, line)) 
    {
        if (!line.empty() && line[0] != '#') 
        {
            std::istringstream lineStream(line);
			std::string key;
        	int value;

            lineStream >> key >> value;
            if (key == "Port") 
            {
                std::istringstream iss(line.substr(line.find(" ") + 1));
                int num;
                iss >> num;
                this->Port = num;
            }
			else if(key == "Host")
			{
                this->Host = line.substr(line.find(" ") + 1);
			}
            else if(key == "DocumentRoot")
            {
                this->DocumentRoot = line.substr(line.find(" ") + 1);
            }
            else if(key == "LogFile")
            {
                this->LogFile = line.substr(line.find(" ") + 1);
            }
            else if(key == "MaxRequestSize")
            {
                this->MaxRequestSize = value;
            }
            else if(key == "Timeout")
            {
                this->Timeout = value;
            }
            else if(key == "DirectoryIndex")
            {
                this->DirectoryIndex = line.substr(line.find(" ") + 1);
            }
            else if(key == "ErrorDocument404")
            {
                this->ErrorDocument_404 = line.substr(line.find(" ") + 1);
            }
            else if(key == "ErrorDocument500")
            {
                this->ErrorDocument_500 = line.substr(line.find(" ") + 1);
            }
            else if(key == "ServerSignature")
            {
                this->ServerSignature_Off = line.substr(line.find(" ") + 1);
            }
            else if(key == "ServerTokens")
            {
                this->ServerTokens_Prod = line.substr(line.find(" ") + 1);
            }
            else if(key == "SSLEngine")
            {
                this->SSLEngine_on = line.substr(line.find(" ") + 1);
            }
            else if(key == "SSLCertificateFile")
            {
                this->SSLCertificateFile = line.substr(line.find(" ") + 1);
            }
            else if(key == "SSLCertificateKeyFile")
            {
                this->SSLCertificateKeyFile = line.substr(line.find(" ") + 1);
            }
            else
            {
                std::cerr <<  RED << "Error: Configuración no válida." << WHITE << std::endl;
            }

        }
    }
    decimalIp = ipToDecimal(Host);
}
void Config::printData()
{
	std::cout << GREEN << "Port: " << YELLOW << this->Port << WHITE << std::endl;
	std::cout << GREEN << "Host: " << YELLOW << this->Host << WHITE << std::endl;
	std::cout << GREEN << "DocumentRoot: " << YELLOW << this->DocumentRoot << WHITE << std::endl;
	std::cout << GREEN << "LogFile: " << YELLOW << this->LogFile << WHITE << std::endl;
	std::cout << GREEN << "MaxRequestSize: " << YELLOW << this->MaxRequestSize << WHITE << std::endl;
	std::cout << GREEN << "Timeout: " << YELLOW << this->Timeout << WHITE << std::endl;
	std::cout << GREEN << "DirectoryIndex: " << YELLOW << this->DirectoryIndex << WHITE << std::endl;
	std::cout << GREEN << "ErrorDocument_404: " << YELLOW << this->ErrorDocument_404 << WHITE << std::endl;
	std::cout << GREEN << "ErrorDocument_500: " << YELLOW << this->ErrorDocument_500 << WHITE << std::endl;
	std::cout << GREEN << "ServerSignature_Off: " << YELLOW << this->ServerSignature_Off << WHITE << std::endl;
	std::cout << GREEN << "ServerTokens_Prod: " << YELLOW << this->ServerTokens_Prod << WHITE << std::endl;
	std::cout << GREEN << "SSLEngine_on: " << YELLOW << this->SSLEngine_on << WHITE << std::endl;
	std::cout << GREEN << "SSLCertificateFile: " << YELLOW << this->SSLCertificateFile << WHITE << std::endl;
	std::cout << GREEN << "SSLCertificateKeyFile: " << YELLOW << this->SSLCertificateKeyFile << WHITE << std::endl;
    std::cout << GREEN << "decimalIp: " << YELLOW << this->decimalIp << WHITE << std::endl;
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

//GETTERS
/* std::ifstream Config::getfile() const
{
    return this->file;
} */
std::string  Config::getConfig_data() const
{
    return this->Config_data;
}
int Config::getPort() const
{
    return this->Port;
}
std::string Config::getHost() const
{
    return this->Host;
}
std::string Config::getDocumentRoot() const
{
    return this->DocumentRoot;
}
std::string Config::getLogFile() const
{
    return this->LogFile;
}
int Config::getMaxRequestSize() const
{
    return this->MaxRequestSize;
}
int Config::getTimeout() const
{
    return this->Timeout;
}
std::string Config::getDirectoryIndex() const
{
    return this->DirectoryIndex;
}
std::string Config::getErrorDocument_404() const
{
    return this->ErrorDocument_404;
}
std::string Config::getErrorDocument_500() const
{
    return this->ErrorDocument_500;
}
std::string Config::getServerSignature_Off() const
{
    return this->ServerSignature_Off;
}
std::string Config::getServerTokens_Prod() const
{
    return this->ServerTokens_Prod;
}
std::string Config::getSSLEngine_on() const
{
    return this->SSLEngine_on;
}
std::string Config::getSSLCertificateFile() const
{
    return this->SSLCertificateFile;
}
std::string Config::getSSLCertificateKeyFile() const
{
    return this->SSLCertificateKeyFile;
}
unsigned long Config::getdecimalIp() const
{
    return this->decimalIp;
}
