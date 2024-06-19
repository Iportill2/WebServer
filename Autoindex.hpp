#ifndef AUTOINDEX_HPP
# define AUTOINDEX_HPP
#include "dependences.hpp"
#include "Config.hpp"
#include "Server.hpp"
#include "srv.hpp"
#include "ErrorPage.hpp"
#include "Error.hpp"
class ErrprPage;
class Server;
class srv;
class Autoindex //: public Config
{
    public:

    srv _server;
    std::string directory_path;
    std::string error;
    size_t _i;
    int _fd;
    Autoindex(srv &server, int fd, size_t i);
    ~Autoindex();


    bool is_directory(const std::string& path);
    std::string generate_autoindex(const std::string& directory_path);
    void handle_request(const std::string& directory_path);
    void process_request(const std::string& path);

    void serve_file(const std::string& index_file);
};

#endif