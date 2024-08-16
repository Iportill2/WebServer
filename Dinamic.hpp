#pragma once

# include "dependences.hpp"
# include "Directory.hpp"

class Dinamic
{
    private:

        int							fd;
		std::string					response;
		std::vector<std::string>	dir;

    public:

        Dinamic(int f);
		~Dinamic();

		void	createResponse();

};