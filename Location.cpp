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
/* {
        std::cout << RED << "R" << WHITE << std::endl;
        std::cout << CYAN  << locationBlock << WHITE <<std::endl;
        size_t pos;
        std::string tmp;

        std::string LOCATION = "location ";

        //std::cout << CYAN << locationBlock << WHITE << std::endl;

        // Find and extract file
        pos = locationBlock.find(LOCATION);
		
        if (pos != std::string::npos) 
		{
            pos += LOCATION.size() - 1; // Skip "file "
            size_t endPos = locationBlock.find('{', pos);
            tmp = locationBlock.substr(pos , endPos - pos);
           /// std::cout << "tmp:"  << tmp << std::endl;
            deletespaces(tmp);
            if(_location.empty())
                _location = tmp;
            else
                return std::cout << "MORE THAN 1 LOCATION IN LOCATION BLOCK" << std::endl,0;

        }

        // Find and extract autoindex
        pos = locationBlock.find("autoindex");
        if (pos != std::string::npos) 
		{
            pos += 10; // Skip "autoindex "
            size_t endPos = locationBlock.find(';', pos);
            tmp = locationBlock.substr(pos, endPos - pos);
            deletespaces(tmp);
            if(_autoindex.empty())
                _autoindex = tmp;
            else
                return std::cout << "MORE THAN 1 AUTOINDEX IN LOCATION BLOCK" << std::endl,0;
        }

        // Find and extract methods
        pos = locationBlock.find("methods");
        if (pos != std::string::npos) 
		{
            pos += 8; // Skip "methods "
            size_t endPos = locationBlock.find(';', pos);
            tmp = locationBlock.substr(pos, endPos - pos);
            if(_methods.empty())
                _methods = tmp;
            else
                return std::cout << "MORE THAN 1 METHODS IN LOCATION BLOCK" << std::endl,0;
            // tmp = locationBlock.substr(pos, endPos - pos);
            // deletespaces(tmp);
            // _methods = tmp;
        }

        // Find and extract root
        pos = locationBlock.find("root");
        if (pos != std::string::npos) 
		{
            pos += 5; // Skip "root "
            size_t endPos = locationBlock.find(';', pos);
            tmp = locationBlock.substr(pos, endPos - pos);
            deletespaces(tmp);
            if(_root.empty())
                _root = tmp;
            else
                return std::cout << "MORE THAN 1 ROOT IN LOCATION BLOCK" << std::endl,0;
        }

        // Find and extract cgi
        pos = locationBlock.find("cgi");
        if (pos != std::string::npos) 
		{
            pos += 4; // Skip "cgi "
            size_t endPos = locationBlock.find(';', pos);
            tmp = locationBlock.substr(pos, endPos - pos);
            deletespaces(tmp);
            if(_cgi.empty())
                _cgi = tmp;
            else
                return std::cout << "MORE THAN 1 CGI IN LOCATION BLOCK" << std::endl,0;
        }

        // Find and extract redirect_302
        pos = locationBlock.find("redirect 302");
        if (pos != std::string::npos) 
		{
            pos += 13; // Skip "redirect_302 "
            size_t endPos = locationBlock.find(';', pos);
            tmp = locationBlock.substr(pos, endPos - pos);
            deletespaces(tmp);
			if(_redirect_302.empty())
                _redirect_302 = tmp;
            else
                return std::cout << "MORE THAN 1 REDIRECT IN LOCATION BLOCK" << std::endl,0;
        }
        // Find and extract file
        pos = locationBlock.find("file");
        if (pos != std::string::npos) 
		{
            pos += 5; // Skip "redirect_302 "
            size_t endPos = locationBlock.find(';', pos);
            tmp = locationBlock.substr(pos, endPos - pos);
            deletespaces(tmp);
	        if(_file.empty())
                _file = tmp;
            else
                return std::cout << "MORE THAN 1 FILE IN LOCATION BLOCK" << std::endl,0;
        }
    return(1);
} */

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
