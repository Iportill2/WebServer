
#pragma once

# include "dependences.hpp"
# include "Error.hpp"

class Cgi
{
    private:

    	std::string body;
		std::string	value;
		std::string result;
		char 		res[128];
		int			fd;
		std::string exe_name;

    public:

        Cgi(std::string  bd, int f, std::string exename);
        ~Cgi();

        void 		parse();
        void 		exec();
        //std::string	getResult();
		void		sendResult();

};