
#include "Error.hpp"
std::string Error::ErrorPage404 = "";

Error::Error(int er, int fdescriptor, srv server): error(er), fd(fdescriptor) 
{
    (void)server;
/*     if(!server.arErr.empty())
        ErrorPage404 = server.arErr.ErrorRoot; */
    sendError();
}

Error::~Error() {}

std::string Error::status(int error)
{
	std::map<int, std::string> errorCodes;

	errorCodes[200] = "200 OK";
	errorCodes[201] = "201 Created";
	errorCodes[202] = "202 Accepted";
	errorCodes[204] = "204 No Content";
	errorCodes[301] = "301 Moved Permanently";
	errorCodes[302] = "302 Found";
	errorCodes[303] = "303 See Other";
	errorCodes[304] = "304 Not Modified";
	errorCodes[400] = "400 Bad Request";
	errorCodes[401] = "401 Unauthorized";
	errorCodes[403] = "403 Forbidden";
    if(ErrorPage404 == "")
    {
	    errorCodes[404] = "404 Not Found";
    }
    else
    {
        errorCodes[404] = ErrorPage404;
    }
	errorCodes[405] = "405 Method Not Allowed";
	errorCodes[406] = "406 Not Acceptable";
	errorCodes[408] = "408 Request Timeout";
	errorCodes[409] = "409 Conflict";
	errorCodes[411] = "411 Length Required";
	errorCodes[413] = "413 Payload Too Large";
	errorCodes[414] = "414 URI Too Long";
	errorCodes[415] = "415 Unsupported Media Type";
	errorCodes[500] = "500 Internal Server Error";
	errorCodes[501] = "501 Not Implemented";
	errorCodes[502] = "502 Bad Gateway";
	errorCodes[503] = "503 Service Unavailable";
	errorCodes[505] = "505 HTTP Version Not Supported";

	return errorCodes[error];
}
std::string Error::toString(const int &num)
{
    std::stringstream s;
    s << num;
    return (s.str());
}

void    Error::sendError()
{
    //std::cout << "--------------ENVIANDO ERROR---------------" << std::endl;
    std::string httpResponse = "HTTP/1.1 " + status(error) + "\r\n";
   	httpResponse += "Content-Type: text/html\r\n";
    httpResponse += "\r\n";

    httpResponse += "<!DOCTYPE html>";
    httpResponse += "<html lang=\"es\">";
    httpResponse += "<head>";
    httpResponse += "<meta charset=\"UTF-8\">";
    httpResponse += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
    httpResponse += "<title>" + status(error) +  "</title>";
    httpResponse += "<style>";
    httpResponse += "body {";
    httpResponse += "text-align: center;";
    httpResponse += "padding: 50px;";
    httpResponse += "font-family: \"Arial\", sans-serif;";
    httpResponse += "}";
    httpResponse += "h1 {";
    httpResponse += "font-size: 50px;";
    httpResponse += "}";
    httpResponse += "p {";
    httpResponse += "font-size: 20px;";
    httpResponse += "}";
    httpResponse += "a {";
    httpResponse += "color: #0077cc;";
    httpResponse += "text-decoration: none;";
    httpResponse += "}";
    httpResponse += "a:hover {";
    httpResponse += "text-decoration: underline;";
    httpResponse += "}";
    httpResponse += "</style>";
    httpResponse += "</head>";
    httpResponse += "<body>";
    httpResponse += "<h2>Error " + status(error) + "</h2>";
    httpResponse += "</body>";
    httpResponse += "</html>";

    write(fd, httpResponse.c_str(), httpResponse.size());
}