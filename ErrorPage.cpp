#include "ErrorPage.hpp"
ErrorPage::ErrorPage(const std::string ErrorPageBlock)
{
    
    std::cout << ErrorPageBlock << "\n";
    //std::cout <<"Default ErrorPage Constructor" << std::endl;
    if(ErrorParseBlock(ErrorPageBlock) == 1)
        return;
}
ErrorPage::~ErrorPage()
{
    //std::cout <<"ErrorPage Destructor" << std::endl;
}
bool ErrorPage::ErrorParseBlock (const std::string ErrorParseBlock)
{
    std::string line;
    std::istringstream stream(ErrorParseBlock);
    std::string tmp;

    while (std::getline(stream, line)) 
	{
		std::istringstream lineStream(line);
		std::string key;

		lineStream >> key;
        if (key == "error_page")
        {
            lineStream >> key;
            if(key == "404")
            {
                lineStream >> key;
                if(key[key.size() -1] == ';')
                    error_page_404 = key.substr(0,key.size() - 1);
                else
                    error_page_404 = key;
            } 
        }
        if(key == "location")
        {
            lineStream >> key;
            if(key == "=")
            {
                lineStream >> key;

                std::string tmp;
                lineStream >> tmp;
                if(tmp == "{")
                {
                    location = key;
                }
                else
                    location = key.substr(0,key.size() -1);
            }
        }
        if(key == "root")
        {
            lineStream >> line;
            if(line[line.size() - 1] == ';')
                root = line.substr(0,line.size() - 1);
            else
                root = line;
        }
        if((key == "internal;" && internal.empty()) || (key == "internal" && internal.empty()))
            internal = "yes";
    }

    if(error_page_404 == location)
        if(!error_page_404.empty() && !root.empty())
            ErrorRoot = root + error_page_404 ;
    return(1);
}