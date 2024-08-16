#include "Download.hpp"

Download::Download(int f) : fd(f)
{
	Directory d("uploaded_files");
    dir = d.getDir();
	//sendForm();
}
   void Download::sendForm()
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
    	response += "<h3>Elige el archivo que quieres descargar:</h3>";

    	for(size_t i = 2; i < dir.size(); i ++)
    	    response += "<a href=\"/download?file=" + dir[i] + "\">" + dir[i] + "</a><br>";

		response += "<br><br><a href=\"/dinamic\"> VOLVER </a><br>";

    	write (fd, response.c_str(), response.size());
   }

void Download::sendFile(std::string fi)
{
	std::string path = "uploaded_files/" + fi;
	std::cout << "PATH:" << path << std::endl;
	std::ifstream file(path.c_str(), std::ios::binary);

	if(Utils::isFile(path.c_str()))
		std::cout << "ES UN ARCHIVO" << std::endl;
	else
		std::cout << "NOOOOOO ES UN ARCHIVO" << std::endl;
	
    if (file)
	{
        // Obtener el tamaño del archivo
        file.seekg(0, std::ios::end);
        std::streamsize size = file.tellg();
        file.seekg(0, std::ios::beg);

        // Crear la respuesta HTTP
        response = "HTTP/1.1 200 OK\r\n";
        response += "Content-Type: application/octet-stream\r\n";
        response += "Content-Disposition: attachment; filename=\"" + fi + "\"\r\n";
        response += "Content-Length: " + Utils::toString(size) + "\r\n";
        response += "\r\n";

        // Leer el archivo y añadirlo al cuerpo de la respuesta
        std::vector<char> buffer(size);
        if (file.read(buffer.data(), size)) {
            response.append(buffer.begin(), buffer.end());
        }
		write (fd, response.c_str(), response.size());
    }
	else
		std::cout << "NO HAY FILE" << std::endl;
}

Download::~Download(){}