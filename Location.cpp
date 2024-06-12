#include "dependences.hpp"
#include "Location.hpp"

Location::Location(const std::string locationBlock)
{
    //std::cout << "Default location Constructor" << std::endl;
    if(parselocationBlock(locationBlock) == 0)
		return;
    //deletespaces(_location);
    checkAndAddMethods(_methods);
}

Location::~Location()
{
    //std::cout << "location Destructor" << std::endl;
}


bool Location::parselocationBlock(const std::string& locationBlock) 
 {
    std::cout   << std::endl;

    //std::cout << CYAN << locationBlock << WHITE << std::endl;

    std::string line;
    std::istringstream stream(locationBlock);
    std::string tmp;

    while (std::getline(stream, line)) 
	{
		std::istringstream lineStream(line);
		std::string key;

		lineStream >> key;


        if (key == "location")
        {
            if(!_location.empty())
                return(std::cout << RED << "location twice" << WHITE << std::endl,0);
            lineStream >> _location;
            if(_location[_location.size()-1] == '{')
                _location = _location.substr(0, _location.size() - 1);
        }

         if (key == "root")
        {
            if(!_root.empty())
                return(std::cout << RED << "root twice" << WHITE << std::endl,0);
            lineStream >> _root;
            if(_root[_root.size()-1] == ';')
                _root = _root.substr(0, _root.size() - 1);
        }
        if (key == "file")
        {
            if(!_file.empty())
                return(std::cout << RED << "file twice" << WHITE << std::endl,0);
            lineStream >> _file;
            if(_file[_file.size()-1] == ';')
                _file = _file.substr(0, _file.size() - 1);
        }
        if (key == "methods")///
        {
            std::string method;
            lineStream >> method;
            while (!method.empty() && (method[method.size() - 1] == ';' || method[method.size() - 1] == '}'))
                method = method.substr(0, method.size() - 1);

            methods_vector.push_back(method);
            
            while(!method.empty())
            {
                method.clear();
                lineStream >> method;

                while (!method.empty() && (method[method.size() - 1] == ';' || method[method.size() - 1] == '}'))
                        method = method.substr(0, method.size() - 1);

                if(!method.empty())
                {
                    if(method == "get" || method == "post" || method == "delete")
                        methods_vector.push_back(method);
                }
            }
        }
        if (key == "autoindex")
        {
            if(!_autoindex.empty())
                return(std::cout << RED << "autoindex twice" << WHITE << std::endl,0);
            lineStream >> _autoindex;
            if(_autoindex[_autoindex.size()-1] == ';')
                _autoindex = _autoindex.substr(0, _file.size() - 1);
        }
        if (key == "cgi")
        {
            if(!_cgi.empty())
                return(std::cout << RED << "cgi twice" << WHITE << std::endl,0);
            lineStream >> _cgi;
            if(_cgi[_cgi.size()-1] == ';')
                _cgi = _cgi.substr(0, _file.size() - 1);
        }
        if (key == "redirect_302")
        {
            std::cout << RED << "@@@" << WHITE << std::endl;
            if(!_redirect_302.empty())
                return(std::cout << RED << "redirect_302 twice" << WHITE << std::endl,0);
            lineStream >> _redirect_302;
            if(_redirect_302[_redirect_302.size()-1] == ';')
                _redirect_302 = _redirect_302.substr(0, _file.size() - 1);
        }
	}
    return(1);
} 

std::string Location::toLowerCase(const std::string& str) 
{
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

void Location::checkAndAddMethods(const std::string& input) 
{
    std::istringstream iss(toLowerCase(input));
    std::string method;

    while (std::getline(iss, method, ' ')) 
    {
        if (method == "get") 
        {
            methods_vector.push_back("get");
        }
        else if (method == "post") 
        {
            methods_vector.push_back("post");
        }
        else if (method == "delete") 
        {
            methods_vector.push_back("delete");
        }
    }
}
