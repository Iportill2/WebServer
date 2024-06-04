
#pragma once

# include "dependences.hpp"
# include "Request.hpp"
# include "Confs.hpp"

class Request;
class Confs;

class Response
{
	private:

		Request *	rq;
		Confs		conf;
		int			fd;

	public:

		Response(Request * request, Confs & cnf, int fDescriptor);
		~Response();

		int		createResponse();
		bool	checkServerName();

	//FUNCIONES PARA PRUEBAS
	void printRequest();
	void printConf();
};