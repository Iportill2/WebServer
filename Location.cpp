#include "dependences.hpp"


Location::Location(const std::string locationBlock)
{
    std::cout << "Default location Constructor" << std::endl;
    parselocationBlock(locationBlock);
/*     std::cout << YELLOW << "void location::printValues() const" << WHITE << std::endl;
    */
    //printValues(); 
}

Location::~Location()
{
    std::cout << "location Destructor" << std::endl;
}

void Location::parselocationBlock(const std::string& locationBlock) 
{
    
        size_t pos;

        // Find and extract file
        pos = locationBlock.find("/");
        if (pos != std::string::npos) 
		{
            pos += 0; // Skip "file "
            size_t endPos = locationBlock.find('{', pos);
            _location = locationBlock.substr(pos, endPos - pos);
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
            size_t endPos = locationBlock.find(' ', pos);
            _file = locationBlock.substr(pos, endPos - pos);
        }
    
}
void Location::printValues() const
{
    std::cout << YELLOW ;
    std::cout << "location: " << _location << std::endl;
    std::cout << "Root: " << _root << std::endl;
    std::cout << "File: " << _file << std::endl;
    std::cout << "Methods: " << _methods << std::endl;
    std::cout << "Autoindex: " << _autoindex << std::endl;
    std::cout << "CGI: " << _cgi << std::endl;
    std::cout << "Redirect 302: " << _redirect_302 << std::endl;
    std::cout << WHITE ;
}