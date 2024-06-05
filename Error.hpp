#pragma once

# include "dependences.hpp"

class Error
{
    private:

        int error;
		int	fd;

    public:

        Error(int er, int fdescriptor);
        ~Error();

        static std::string	status(int error);
		std::string 		toString(const int &num);
        void				sendError();
};