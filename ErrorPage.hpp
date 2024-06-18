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

    ErrorPage(const std::string ErrorPageBlock);
    ~ErrorPage();

    bool ErrorParseBlock (const std::string ErrorParseBlock);
};

#endif