
#pragma once

# include "dependences.hpp"
# include "Request.hpp"
# include "Utils.hpp"
# include "srv.hpp"

class Request;
class srv;

class Respons
{
	private:

		Request *	rq;
		srv			server;
		int			fd;

		std::string _url;

	public:

		Respons(Request * request, srv & sv, int fDescriptor);
		~Respons();

		int		createRespons();
		bool	checkServerName();
		bool	checkLocation();
		bool	checkAuthorized();
		
		

	//FUNCIONES PARA PRUEBAS
	void printRequest();
	void printConf();
};