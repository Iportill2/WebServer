

# include "Request.hpp"

Request::Request(std::string buf) : buffer(buf), content_len(0)
{
    parse();
}

Request::~Request(){}

void    Request::parse()
{
    std::string line;
    std::istringstream stream(buffer);

    while (std::getline(stream, line)) 
	{
		std::istringstream lineStream(line);
		std::string key;

		lineStream >> key;

        if (key == "GET" || key == "POST" || key == "DELETE")
        {
            if (key == "GET")
                method = "get";
            if (key == "POST")
                method = "post";
            if (key == "DELETE")
                method = "delete";
            lineStream >> uri;
        }
        else if (key == "Host:")
        {
            //size_t colonPos = line.find(":");
            //std::string hostAndPort = line.substr(colonPos + 2);
            std::string hostAndPort;
            lineStream >> hostAndPort;

            size_t secondColonPos = hostAndPort.find(":");
    
            host = hostAndPort.substr(0, secondColonPos);
            port = hostAndPort.substr(secondColonPos + 1);
        }
        else if (key == "Content-Length:")
            lineStream >> content_len;
        else if (line == "\r")
            break;
	}
    line.clear();
    while (std::getline(stream, line)) 
        body += line;

    if (buffer.find("boundary=")!= std::string::npos)
        boundary = buffer.substr(buffer.find("boundary="));

    if (uri.size() > 1 && uri[uri.size() - 1] == '/')
        uri = uri.substr(0, uri.size() - 1);
    //std::cout << RED << "URI en parse: " << uri << WHITE << std::endl;
    if (uri.size() > 15 && uri.substr(0, 15)  == "/download?file=")
    {
        file = uri.substr(15);
        uri = "/download";
        std::cout << "File:" << file << std::endl;
        size_t hueco = file.find("%20");
        while (hueco != std::string::npos)
        {
			file.replace(hueco, 3, " ");
			hueco = file.find("%20");
		}
    }
}

std::string Request::getMethod() {return method;}
std::string Request::getUri() {return uri;}
std::string Request::getHost() {return host;}
std::string Request::getPort() {return port;}
std::string Request::getBody() {return body;}
std::string Request::getBoundary() {return boundary;}
size_t		Request::getContentLen() {return content_len;}
std::string Request::getFile() {return file;}

//FUNCIONES PARA PRUEBAS----------------------------------------------------------
void Request::printRequest()
{
	std::cout << GREEN << "method: " << BLUE << method << std::endl;
    std::cout << GREEN << "uri: " << BLUE << uri << std::endl;
    std::cout << GREEN << "host: " << BLUE << host << std::endl;
    std::cout << GREEN << "port: " << BLUE << port << std::endl;
    std::cout << GREEN << "Content Lenght: " << BLUE << content_len << std::endl;
    std::cout << GREEN << "Body: " << BLUE << body << WHITE << std::endl << std::endl;
}