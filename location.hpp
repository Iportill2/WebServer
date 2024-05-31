#ifndef LOCATION_HPP
# define LOCATION_HPP

#include "dependences.hpp"
class location
{
    public:
    std::string _name;

    std::string _root;
    std::string _file;
    std::string _methods;
    std::string _autoindex;
    std::string _cgi;
    std::string _redirect_302;
    location();
    ~location();
};
#endif