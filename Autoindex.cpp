#include "Autoindex.hpp"
#include "dependences.hpp"

Autoindex::Autoindex(std::string path) 
{
    std::cout <<"Constructor de Autoindex" << std::endl;
     // Example usage
   // std::string directory_path = "."; // Current directory
    std::cout << GREEN << path << WHITE << std::endl;
    handle_request(path);
}
Autoindex::~Autoindex()
{
    std::cout << "Destructor de Autoindex" << std::endl;
}
// Helper function to check if path is a directory
bool Autoindex::is_directory(const std::string& path) 
{
    struct stat statbuf;
    if (stat(path.c_str(), &statbuf) != 0) 
    {
        return false;
    }
    std::cout << "HHHH" <<std::endl;
    return S_ISDIR(statbuf.st_mode);
}

// Function to generate autoindex HTML
std::string Autoindex::generate_autoindex(const std::string& directory_path) 
{
    DIR *dir;
    struct dirent *entry;
    std::ostringstream html;

    dir = opendir(directory_path.c_str());
    if (dir == NULL) 
    {
        return "<html><body><h1>Unable to open directory</h1></body></html>";
    }

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

// Example function to handle a request and send a response
void Autoindex::handle_request(const std::string& directory_path) 
{
    std::cout << RED << "XXX" << WHITE << std::endl;
    std::string response;

    if (is_directory(directory_path)) 
    {
        response = generate_autoindex(directory_path);
    } 
    else 
    {
        response = "<html><body><h1>Not Found</h1></body></html>";
    }

    // Send HTTP response (pseudo code, replace with your actual send function)
    std::cout << "HTTP/1.1 200 OK\r\n";
    std::cout << "Content-Type: text/html\r\n";
    std::cout << "Content-Length: " << response.size() << "\r\n";
    std::cout << "\r\n";
    std::cout << response;
}


///////////////////////////////////////////////////
void Autoindex::serve_file(const std::string& index_file)
{
    (void) index_file;
}


void Autoindex::process_request(const std::string& path) 
{
    std::string index_file = path + "/index.html";
    //std::cout << RED << index_file << WHITE << std::endl;
    struct stat buffer;
    
    // Check if index.html exists
    if (stat(index_file.c_str(), &buffer) == 0) 
    {
        // Serve the index.html file (pseudo code)
        serve_file(index_file);
    } 
    else 
    {
        // Generate and serve the autoindex
        handle_request(path);
    }
}


