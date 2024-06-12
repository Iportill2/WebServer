
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
		std::string _extension;

	public:

		Respons(Request * request, srv & sv, int fDescriptor);
		~Respons();

		int		createRespons();
		bool	checkServerName();
		bool	checkLocation();
		bool	checkAuthorized();

		void	htmlRespond();
		void	jpgRespond();
		void	pngRespond();
		
		

	//FUNCIONES PARA PRUEBAS
	void printRequest();
	void printConf();
};