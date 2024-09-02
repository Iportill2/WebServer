#pragma once

# include "dependences.hpp"
# include "Request.hpp"
# include "Error.hpp"
# include "srv.hpp"

class Load
{
    private:

        Request   * rq;
		int			fd;
        std::string _url;
        srv         server;

        // std::string	boundary_clave;
        // std::string boundary_content;
        // std::string file_name;
        // std::string file_content;
        // std::string content_type;
        // std::string last_line;

        bool        finish;

    public:

        Load(Request * r, int f, std::string & url, srv & serv);

        ~Load();

        
        bool    createFile();
};