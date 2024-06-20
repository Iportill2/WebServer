#include "Autoindex.hpp"
#include "dependences.hpp"


Autoindex::Autoindex(srv& server, int fd, size_t i) 
{
    std::cout <<"Constructor de Autoindex" << std::endl;
    _i = i;
    _fd = fd;
    _server = server;
    directory_path = server.arLoc[i]._root;
    if(!server.arErr.empty())
        error = server.arErr[0].ErrorRoot;
    handle_request(directory_path); 
   
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
        response = generate_autoindex(directory_path);
    else 
    {
        std::ifstream file( error.c_str());

        if (file)
        {
            std::stringstream buffer;
            buffer << file.rdbuf();
            response = buffer.str();
            std::cout<< RED << response << WHITE << std::endl;
            file.close();
        }
        else
            return; 
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
    html << "<body><h1>Index of " << directory_path << "</h1><ul>";

    while ((entry = readdir(dir)) != NULL) 
    {
        std::string name = entry->d_name;
        if (name == ".")
        {
            continue;
        }
        std::string full_path = directory_path + "/" + name;

        if (is_directory(full_path)) 
        {
            html << "<li><a href=\"" << name << "/\">" << name << "/</a></li>";
            std::string s = html.str() ;
        } 
        else
        {
            int i = open(directory_path.c_str(),O_RDONLY);
            if(i < 0)
            {
                close(i);
                if(error.empty())
                    return "<html><body><h1>Unable to open directory</h1></body></html>";
                else
                {
                    std::ifstream file( error.c_str());
                    std::string response;
                    if (file)
                    {
                        std::stringstream buffer;
                        buffer << file.rdbuf();
                        response = buffer.str();
                        std::cout<< RED << response << WHITE << std::endl;
                        file.close();
                        std::string s ="<html><body><h1>"+ response;
                        s +"</h1></body></html>";
                        html << s;
                        return html.str();
                    }
                     else
                        return "<html><body><h1>PATAATA</h1></body></html>"; 
                }

            }
            html << "<li><a href=\"" << name << "\">" << name << "</a></li>";
        }
    }
    closedir(dir);

    html << "</ul></body></html>";
    return html.str();
}








