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
    ErrorPage(std::string ErrorPageBlock);
    ~ErrorPage();

    void inidefaultErMap();

    bool ErrorParseBlock (const std::string ErrorParseBlock);
    void printmap();
    std::string createHtml_in_mapValue(std::string text);
};

#endif



/*
#ifndef ERRORPAGE_HPP
# define ERRORPAGE_HPP
#include "dependences.hpp"

#include "Server.hpp"

class ErrorPage
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

    std::map< int, std::string> ErRoute;


    ErrorPage();
    ErrorPage(const std::string ErrorPageBlock);
    ~ErrorPage();

    void inidefaultErMap();
    void iniErRoute();

    bool ErrorParseBlock (const std::string ErrorParseBlock);
    void printmap();
    std::string createHtml_in_mapValue(std::string text);


    bool directoryExistsA(const std::string& dirName);
    bool fileExistsA(const std::string& filename);
};

#endif
*/