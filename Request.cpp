

#include "Request.hpp"

Request::Request() : content_len(0)
{
    
}

void Request::addBuffer(char * buf, int bytes)
{
    buffer.append(buf, bytes);
    //std::cout  << GREEN << buf << WHITE << std::endl;
    //std::cout << "tamaño buffer = " << buffer.size() << std::endl;
}

Request::~Request() {}

void Request::parse()
{
    std::cout << std::endl << YELLOW << buffer << WHITE << std::endl;
   // std::cout << "tamaño buffer = " << buffer.size() << std::endl;
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
            std::string hostAndPort;
            lineStream >> hostAndPort;

            size_t secondColonPos = hostAndPort.find(":");

            host = hostAndPort.substr(0, secondColonPos);
            port = hostAndPort.substr(secondColonPos + 1);
        }
        else if (key == "Content-Length:")
            lineStream >> content_len;
        else if (line.find("boundary=") != std::string::npos)
            stractBoundary(line.substr(line.find("boundary=") + 9));
        else if (line == "\r")
            break;
    }
    line.clear();
    while (std::getline(stream, line))
        body += line;

    if (uri.size() > 1 && uri[uri.size() - 1] == '/')
        uri = uri.substr(0, uri.size() - 1);
    // std::cout << RED << "URI en parse: " << uri << WHITE << std::endl;
    if (uri.size() > 15 && uri.substr(0, 15) == "/download?file=")
    {
        downfile = uri.substr(15);
        uri = "/download";
        std::cout << "File:" << downfile << std::endl;
    }
    if (uri.size() > 13 && uri.substr(0, 13) == "/Delete?file=")
    {
        downfile = uri.substr(13);
        uri = "/delete";
        std::cout << "File:" << downfile << std::endl;
    }
    if (!downfile.empty())
    {
        size_t hueco = downfile.find("%20");
        while (hueco != std::string::npos)
        {
            downfile.replace(hueco, 3, " ");
            hueco = downfile.find("%20");
        }
    }
}

void Request::stractBoundary(std::string bound)
{
    boundary = bound.substr(0, bound.size() - 1);
    //std::cout << std::endl << "-----------Boundary en REQUEST------------" << std::endl << YELLOW << boundary << WHITE << std::endl;

    std::string boundaryStart = "--" + boundary;
    std::string boundaryEnd = "--" + boundary + "--";

    size_t in = buffer.find(boundaryStart) + boundaryStart.size() + 1;
    boundaryContent = buffer.substr(in, buffer.find(boundaryEnd) - in - 2);

    upfileContent = boundaryContent.substr(boundaryContent.find("\r\n\r\n") + 4);
    
    std::string requestHead = buffer.substr(0, buffer.find("\r\n\r\n"));
    //std::cout << std::endl << "-----------RequestHead en REQUEST------------" << std::endl << MAGENTA << requestHead << WHITE << std::endl;

    std::string boundaryHead = boundaryContent.substr(0, boundaryContent.find("\r\n\r\n"));
    //std::cout << std::endl << "-----------BoundaryHead en REQUEST------------" << std::endl << MAGENTA << boundaryHead << WHITE << std::endl;

   /*  std::string boundaryconfinal = buffer.substr(in);
    size_t final = boundaryconfinal.find(boundary); 
    if (final != std::string::npos)
        std::cout << "ENCONTRADO!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl; */

    upfileName = boundaryContent.substr(boundaryContent.find("filename=\"") + 10);
    upfileName = upfileName.substr(0, upfileName.find("\""));
    //std::cout << std::endl << "-----------UpfileName en REQUEST------------" << std::endl << YELLOW << upfileName << WHITE << std::endl;
}


std::string Request::getMethod() { return method; }
std::string Request::getUri() { return uri; }
std::string Request::getHost() { return host; }
std::string Request::getPort() { return port; }
std::string Request::getBody() { return body; }
std::string Request::getBoundary() { return boundary; }
size_t Request::getContentLen() { return content_len; }
std::string Request::getDownFile() { return downfile; }
std::string Request::getUpFileContent() { return upfileContent; }
std::string Request::getUpFileName(){ return upfileName; }

// FUNCIONES PARA PRUEBAS----------------------------------------------------------
void Request::printRequest()
{
    std::cout << GREEN << "method: " << BLUE << method << std::endl;
    std::cout << GREEN << "uri: " << BLUE << uri << std::endl;
    std::cout << GREEN << "host: " << BLUE << host << std::endl;
    std::cout << GREEN << "port: " << BLUE << port << std::endl;
    std::cout << GREEN << "Content Lenght: " << BLUE << content_len << std::endl;
    std::cout << GREEN << "Body: " << BLUE << body << WHITE << std::endl
              << std::endl;
}