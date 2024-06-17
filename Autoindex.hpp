#ifndef AUTOINDEX_HPP
# define AUTOINDEX_HPP
#include "dependences.hpp"
#include "Config.hpp"

class Autoindex //: public Config
{
    public:

    int _fd;
    Autoindex(std::string path, int fd);
    ~Autoindex();


    bool is_directory(const std::string& path);
    std::string generate_autoindex(const std::string& directory_path);
    void handle_request(const std::string& directory_path);
    void process_request(const std::string& path);

    void serve_file(const std::string& index_file);
};

#endif