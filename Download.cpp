#include "Download.hpp"

Download::Download(Request * r, std::string & ur, int f, srv & server) : fd(f)
{
    _server = server;
	rq = r;
	url = ur;
	Directory d(url);
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
    response += "<title>File download</title>";
    response += "</head>";

    response += "<body>";
    response += "<h3>Clic on the file you wanna download:</h3>";

    for(size_t i = 2; i < dir.size(); i ++)
		response += "<a href=\"/upload?file=" + dir[i] + "&page=setdownload\">" + dir[i] + "</a><br>";

	response += "<br><br><a href=\"load/index.html\"> BACK </a><br>";

    write (fd, response.c_str(), response.size());
}

void Download::sendFile()
{
	std::string fileName;
	std::map<std::string, std::string>::iterator it = rq->data.begin();
	while (it != rq->data.end())
	{
		if(it->first == "file")
			fileName = it->second;
		it++;
	}

	std::string path = url + "/" + fileName;
	std::cout << "PATH:" << path << std::endl;
	std::ifstream file(path.c_str(), std::ios::binary);

	if(Utils::isFile(path.c_str()))
		std::cout << "It is a file" << std::endl;
	else
    {
        Error(404,fd, _server);
        return;
		//std::cout << "Is not a file" << std::endl;
    }
	 
    if (file)
	{
        // Obtener el tamaño del archivo
        file.seekg(0, std::ios::end);
        std::streamsize size = file.tellg();
        file.seekg(0, std::ios::beg);

        // Crear la respuesta HTTP
        response = "HTTP/1.1 200 OK\r\n";
        response += "Content-Type: application/octet-stream\r\n";
        response += "Content-Disposition: attachment; filename=\"" + fileName + "\"\r\n";
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
    {
        Error(404,fd, _server);
		//std::cout << "There is no file" << std::endl;
    }
}

Download::~Download(){}