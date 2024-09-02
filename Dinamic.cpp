#include "Dinamic.hpp"

Dinamic::Dinamic(int f) : fd(f) 
{
    Directory d("uploaded_files");
    dir = d.getDir();
    createResponse();
}

Dinamic::~Dinamic(){}


void    Dinamic::createResponse()
{
    response = "HTTP/1.1 200 OK\r\n";
   	response += "Content-Type: text/html\r\n";
  	response += "\r\n";

    response += "<!DOCTYPE html>";
    response += "<html lang=\"es\">";

    response += "<head>";
    response += "<meta charset=\"UTF-8\">";
    response += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
    response += "<title>Gestion de archivos</title>";
    response += "</head>";

    response += "<body>";
    response += "<h1>Gestion de archivos en el servidor</h1>";
    response += "<h2>Archivos en el servidor:</h2>";

    for(size_t i = 2; i < dir.size(); i ++)
        response +=   dir[i] + "<br>";

    response += "<br><h4>¿Que quieres hacer bonita?:</h4>";

    response += "<form method=\"GET\" action=\"/load\" style=\"display: inline;\">";
    response += "<button type=\"submit\">Subir archivo</button>  ";
    response += "</form>";
    
    response += "<form method=\"POST\" action=\"/download\" style=\"display: inline;\">";
    response += "<button type=\"submit\">Descargar archivo</button>  ";
    response += "</form>";

    response += "<form method=\"POST\" action=\"/delete\" style=\"display: inline;\">";
    response += "<button type=\"submit\">Borrar archivo</button>  ";
    response += "</form>";

    response += "</body>";
    response += "</html>";

    write (fd, response.c_str(), response.size());
}