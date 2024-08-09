
# include "Load.hpp"


Load::Load(Request * r, int f) : rq(r), fd(f)
{
    parse();
    createTextFile();
}

void    Load::parse()
{
    std::string line;
    std::istringstream stream(rq->getBoundary());

    std::getline(stream, line);//EXTRACT BOUNDARY CLAVE
    boundary_clave = line.substr(9, line.size() - 10);

    //std::cout << "Boundary clave: " << boundary_clave << std::endl;

    while (std::getline(stream, line)) 
	{
        last_line = line;
		/* std::istringstream lineStream(line);
		std::string key;

		lineStream >> key;

        std::size_t first = line.find(boundary_clave);

        if (first != std::string::npos)
            std::cout << key << std::endl; */
    }
   
	std::size_t first = rq->getBoundary().find(boundary_clave);//EXTRACT BOUNDARY CONTENT
	std::size_t second;

    if (first != std::string::npos)
		second = rq->getBoundary().find(boundary_clave, first + boundary_clave.length());
	if (second != std::string::npos)
		boundary_content = rq->getBoundary().substr(second);

    if (last_line.substr(last_line.size() - 3, 2) == "--")
        finish = 1;
    else
		finish = 0;

    std::size_t fName = boundary_content.find("filename="); //EXTRACT FILENAME
    if (fName != std::string::npos)
    {
        file_name = boundary_content.substr(fName + 10);
        std::size_t quote = file_name.find("\"");
        file_name = file_name.substr(0, quote);
    }


    std::size_t type = boundary_content.find("Content-Type: "); //EXTRACT CONTENT-TYPE
    if (type != std::string::npos)
    {
        content_type = boundary_content.substr(type + 14);
        std::size_t jump = content_type.find("\r\n");
        content_type = content_type.substr(0, jump);
    }

    std::size_t content = boundary_content.find("\r\n\r\n"); //EXTRACT CONTENT
    if (content != std::string::npos)
    {
        file_content = boundary_content.substr(content + 4);
        std::size_t jump = file_content.find("\r\n");
    	file_content = file_content.substr(0, jump);
    }

	std::cout << "---------boundary_content--------" << std::endl << GREEN << boundary_content << WHITE << std::endl;
    std::cout << "my File name: "  << file_name << std::endl;
    std::cout << "my Content-Type: "  << content_type << std::endl;
	std::cout << "my File-content: "  << file_content << std::endl;
    /* if (finish)
        std::cout << "--- FINAL DEL MENSAJE ---" << std::endl;
    else
        std::cout << "--- MENSAJE SIN FINALIZAR ---" << std::endl; */
}

void    Load::createTextFile()
{
    std::string path = "uploaded_files/" + file_name;
    std::ofstream file(path.c_str());

    if (file.is_open())
    {
        file << file_content;
        file.close();
    }
}

Load::Load(std::string  bd, int f)
{
    (void)f;
    (void)bd;
    //std::cout << "Boundary en Load: " << "\"" << body << "\"" << std::endl;
    //parse();
    //exec();
    //sendResult();
    //std::cout << "Result: " << "\"" << result << "\"" << std::endl << std::endl << std::endl << std::endl << std::endl;
}
Load::~Load(){}



/* std::string Load::getResult()
{
    return (result);
} */

/* void Load::sendResult()
{
    Error r(403, fd);
} */

/* void Load::sendResult()
{
    std::string httpResponse = "HTTP/1.1 200 OK\r\n";
   	httpResponse += "Content-Type: text/plain\r\n";
  	httpResponse += "\r\n";

    httpResponse += "<!DOCTYPE html>";
    httpResponse += "<html lang=\"es\">";

    httpResponse += "<head>";
    httpResponse += "<meta charset=\"UTF-8\">";
    httpResponse += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
    httpResponse += "<title>Magia!</title>";
    httpResponse += "</head>";

    httpResponse += "<body>";
    httpResponse += "</body>";
    httpResponse += "</html>";

    //std::string prueba = "MAMON";
    //write (fd, prueba.c_str(), sizeof(prueba));

    write (fd, httpResponse.c_str(), httpResponse.size());
    //std::cout << "-----------hola------------" << std::endl;
} */