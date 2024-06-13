
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
		size_t		_loc;

	public:

		Respons(Request * request, srv & sv, int fDescriptor);
		~Respons();

		int		createRespons();
		bool	checkServerName();
		int	checkLocation();
		bool	checkAuthorized();
		bool	checkMethod();

		void	htmlRespond();
		void	jpgRespond();
		void	pngRespond();
		
		

	//FUNCIONES PARA PRUEBAS
	void printRequest();
	void printConf();
};