#ifndef ERRORPAGE_HPP
# define ERRORPAGE_HPP
#include "dependences.hpp"

//#include "Config.hpp"

class ErrorPage //: public Config
{
    public:

    std::string error_page_404;
    std::string location;
    std::string root;
    std::string internal;

    std::string ErrorRoot;

    std::map< int, std::string> defaultErMap;
    std::map< int, std::string> ErMap;
    std::map< int, std::string> FinalErMap;


    ErrorPage();
    ErrorPage(const std::string ErrorPageBlock);
    ~ErrorPage();

    void inidefaultErMap();

    bool ErrorParseBlock (const std::string ErrorParseBlock);
    void printmap();
    std::string createHtml_in_mapValue(std::string text);
};

#endif