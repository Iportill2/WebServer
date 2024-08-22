#include "dependences.hpp"
#include "Location.hpp"

Location::Location(const std::string locationBlock)
{
    lock_ok = 1;
    //std::cout << "Default location Constructor" << std::endl;

    lock_ok = parselocationBlock(locationBlock);
    //std::cout << "lock_ok:"<< lock_ok << std::endl;
	std::cout << CYAN << "exefilename=" << _cgi_exefilename << WHITE << std::endl;
    std::cout << CYAN << "exefilename[exefilename.size() - 1]=" << _cgi_exefilename[_cgi_exefilename.size() - 1] << WHITE << std::endl;
    
    return;

/*     deletespaces(_location);
    checkAndAddMethods(_methods); */
}

Location::~Location()
{
    //std::cout << "location Destructor" << std::endl;
}


bool Location::parselocationBlock(const std::string& locationBlock) 
 {
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
            if(setlocationconfig(_location,key, lineStream ) == false)
                return(false);
        }
        if (key == "root")
        {
            if(setlocationconfig(_root,key, lineStream ) == false)
                return(false);
        }
        if (key == "file")
        {
            if(setlocationconfig(_file,key, lineStream ) == false)
                return(false);
        }
        if( key == "exefilename")
        {
            if(setlocationconfig(_cgi_exefilename, key, lineStream) == false)
                return(false);
        }
        if (key == "methods;"  || key == "methods" )
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
        if ((key == "autoindex;" && _autoindex.empty()) || (key == "autoindex" && _autoindex.empty()))
        {
            if(!_autoindex.empty())
                return(std::cout << RED << "autoindex twice" << WHITE << std::endl,0);
            lineStream >> _autoindex;
            if(_autoindex[_autoindex.size()-1] == ';')
                _autoindex = _autoindex.substr(0, _autoindex.size() - 1);
        }
        if ((key == "cgi;" && _cgi.empty() )||( key == "cgi" && _cgi.empty()))
        {
            if(!_cgi.empty())
                return(std::cout << RED << "cgi twice" << WHITE << std::endl,0);
            lineStream >> _cgi;
            if(_cgi[_cgi.size()-1] == ';')
                _cgi = _cgi.substr(0, _cgi.size() - 1);
        }
        if ((key == "redirect;" && _redirect.empty()) || (key == "redirect" && _redirect.empty()))
        {
            lineStream >> redirect_num;
            lineStream >> _redirect;
            if(_redirect[_redirect.size()-1] == ';')
                _redirect = _redirect.substr(0, _redirect.size() - 1);
		}
        if((key == "internal;" && _internal.empty()) || (key == "internal" && _internal.empty()))
            _internal = "on";



	}
    return(true);
}

std::string Location::toLowerCase(const std::string& str) 
{
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}
bool Location::setlocationconfig(std::string & variable,std::string print, std::istringstream & lineStream )
{
    std::string temp;
    if(!variable.empty())
        return(std::cout << RED << "twice "<< print <<" in server" << WHITE << std::endl,false);
    lineStream >> temp;
    if (temp[temp.size() - 1] == ';')
        variable = temp.substr(0, temp.size() - 1);
    else
        variable = temp;
    return(true);
}