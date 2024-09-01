#pragma once

# include "dependences.hpp"
# include "Directory.hpp"
# include "Error.hpp"

class Delete
{
    private:

    	int 						fd;
		std::string					url;
		std::string 				response;
		std::vector<std::string>	dir;

    public:

		Delete(std::string & ur, int f);
		~Delete();

		int		DeleteResource();
		bool	DeleteFolder(std::string ur);
		bool	DeleteFile(std::string ur);
		void	sendResponseOk();

};