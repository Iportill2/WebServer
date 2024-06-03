#ifndef LOCATION_HPP
# define LOCATION_HPP

#include "dependences.hpp"
class Location
{
    public:
    std::string _location;

    std::string _root;
    std::string _file;
    std::string _methods;
    std::string _autoindex;
    std::string _cgi;
    std::string _redirect_302;
    Location() = default;
    Location(const std::string locationBlock);
    ~Location();

    void parselocationBlock(const std::string& locationBlock);
    void printValues() const;
};
#endif