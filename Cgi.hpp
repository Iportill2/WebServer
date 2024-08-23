
#pragma once

# include "dependences.hpp"
# include "Error.hpp"

/* class Cgi
{
    private:

    	std::string body;
		std::string	value;
		std::string result;
		char 		res[128];
		int			fd;
		std::string exe_name;
        srv server;

    public:

        Cgi(std::string  bd, int f, std::string exename,srv Server);
        ~Cgi();
        bool tienePermisosDeEjecucion(const std::string& rutaArchivo) ;
        bool 		parse();
        void 		exec();
        //std::string	getResult();
		void		sendResult();
}; */
class Cgi {
public:
    Cgi(std::string bd, int f, std::string exename, srv Server);
    ~Cgi();

    bool parse();
    bool exec(); // La función exec() debería devolver un bool

private:
    bool tienePermisosDeEjecucion(const std::string& rutaArchivo);
    void sendResult(const std::string& content); // Cambiar firma del método
    void sendResult(); // Método para el resultado por defecto
    static void handle_alarm(int sig);

    std::string body;
    int fd;
    std::string exe_name;
    std::string value;
    std::string result;
    srv server; // Mueve esto al final de la lista

    static pid_t child_pid; // Variable estática
    static bool alarm_triggered; // Variable estática

    char res[4096]; // Tamaño del buffer para leer del pipe
};