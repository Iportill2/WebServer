#ifndef LOCATION_HPP
# define LOCATION_HPP
#include "Utils.hpp"
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
    //std::string _exe;///
    std::string _redirect;
    int redirect_num;

    bool lock_ok;

    std::vector <std::string> methods_vector;
    Location(){
        lock_ok = false;
        redirect_num = 0;
    };
    Location(const std::string locationBlock);
    ~Location();

    bool parselocationBlock(const std::string& locationBlock);

    std::string getLocation() const { return _location; }
    std::string getRoot() const { return _root; }
    std::string getFile() const { return _file; }
    std::string getMethods() const { return _methods; }
    std::string getAutoindex() const { return _autoindex; }
    std::string getCgi() const { return _cgi; }
    //std::string getExe() const { return _exe; }//
    std::string getRedirect302() const { return _redirect; }

    std::string toLowerCase(const std::string& str);
    void checkAndAddMethods(const std::string& input);

};
#endif