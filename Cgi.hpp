
#pragma once

# include "dependences.hpp"
# include "Error.hpp"
# include "Request.hpp"

class Cgi
{
    private:

    	Request     *rq;
        std::string url;
		std::vector<std::string>    envVect;

        std::string result;

        char        **_env;
        char 		res[128];
		int			fd;

        int         inFd;
        int         outFd;
        int         inPipe[2];
        int         outPipe[2];
		

    public:

        Cgi(Request *r, std::string  ur, int f);
        ~Cgi();

        void 		createGetEnv();
        void 		createPostEnv();
        void        setPost();
        void 		exec();
        

		void		sendResult();

};