#include "dependences.hpp"
#include "Location.hpp"

Location::Location(const std::string locationBlock)
{
    //std::cout << "Default location Constructor" << std::endl;
    nullstrings();
    parselocationBlock(locationBlock);
    deletespaces(_location);
    checkAndAddMethods(_methods);
}

Location::~Location()
{
    //std::cout << "location Destructor" << std::endl;
}
void Location::deletespaces(std::string &s)
{
    size_t i = 0;
    std::string temp;
    while(i < s.size())
    {
        while(s[i] == ' ')
            i++;
		if(s[i] != ' ')
		{
        	temp.push_back(s[i]);
        	i++;
		}
    }
	s = temp;
    //checker
	//std::cout << "s:"<< "|" << s << "|" << std::endl;
	//std::cout << "temp:"<< "|" << temp << "|" << std::endl;
	//return(s);
}
void Location::nullstrings()
{
    _location = "";
    _root = "";
    _file = "";
    _methods = "";
    _autoindex = "";
    _cgi = "";
    _redirect_302 = "";

}
void Location::parselocationBlock(const std::string& locationBlock) 
{
    
        size_t pos;
        std::string tmp;

        std::string LOCATION = "location /";

        //std::cout << CYAN << locationBlock << WHITE << std::endl;

        // Find and extract file
        pos = locationBlock.find(LOCATION);
        if (pos != std::string::npos) 
		{
            pos += LOCATION.size() - 1; // Skip "file "
            size_t endPos = locationBlock.find('{', pos);
            tmp = locationBlock.substr(pos , endPos - pos);

            if(_location == "")
                _location = tmp;
            else
                std::cout << "ERROR AL LOCATION REDIRECT" << std::endl;
        }

        // Find and extract autoindex
        pos = locationBlock.find("autoindex");
        if (pos != std::string::npos) 
		{
            pos += 10; // Skip "autoindex "
            size_t endPos = locationBlock.find(';', pos);
            _autoindex = locationBlock.substr(pos, endPos - pos);
        }

        // Find and extract methods
        pos = locationBlock.find("methods");
        if (pos != std::string::npos) 
		{
            pos += 8; // Skip "methods "
            size_t endPos = locationBlock.find(';', pos);
            _methods = locationBlock.substr(pos, endPos - pos);
        }

        // Find and extract root
        pos = locationBlock.find("root");
        if (pos != std::string::npos) 
		{
            pos += 5; // Skip "root "
            size_t endPos = locationBlock.find(';', pos);
            _root = locationBlock.substr(pos, endPos - pos);
        }

        // Find and extract cgi
        pos = locationBlock.find("cgi");
        if (pos != std::string::npos) 
		{
            pos += 4; // Skip "cgi "
            size_t endPos = locationBlock.find(';', pos);
            _cgi = locationBlock.substr(pos, endPos - pos);
        }

        // Find and extract redirect_302
        pos = locationBlock.find("redirect 302");
        if (pos != std::string::npos) 
		{
            pos += 13; // Skip "redirect_302 "
            size_t endPos = locationBlock.find(';', pos);
            _redirect_302 = locationBlock.substr(pos, endPos - pos);
        }
        // Find and extract file
        pos = locationBlock.find("file");
        if (pos != std::string::npos) 
		{
            pos += 5; // Skip "redirect_302 "
            size_t endPos = locationBlock.find(';', pos);
            _file = locationBlock.substr(pos, endPos - pos);
        }
    
}

std::string Location::toLowerCase(const std::string& str) 
{
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

void Location::checkAndAddMethods(const std::string& input) 
{
    std::string lowerInput = toLowerCase(input);

    if (lowerInput.find("get") != std::string::npos) 
    {
        methods_vector.push_back("get");
    }
    if (lowerInput.find("post") != std::string::npos) 
    {
        methods_vector.push_back("post");
    }
    if (lowerInput.find("delete") != std::string::npos) 
    {
        methods_vector.push_back("delete");
    }
}
