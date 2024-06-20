#pragma once

# include "dependences.hpp"

class Load
{
    private:

    	std::string body;
		std::string	value;
		std::string result;
		char 		res[128];
		int			fd;
		

    public:

        Load(std::string  bd, int f);
        ~Load();

        void 		parse();
        void 		exec();
        //std::string	getResult();
		void		sendResult();
};