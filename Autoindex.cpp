#include "Autoindex.hpp"
#include "dependences.hpp"


Autoindex::Autoindex(srv& server, int fd, size_t i) 
{
    //std::cout <<"Constructor de Autoindex" << std::endl;
    _i = i;
    _fd = fd;
    //directory_path = server.arLoc[i]._root;
	//std::cout << RED << "server.arLoc[i]._root=" << server.arLoc[i]._root << WHITE <<"\n";
/*     if(!server.arErr.empty())
        error = server.ErrorRoot; */
    //std::cout << YELLOW << "server.arLoc[i]._location=" << server.arLoc[i]._location <<  WHITE << std::endl;
    handle_request(server.arLoc[i]._root); 
   
}
Autoindex::~Autoindex()
{
    //std::cout << "Destructor de Autoindex" << std::endl;
}
void Autoindex::handle_request(const std::string& directory_path) 
{
    std::string response;
    std::ostringstream oss;

    if (is_directory(directory_path)) 
	{
		//std::cout << RED << "gereateautoindex" << WHITE <<"\n";
        response = generate_autoindex(directory_path);

	}
    else 
    {
		//std::cout << RED << "NO gereateautoindex\n" << WHITE <<"\n";
        std::ifstream file( directory_path.c_str());

        if (file)
        {
            std::stringstream buffer;
            buffer << file.rdbuf();
            response = buffer.str();
            //std::cout<< RED << response << WHITE << std::endl;
            file.close();
        }
        else
		{
			//std::cout << RED << "HOLA\n" << WHITE <<"\n";
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

    // Inicio del HTML con estilos modernos
    html << "<!DOCTYPE html>\n";
    html << "<html lang=\"es\">\n";
    html << "<head>\n";
    html << "    <meta charset=\"UTF-8\">\n";
    html << "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n";
    html << "    <title>Índice de " << directory_path << "</title>\n";
    html << "    <link rel=\"icon\" href=\"/42favicon.png\" type=\"image/png\">\n";
    html << "    <style>\n";
    html << "        * {\n";
    html << "            margin: 0;\n";
    html << "            padding: 0;\n";
    html << "            box-sizing: border-box;\n";
    html << "        }\n";
    html << "        body {\n";
    html << "            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;\n";
    html << "            background: linear-gradient(135deg, #1e3c72 0%, #2a5298 100%);\n";
    html << "            min-height: 100vh;\n";
    html << "            display: flex;\n";
    html << "            align-items: center;\n";
    html << "            justify-content: center;\n";
    html << "            padding: 20px;\n";
    html << "        }\n";
    html << "        .main-container {\n";
    html << "            background: rgba(255, 255, 255, 0.95);\n";
    html << "            backdrop-filter: blur(10px);\n";
    html << "            border-radius: 20px;\n";
    html << "            box-shadow: 0 25px 50px rgba(0, 0, 0, 0.15);\n";
    html << "            padding: 50px;\n";
    html << "            max-width: 900px;\n";
    html << "            width: 100%;\n";
    html << "            position: relative;\n";
    html << "            overflow: hidden;\n";
    html << "        }\n";
    html << "        .main-container::before {\n";
    html << "            content: '';\n";
    html << "            position: absolute;\n";
    html << "            top: 0;\n";
    html << "            left: 0;\n";
    html << "            right: 0;\n";
    html << "            height: 4px;\n";
    html << "            background: linear-gradient(90deg, #00d4ff, #090979);\n";
    html << "        }\n";
    html << "        h1 {\n";
    html << "            font-size: 2.5rem;\n";
    html << "            font-weight: 700;\n";
    html << "            color: #2c3e50;\n";
    html << "            margin-bottom: 30px;\n";
    html << "            text-align: center;\n";
    html << "        }\n";
    html << "        table {\n";
    html << "            width: 100%;\n";
    html << "            border-collapse: collapse;\n";
    html << "            margin: 20px 0;\n";
    html << "            background: rgba(236, 240, 241, 0.7);\n";
    html << "            border-radius: 10px;\n";
    html << "            overflow: hidden;\n";
    html << "        }\n";
    html << "        th, td {\n";
    html << "            padding: 15px;\n";
    html << "            text-align: left;\n";
    html << "            border-bottom: 1px solid #ddd;\n";
    html << "        }\n";
    html << "        th {\n";
    html << "            background: linear-gradient(45deg, #3498db, #2980b9);\n";
    html << "            color: white;\n";
    html << "            font-weight: 600;\n";
    html << "        }\n";
    html << "        tr:hover {\n";
    html << "            background-color: rgba(52, 152, 219, 0.1);\n";
    html << "        }\n";
    html << "        a {\n";
    html << "            color: #2980b9;\n";
    html << "            text-decoration: none;\n";
    html << "            font-weight: 500;\n";
    html << "            transition: color 0.3s ease;\n";
    html << "        }\n";
    html << "        a:hover {\n";
    html << "            color: #3498db;\n";
    html << "            text-decoration: underline;\n";
    html << "        }\n";
    html << "        .directory {\n";
    html << "            color: #e67e22;\n";
    html << "            font-weight: bold;\n";
    html << "        }\n";
    html << "        .footer {\n";
    html << "            text-align: center;\n";
    html << "            margin-top: 30px;\n";
    html << "            color: #7f8c8d;\n";
    html << "            font-size: 0.9rem;\n";
    html << "        }\n";
    html << "        .back-button {\n";
    html << "            display: inline-block;\n";
    html << "            margin-top: 20px;\n";
    html << "            padding: 10px 20px;\n";
    html << "            background: linear-gradient(45deg, #3498db, #2980b9);\n";
    html << "            color: white;\n";
    html << "            border-radius: 50px;\n";
    html << "            text-decoration: none;\n";
    html << "            font-weight: 600;\n";
    html << "            transition: all 0.3s ease;\n";
    html << "        }\n";
    html << "        .back-button:hover {\n";
    html << "            transform: translateY(-2px);\n";
    html << "            box-shadow: 0 8px 15px rgba(52, 152, 219, 0.3);\n";
    html << "            text-decoration: none;\n";
    html << "        }\n";
    html << "    </style>\n";
    html << "</head>\n";
    html << "<body>\n";
    html << "    <div class=\"main-container\">\n";
    html << "        <h1>Índice de " << directory_path << "</h1>\n";
    html << "        <table>\n";
    html << "            <tr>\n";
    html << "                <th>Nombre</th>\n";
    html << "                <th>Tamaño</th>\n";
    html << "                <th>Última modificación</th>\n";
    html << "            </tr>\n";

    // Entrada para el directorio padre (..)
    html << "            <tr>\n";
    html << "                <td><a href=\"../\" class=\"directory\">..</a></td>\n";
    html << "                <td>-</td>\n";
    html << "                <td>-</td>\n";
    html << "            </tr>\n";

    while ((entry = readdir(dir)) != NULL) 
    {
        std::string name = entry->d_name;
        if (name == "." /* || name == ".." */)
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

        html << "            <tr>\n";

        if (is_directory(full_path)) 
        {
            if(full_path[0] == '.' && full_path[1] == '/')
            {
                full_path = full_path.substr(1);
                std::cout << YELLOW << "full_path=" << full_path << WHITE << std::endl;
            }
            html << "                <td><a href=\"" << full_path << "/\" class=\"directory\">" << name << "/</a></td>\n";
            html << "                <td>-</td>\n";  // Sin tamaño para directorios
        } 
        else 
        {
            if(full_path[0] == '.' && full_path[1] == '/')
            {
                std::cout << GREEN << "full_path=" << full_path << WHITE << std::endl;
                full_path = full_path.substr(1);
            }
            html << "                <td><a href=\"" << full_path  << "\">" << name << "</a></td>\n";
            html << "                <td>" << filestat.st_size << " bytes</td>\n";
        }

        html << "                <td>" << timebuf << "</td>\n";
        html << "            </tr>\n";
    }
    closedir(dir);

    html << "        </table>\n";
    html << "        <div class=\"footer\">\n";
    html << "            <p>WebServ - Proyecto 42</p>\n";
    html << "            <a href=\"javascript:history.back()\" class=\"back-button\">Volver</a>\n";
    html << "        </div>\n";
    html << "    </div>\n";
    html << "</body>\n";
    html << "</html>\n";
    
    return html.str();
}
