#pragma once

# include "dependences.hpp"
# include "srv.hpp"
class Error
{
    private:

        int error;
		int	fd;
        static std::string ErrorPage404 ; 

    public:

        Error(int er, int fdescriptor, srv server);
        ~Error();

        static std::string	status(int error);
		std::string 		toString(const int &num);
        void				sendError();
};