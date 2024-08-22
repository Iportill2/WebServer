

#include "Request.hpp"

Request::Request() : content_len(0), kepOnReading(true), firstRead(true)
{
    
}

void Request::addBuffer(char * buf, int bytes)
{
    if (bytes > 100)
        part.clear();
    buffer.append(buf, bytes);
    part.append(buf, bytes);

    if (firstRead)
    {
        firstRead = false;

        std::string head;
        size_t headEnd = buffer.find("\r\n\r\n");
        if (headEnd != std::string::npos)
            head = buffer.substr(0, headEnd);
        else
            head = buffer;
        
        std::string line;
        std::istringstream stream(head);

        while (std::getline(stream, line))
        {
            if (line.find("boundary=") != std::string::npos)
            {
                boundary = line.substr(line.find("boundary=") + 9);
                boundary = boundary.substr(0, boundary.size() - 1);
                boundaryStart = "--" + boundary;
                boundaryEnd = "--" + boundary + "--";
            }
        }
    }
}

Request::~Request() {}

void Request::parse()
{
    //std::cout << std::endl << YELLOW << buffer << WHITE << std::endl;

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
            stractBoundary();
        else if (line == "\r")
            break;
        //std::cout << "ER conten len: " << content_len << std::endl;
    }
    line.clear();
    while (std::getline(stream, line))
        body += line;

    if (uri.size() > 1 && uri[uri.size() - 1] == '/')
        uri = uri.substr(0, uri.size() - 1);
    
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

void Request::stractBoundary()
{
    size_t in = buffer.find(boundaryStart) + boundaryStart.size() + 1;
    boundaryContent = buffer.substr(in, buffer.find(boundaryEnd) - in - 2);

    upfileContent = boundaryContent.substr(boundaryContent.find("\r\n\r\n") + 4);

    upfileName = boundaryContent.substr(boundaryContent.find("filename=\"") + 10);
    upfileName = upfileName.substr(0, upfileName.find("\""));

    /* size_t inPrueba = buffer.find(boundaryStart);
    if (inPrueba != std::string::npos)
        std::string boundaryContentPrueba = buffer.substr(inPrueba);
    std::cout << MAGENTA << boundaryContentPrueba << WHITE << std::endl;
    std::cout << "Er boundary size: " << boundaryContentPrueba.size() << std::endl; */
;
    
    /* std::string requestHead = buffer.substr(0, buffer.find("\r\n\r\n"));
    std::cout << std::endl << "-----------RequestHead en REQUEST------------" << std::endl << MAGENTA << requestHead << WHITE << std::endl; */

    /* std::string boundaryHead = boundaryContent.substr(0, boundaryContent.find("\r\n\r\n"));
    std::cout << std::endl << "-----------BoundaryHead en REQUEST------------" << std::endl << MAGENTA << boundaryHead << WHITE << std::endl; */

   /*  std::string boundaryconfinal = buffer.substr(in);
    size_t final = boundaryconfinal.find(boundary); 
    if (final != std::string::npos)
        std::cout << "ENCONTRADO!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl; */


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