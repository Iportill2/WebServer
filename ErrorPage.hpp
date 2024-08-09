#ifndef ERRORPAGE_HPP
# define ERRORPAGE_HPP
#include "dependences.hpp"


class ErrorPage 
{
    public:

    std::string error_page_404;
    int errorIndex;
    std::map< int, std::string> defaultErMap;

    ErrorPage();
    ErrorPage(std::string ErrorPageBlock);
    ~ErrorPage();

    void inidefaultErMap();
    std::string createHtml_in_mapValue(std::string text);
    bool ErrorParseBlock (const std::string ErrorParseBlock);

    bool directoryExistsA(const std::string& dirName);
    bool fileExistsA(const std::string& filename);

};
#endif