#include "ErrorPage.hpp"

ErrorPage::ErrorPage()
{
        std::cout << "YES\n";
    inidefaultErMap();
    iniErRoute();



std::ifstream file("./errors/404.html");
                if (!file)
                {
                    //throw std::runtime_error("Could not open file: " + ErrorRoot);
                    std::cout << "Could not open file " << ErrorRoot << "\n";
                }
                else
                {

                std::stringstream buffer;
                buffer << file.rdbuf();

                std::string s = "404 OK!"; 
                std::string httpResponse = "HTTP/1.1 " + s + "\r\n";
   	            httpResponse += "Content-Type: text/html\r\n";
                httpResponse += "\r\n";
                httpResponse += buffer.str();

                /* std::cout << "HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH\n" <<  httpResponse << "\n"; */
                
                defaultErMap[404] = httpResponse;
                }


/*     std:: cout << "error_page_404 = "  << error_page_404 << "\n";
    std:: cout << "location = "  << location << "\n";
    std:: cout << "root = "  << root << "\n";
    std:: cout << "internal = "  << internal << "\n";
    std:: cout << "ErrorRoot = "  << ErrorRoot << "\n";
   // std:: cout << "defaultErMap = "  << defaultErMap[404] << "\n;"
    std:: cout << "defaultErMap[404] = "  << defaultErMap[404] << "\n";
    std:: cout << "ErRoute[404] = "  << ErRoute[404] << "\n"; */

    
    //printmap();/////
}

ErrorPage::ErrorPage(std::string ErrorPageBlock)
{
    std::cout << "NO\n";
    inidefaultErMap();
    iniErRoute();
    //printmap();/////
    //std::cout << ErrorPageBlock << "\n";
    //std::cout <<"Default ErrorPage Constructor" << std::endl;
    if(ErrorParseBlock(ErrorPageBlock) == false)
        return;
    mergedefaultErMapErRoute();

        std:: cout << "error_page_404 = "  << error_page_404 << "\n";
    std:: cout << "location = "  << location << "\n";
    std:: cout << "root = "  << root << "\n";
    std:: cout << "internal = "  << internal << "\n";
    std:: cout << "ErrorRoot = "  << ErrorRoot << "\n";
   // std:: cout << "defaultErMap = "  << defaultErMap[404] << "\n;"
    std:: cout << "defaultErMap[404] = "  << defaultErMap[404] << "\n";
    std:: cout << "ErRoute[404] = "  << ErRoute[404] << "\n";

/*                     std::cout << "HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH\n" <<  defaultErMap[404] << "\n";
                std::cout << "HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH\n"; */
/*     for (std::map<int, std::string>::iterator it = defaultErMap.begin(); it != defaultErMap.end(); ++it)
    {
        std::cout << "Key: " << it->first << " Value: " << it->second << std::endl<< std::endl;
    } */

    
}
void ErrorPage::mergedefaultErMapErRoute()
{
    {
    for (std::map<int, std::string>::iterator it = ErRoute.begin(); it != ErRoute.end(); ++it)
    {
        if (it->second.size() != 0)
        {
            defaultErMap[it->first] = it->second;
        }
    }
}
}
ErrorPage::~ErrorPage()
{
    //std::cout <<"ErrorPage Destructor" << std::endl;
}

std::string ErrorPage::createHtml_in_mapValue(std::string text)
{

     std::string httpResponse = "HTTP/1.1 " + text + "\r\n";
   	httpResponse += "Content-Type: text/html\r\n";
    httpResponse += "\r\n";

    httpResponse += "<!DOCTYPE html>";
    httpResponse += "<html lang=\"es\">";
    httpResponse += "<head>";
    httpResponse += "<meta charset=\"UTF-8\">";
    httpResponse += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
    httpResponse += "<title>" + text +  "</title>";
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
    httpResponse += "<h2>Error " + text + "</h2>";
    httpResponse += "</body>";
    httpResponse += "</html>"; 
    return httpResponse;
/*     std::ostringstream s;
    s << "HTTP/1.1 ";
    s << text;
    s << "\r\n";
    s << "Content-Type: text/html\r\n";
    s << "Content-Length: " << text.size() << "\r\n";
    s << "\r\n";
    return(s.str()); */
}
void ErrorPage::inidefaultErMap()
{
    std::string _200 = "200 OK";
    std::string _201 = "201 Created";
    std::string _202 = "202 Accepted";
    std::string _204 = "204 No Content";

    std::string _301 = "301 Moved Permanently";
    std::string _302 = "302 Found";
    std::string _303 = "303 See Other";
    std::string _304 = "304 Not Modified";

    std::string _400 = "400 Bad Request";
    std::string _401 = "401 Unauthorized";
    std::string _403 = "403 Forbidden";
    std::string _404 = "404 Not Found PATATA";
    std::string _405 = "405 Method Not Allowed";
    std::string _406 = "406 Not Acceptable";
    std::string _408 = "408 Request Timeout";
    std::string _409 = "409 Conflict";
    std::string _411 = "411 Length Required";
    std::string _413 = "413 Payload Too Large";
    std::string _414 = "414 URI Too Long";
    std::string _415 = "415 Unsupported Media Type";

    std::string _500 = "500 Internal Server Error";
    std::string _501 = "501 Not Implemented";
    std::string _502 = "502 Bad Gateway";
    std::string _503 = "503 Service Unavailable";
    std::string _505 = "505 HTTP Version Not Supported";


////////////////////////////////////////////////////////////////

    defaultErMap[200] = createHtml_in_mapValue(_200);
    defaultErMap[201] = createHtml_in_mapValue(_201);
    defaultErMap[202] = createHtml_in_mapValue(_202);
    defaultErMap[204] = createHtml_in_mapValue(_204);

    defaultErMap[301] = createHtml_in_mapValue(_301);
    defaultErMap[302] = createHtml_in_mapValue(_302);
    defaultErMap[303] = createHtml_in_mapValue(_303);
    defaultErMap[304] = createHtml_in_mapValue(_304);

    defaultErMap[400] = createHtml_in_mapValue(_400);
    defaultErMap[401] = createHtml_in_mapValue(_401);
    defaultErMap[403] = createHtml_in_mapValue(_403);
    defaultErMap[404] = createHtml_in_mapValue(_404);
    defaultErMap[405] = createHtml_in_mapValue(_405);
    defaultErMap[406] = createHtml_in_mapValue(_406);
    defaultErMap[408] = createHtml_in_mapValue(_408);
    defaultErMap[409] = createHtml_in_mapValue(_409);
    defaultErMap[411] = createHtml_in_mapValue(_411);
    defaultErMap[413] = createHtml_in_mapValue(_413);
    defaultErMap[414] = createHtml_in_mapValue(_414);
    defaultErMap[415] = createHtml_in_mapValue(_415);

    defaultErMap[500] = createHtml_in_mapValue(_500);
    defaultErMap[501] = createHtml_in_mapValue(_501);
    defaultErMap[502] = createHtml_in_mapValue(_502);
    defaultErMap[503] = createHtml_in_mapValue(_503);
    defaultErMap[505] = createHtml_in_mapValue(_505);   




}
void ErrorPage::iniErRoute()
{
    ErRoute[200] = "";
    ErRoute[201] = "";
    ErRoute[202] = "";
    ErRoute[204] = "";

    ErRoute[301] = "";
    ErRoute[302] = "";
    ErRoute[303] = "";
    ErRoute[304] = "";

    ErRoute[400] = "";
    ErRoute[401] = "";
    ErRoute[403] = "";
    ErRoute[404] = "";
    ErRoute[405] = "";
    ErRoute[406] = "";
    ErRoute[408] = "";
    ErRoute[409] = "";
    ErRoute[411] = "";
    ErRoute[413] = "";
    ErRoute[414] = "";
    ErRoute[415] = "";

    ErRoute[500] = "";
    ErRoute[501] = "";
    ErRoute[502] = "";
    ErRoute[503] = "";
    ErRoute[505] = "";  
}
void ErrorPage::printmap()
{
	std::cout << GREEN << "***************************************\n" << RED ;
    std::map<int, std::string>::iterator it;
    for (it = defaultErMap.begin(); it != defaultErMap.end(); ++it) 
	{
        std::cout << it->first << " -> " << it->second << std::endl;
    }
	std::cout << GREEN << "***************************************\n" << WHITE ;
}

bool ErrorPage::ErrorParseBlock (const std::string ErrorParseBlock)
{
    std::string line;
    std::istringstream stream(ErrorParseBlock);
    std::string tmp;

    while (std::getline(stream, line)) 
	{
		std::istringstream lineStream(line);
		std::string key;

		lineStream >> key;
        if (key == "error_page")
        {
            lineStream >> key;
            int keyInt = std::atoi(key.c_str());
            std::map<int, std::string>::iterator it;
            for (it = ErRoute.begin(); it != ErRoute.end(); ++it) 
            {
                if(keyInt == it->first)
                {
                    lineStream >> key;
                    if(key[key.size() -1] == ';')
                        ErRoute[keyInt] = key.substr(0,key.size() - 1);
                     else
                        ErRoute[keyInt] = key;
                break;
                }
            }
        }
        if(key == "location")
        {
            lineStream >> key;
            if(key == "=")
            {
                lineStream >> key;

                std::string tmp;
                lineStream >> tmp;
                if(tmp == "{")
                {
                    location = key;
                }
                else
                    location = key.substr(0,key.size() -1);
            }
        }
        if(key == "root")
        {
            lineStream >> line;
            if(line[line.size() - 1] == ';')
                root = line.substr(0,line.size() - 1);
            else
                root = line;

            if(directoryExistsA(root) == 0)
                return(std::cout << "the directory " << root << " didnt exit\n",0);
            
        }
        if((key == "internal;" && internal.empty()) || (key == "internal" && internal.empty()))
            internal = "yes";
    }
    std::map<int, std::string>::iterator it;
    for (it = ErRoute.begin(); it != ErRoute.end(); ++it) 
    {
        if(location == it->second)
        {
            if(!location.empty() && !root.empty())
            {
/*                 if(fileExistsA(location) == false)
                    return(std::cout << "the location " << location << " didnt exit\n",0); */
                ErrorRoot = root + location ;
                if(fileExistsA(ErrorRoot) == false)
                    return(std::cout << "the ErrorRoot " << ErrorRoot << " didnt exit\n",0);
                std::ifstream file(ErrorRoot.c_str());
                if (!file)
                {
                    throw std::runtime_error("Could not open file: " + ErrorRoot);
                }
                std::stringstream buffer;
                buffer << file.rdbuf();

                std::string httpResponse = "HTTP/1.1 " + error_page_404 + "\r\n";
   	            httpResponse += "Content-Type: text/html\r\n";
                httpResponse += "\r\n";
                httpResponse += buffer.str();

                /* std::cout << "HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH\n" <<  httpResponse << "\n"; */
                ErRoute[404] = httpResponse;
/*                 std::cout << "HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH\n" <<  ErRoute[404] << "\n";
                std::cout << "HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH\n"; */
            }
            break;
        }
    }
    return(1);
}
bool ErrorPage::directoryExistsA(const std::string& dirName) 
{
    struct stat info;

    if (stat(dirName.c_str(), &info) != 0) {
        // No se puede acceder al directorio
        return false;
    } else if (info.st_mode & S_IFDIR) {
        // Es un directorio
        return true;
    } else {
        // Existe, pero no es un directorio
        return false;
    }
}
bool ErrorPage::fileExistsA(const std::string& filename) 
{
    std::ifstream file(filename.c_str());
    return file.good();
}