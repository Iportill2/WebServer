#ifndef CONFIG_HPP
# define CONFIG_HPP
#include "dependences.hpp"
class Config
{
	protected:
//ifstream de donde leeremos el archivo server.conf
	std::ifstream file;
//string donde guardaremos los datos leidos del archivo server.conf
	std::string Config_data;
//Define el puerto en el que el servidor escuchará las solicitudes
    int 		Port;
//Especifica la dirección IP en la que el servidor aceptará conexiones
//Usar 0.0.0.0 significa que el servidor es accesible en todas las interfaces de red
    std::string	Host;
//Directorio raíz desde donde el servidor servirá los archivos
    std::string	DocumentRoot;
//Define la ubicación del archivo de registro del servidor
	std::string LogFile;
//Especifica el tamaño máximo de la solicitud en bytes
	int			MaxRequestSize;
//Define el tiempo máximo de inactividad de una conexión antes de cerrarla, en segundos
	int			Timeout;
//Especifica el archivo que se servirá si se solicita un directorio
	std::string	DirectoryIndex;
//Configuración de errores personalizados
	std::string ErrorDocument_404;
	std::string ErrorDocument_500;
//Configuración de seguridad básica
	std::string ServerSignature_Off;
	std::string ServerTokens_Prod;
//Configuración de SSL/TLS
	std::string SSLEngine_on;
	std::string SSLCertificateFile;
	std::string SSLCertificateKeyFile;

//Id en binario para el hton
	unsigned long decimalIp;


public:
	//CANONICAL
	Config(std::string configName);
	//copy;
	//operator=;
    ~Config();

	bool openFile();
	void saveData();
	void printData();

	unsigned long ipToDecimal(const std::string& ip);
	//GETTERS

	//std::ifstream 	getfile() const ;
	std::string getConfig_data()const ;//
	int 		getPort() const;//

    std::string	getHost() const;
    std::string	getDocumentRoot()const ;
	std::string getLogFile()const ;
	int			getMaxRequestSize()const ;
	int			getTimeout()const ;
	std::string	getDirectoryIndex()const ;
	std::string getErrorDocument_404()const ;
	std::string getErrorDocument_500()const ;
	std::string getServerSignature_Off()const ;
	std::string getServerTokens_Prod()const ;
	std::string getSSLEngine_on()const ;
	std::string getSSLCertificateFile()const ;
	std::string getSSLCertificateKeyFile()const ;

	unsigned long getdecimalIp()const ;

};

#endif