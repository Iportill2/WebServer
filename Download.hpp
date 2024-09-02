#pragma once

# include "dependences.hpp"
# include "Directory.hpp"
# include "Request.hpp"

class Download
{
    private:

    	int 						fd;
		std::string					url;
		std::string 				response;
		std::vector<std::string>	dir;
		Request			        	*rq;

    public:

		Download(Request * r, std::string & ur, int f);
		~Download();

		void	sendForm();
		void	sendFile();

};