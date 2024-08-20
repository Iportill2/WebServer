#pragma once

# include "dependences.hpp"
# include "Directory.hpp"

class Delete
{
    private:

    	int 						fd;
		std::string 				response;
		std::vector<std::string>	dir;

    public:

		Delete(int f);
		~Delete();

		void	sendForm();
		void	sendFile(std::string fi);

};