#pragma once

# include "dependences.hpp"
# include "Directory.hpp"
//# include "Request.hpp"

class Dinamic
{
    private:

        int							fd;
        std::string                 url;
		std::string					response;
		std::vector<std::string>	dir;

    public:

        Dinamic(std::string ur, int f);
		~Dinamic();

		void	createResponse();
        void    createDeleteForm();

};