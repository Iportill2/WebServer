
#pragma once

# include "dependences.hpp"
# include "Request.hpp"
# include "Confs.hpp"
# include "Utils.hpp"
#include <string>
class Request;
class Confs;

class Response
{
	private:

		Request *	rq;
		Confs		conf;
		int			fd;

		std::string _url;

	public:

		Response(Request * request, Confs & cnf, int fDescriptor);
		~Response();

		int		createResponse();
		bool	checkServerName();
		bool	checkLocation();
		
		

	//FUNCIONES PARA PRUEBAS
	void printRequest();
	void printConf();
};