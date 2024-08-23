#include "dependences.hpp"
#include "Location.hpp"

Location::Location(const std::string locationBlock)
{
    lock_ok = 1;
    _cgi_exefilename = "";
    //std::cout << "Default location Constructor" << std::endl;

    lock_ok = parselocationBlock(locationBlock);
    //std::cout << "lock_ok:"<< lock_ok << std::endl;
	
    
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
        if( key == "exe")
        {
            if(setlocationconfig(_cgi_exefilename, key, lineStream) == false)
                return(false);
            size_t len = _cgi_exefilename.size();
/*             std::cout << "len=" <<len <<std::endl; */
            if(_cgi_exefilename[len -4] != '.' && _cgi_exefilename[len -3] != 'o' && _cgi_exefilename[len -2] != 'u'&& _cgi_exefilename[len -1] != 't' && len < 5 )
                return(std::cout << RED << "the executable dont finish in .out"<< std::endl, false);
            struct stat buffer;
            if((stat(_cgi_exefilename.c_str(), &buffer) == 0) == false)//checkeamos y el archivo existe en la ruta guardada en _cgi_exefilename
                return(std::cout << RED << "the executable dont exist in that route"<< std::endl, false);
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
    //std::cout << RED <<"a"<<WHITE;
    std::string temp;
    if(!variable.empty())
        return(std::cout << RED << "twice "<< print <<" in server" << WHITE << std::endl,false);
    lineStream >> temp;
    if (temp[temp.size() - 1] == ';')
        variable = temp.substr(0, temp.size() - 1);
    else
        variable = temp;
/*     if(variable[variable.size()] == 't' && variable[variable.size()-1] == 'u' && variable[variable.size()-1] && variable[variable.size()-1]== 'o' && variable[variable.size()-1] == '.')
    { */
        
        //return(false);
/*     } */
    return(true);
}