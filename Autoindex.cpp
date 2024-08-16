#include "Autoindex.hpp"
#include "dependences.hpp"


Autoindex::Autoindex(srv& server, int fd, size_t i) 
{
    std::cout <<"Constructor de Autoindex" << std::endl;
    _i = i;
    _fd = fd;
    //directory_path = server.arLoc[i]._root;
	std::cout << RED << server.arLoc[i]._root << WHITE <<"\n";
/*     if(!server.arErr.empty())
        error = server.ErrorRoot; */
    handle_request(server.arLoc[i]._root); 
   
}
Autoindex::~Autoindex()
{
    std::cout << "Destructor de Autoindex" << std::endl;
}
void Autoindex::handle_request(const std::string& directory_path) 
{
    std::string response;
    std::ostringstream oss;

    if (is_directory(directory_path)) 
	{
		std::cout << RED << "gereateautoindex" << WHITE <<"\n";
        response = generate_autoindex(directory_path);

	}
    else 
    {
		std::cout << RED << "NO gereateautoindex\n" << WHITE <<"\n";
        std::ifstream file( directory_path.c_str());

        if (file)
        {
            std::stringstream buffer;
            buffer << file.rdbuf();
            response = buffer.str();
            std::cout<< RED << response << WHITE << std::endl;
            file.close();
        }
        else
		{
			std::cout << RED << "HOLA\n" << WHITE <<"\n";
            return; 
		}
    }

    // metemos la info del html y del index que hemos creado para el index en un ostringstream
    oss << "HTTP/1.1 200 OK\r\n";
    oss << "Content-Type: text/html\r\n";
    oss << "Content-Length: " << response.size() << "\r\n";
    oss << "\r\n";
    oss << response;
    std::string str = oss.str();
    size_t n = str.size();
    char* cstr = new char[str.length() + 1];
    std::strcpy(cstr, str.c_str());
    write (_fd, cstr, n);
    delete [] cstr;
}
bool Autoindex::is_directory(const std::string& path) 
{
    struct stat statbuf;
    if (stat(path.c_str(), &statbuf) != 0) 
        return false;
    return S_ISDIR(statbuf.st_mode);
}


std::string Autoindex::generate_autoindex(const std::string& directory_path) 
{
    DIR *dir;
    struct dirent *entry;
    std::ostringstream html;

    dir = opendir(directory_path.c_str());
    if (dir == NULL) 
        return "<html><body><h1>Unable to open directory</h1></body></html>";

    html << "<html><head><title>Index of " << directory_path << "</title></head>";
    html << "<body><h1>Index of " << directory_path << "</h1>";
    html << "<table>";
    html << "<tr><th>Name</th><th>Size</th><th>Last Modified</th></tr>";

    while ((entry = readdir(dir)) != NULL) 
    {
        std::string name = entry->d_name;
        if (name == "." || name == "..")
        {
            continue;
        }
        std::string full_path = directory_path + "/" + name;

        struct stat filestat;
        if (stat(full_path.c_str(), &filestat) != 0) 
        {
            continue; // Error al obtener información del archivo
        }

        // Formatear la fecha de modificación
        char timebuf[80];
        struct tm *timeinfo;
        timeinfo = localtime(&filestat.st_mtime);
        strftime(timebuf, sizeof(timebuf), "%Y-%m-%d %H:%M:%S", timeinfo);

        html << "<tr>";

        if (is_directory(full_path)) 
        {
            html << "<td><a href=\"" << name << "/\">" << name << "/</a></td>";
            html << "<td>-</td>";  // Sin tamaño para directorios
        } 
        else 
        {
            html << "<td><a href=\"" << name << "\">" << name << "</a></td>";
            html << "<td>" << filestat.st_size << " bytes</td>";
        }

        html << "<td>" << timebuf << "</td>";
        html << "</tr>";
    }
    closedir(dir);

    html << "</table></body></html>";
    return html.str();
}



/*
#include <iostream>
#include <sstream>
#include <fstream>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <cstring>

class Autoindex {
public:
    Autoindex(srv& server, int fd, size_t i);
    ~Autoindex();

private:
    void handle_request(const std::string& directory_path);
    bool is_directory(const std::string& path);
    std::string generate_autoindex(const std::string& directory_path);

    int _fd;
    size_t _i;
    std::string error;
};

Autoindex::Autoindex(srv& server, int fd, size_t i) 
    : _fd(fd), _i(i) // Usar lista de inicialización
{
    std::cout << "Constructor de Autoindex" << std::endl;

    std::cout << "Root path: " << server.arLoc[i]._root << std::endl;

    // Si hay un error configurado en el servidor, guardarlo
    // if (!server.arErr.empty()) 
    //     error = server.ErrorRoot;

    handle_request(server.arLoc[i]._root); 
}

Autoindex::~Autoindex() 
{
    std::cout << "Destructor de Autoindex" << std::endl;
}

void Autoindex::handle_request(const std::string& directory_path) 
{
    std::string response;
    std::ostringstream oss;

    if (is_directory(directory_path)) 
    {
        std::cout << "Generando autoindex...\n";
        response = generate_autoindex(directory_path);
    } 
    else 
    {
        std::ifstream file(directory_path.c_str());

        if (file)
        {
            std::stringstream buffer;
            buffer << file.rdbuf();
            response = buffer.str();
            file.close();
        } 
        else 
        {
            std::cerr << "Error: No se pudo abrir el archivo.\n";
            return;
        }
    }

    oss << "HTTP/1.1 200 OK\r\n";
    oss << "Content-Type: text/html\r\n";
    oss << "Content-Length: " << response.size() << "\r\n";
    oss << "\r\n";
    oss << response;

    std::string str = oss.str();
    write(_fd, str.c_str(), str.size());
}

bool Autoindex::is_directory(const std::string& path) 
{
    struct stat statbuf;
    if (stat(path.c_str(), &statbuf) != 0) 
    {
        std::cerr << "Error: No se pudo obtener la información del directorio.\n";
        return false;
    }
    return S_ISDIR(statbuf.st_mode);
}

std::string Autoindex::generate_autoindex(const std::string& directory_path) 
{
    DIR *dir;
    struct dirent *entry;
    std::ostringstream html;

    dir = opendir(directory_path.c_str());
    if (dir == NULL) 
    {
        std::cerr << "Error: No se pudo abrir el directorio.\n";
        return "<html><body><h1>Unable to open directory</h1></body></html>";
    }

    html << "<html><head><title>Index of " << directory_path << "</title></head>";
    html << "<body><h1>Index of " << directory_path << "</h1><ul>";

    while ((entry = readdir(dir)) != NULL) 
    {
        std::string name = entry->d_name;
        if (name == "." || name == "..") // Ignorar los directorios "." y ".."
        {
            continue;
        }

        std::string full_path = directory_path + "/" + name;

        if (is_directory(full_path)) 
        {
            html << "<li><a href=\"" << name << "/\">" << name << "/</a></li>";
        } 
        else 
        {
            html << "<li><a href=\"" << name << "\">" << name << "</a></li>";
        }
    }
    closedir(dir);

    html << "</ul></body></html>";
    return html.str();
}

*/





