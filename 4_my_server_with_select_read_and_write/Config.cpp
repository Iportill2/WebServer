#include "Config.hpp"
#include "dependences.hpp"


//false 0
//true 1
#include <iostream>
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

Config::Config(std::string configName)
{
    this->Config_data = configName;
    std::cout << "Config Constructor" << std::endl;
    std::cout << "Config_data: " << this->Config_data << std::endl;
    std::cout << false << std::endl;
    if(openFile() == true)
	{
        saveData();
	}
	printData();
}

Config::~Config()
{
    std::cout << "Config Destructor" << std::endl;
}


bool Config::openFile()
{
    this->file.open(this->Config_data, std::ios::in);
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
    //std::cout << "saveData" << std::endl;
   // std::cout << this->Config_data << std::endl;
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
            int count = 0;

            lineStream >> key >> value;
            if (key == "Port") 
            {
                this->Port = std::stoi(line.substr(line.find(" ") + 1));
            }
			else if(key == "Host")
			{
                this->Host = std::stoi(line.substr(line.find(" ") + 1));
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
            else if(key == "ErrorDocument" && count == 0)
            {
                this->ErrorDocument_404 = line.substr(line.find(" ") + 1);
                count++;
            }
            else if(key == "ErrorDocument" && count == 1)
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
/*
*/
}



