#include "ErrorPage.hpp"


std::string ErrorPage::createHtml_in_mapValue(std::string text)
{

    std::ostringstream s;
    s << "HTTP/1.1 ";
    s << text;
    s << "\r\n";
    s << "Content-Type: text/html\r\n";
    s << "Content-Length: " << text.size() << "\r\n";
    s << "\r\n";
    return(s.str());
}
void ErrorPage::inidefaultErMap()
{
    std::string _200 = "200 OK PATATA";
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
    std::string _404 = "404 Not Found";
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
ErrorPage::ErrorPage()
{
    inidefaultErMap();
    printmap();/////
}

ErrorPage::ErrorPage(const std::string ErrorPageBlock)
{
    inidefaultErMap();
    printmap();/////
    std::cout << ErrorPageBlock << "\n";
    //std::cout <<"Default ErrorPage Constructor" << std::endl;
    if(ErrorParseBlock(ErrorPageBlock) == 1)
        return;
}
ErrorPage::~ErrorPage()
{
    //std::cout <<"ErrorPage Destructor" << std::endl;
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
            if(key == "404")
            {
                lineStream >> key;
                if(key[key.size() -1] == ';')
                    error_page_404 = key.substr(0,key.size() - 1);
                else
                    error_page_404 = key;
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
        }
        if((key == "internal;" && internal.empty()) || (key == "internal" && internal.empty()))
            internal = "yes";
    }

    if(error_page_404 == location)
        if(!error_page_404.empty() && !root.empty())
            ErrorRoot = root + error_page_404 ;
    return(1);
}