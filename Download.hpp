#pragma once

# include "dependences.hpp"
# include "Directory.hpp"

class Download
{
    private:

    	int 						fd;
		std::string 				response;
		std::vector<std::string>	dir;

    public:

		Download(int f);
		~Download();

		void	sendForm();
		void	sendFile(std::string fi);

};