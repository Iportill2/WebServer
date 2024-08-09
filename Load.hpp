#pragma once

# include "dependences.hpp"
# include "Request.hpp"

class Load
{
    private:

        Request   * rq;
		int			fd;

        std::string	boundary_clave;
        std::string boundary_content;
        std::string file_name;
        std::string file_content;
        std::string content_type;
        std::string last_line;

        bool        finish;

    public:

        Load(Request * r, int f);

        Load(std::string  bd, int f);//OBSOLETO
        ~Load();

        void    parse();
        void    createTextFile();
};