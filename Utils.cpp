
#include "Utils.hpp"

bool Utils::isFile(const char* path)
{
    struct stat info;
    if (stat(path, &info) != 0)
        return (false);

    return S_ISREG(info.st_mode);
}

bool Utils::isDirectory(const char* path)
{
    struct stat info;
    if (stat(path, &info) != 0)
        return false;

    return S_ISDIR(info.st_mode);
}

int Utils::toInt(const std::string &str)
{
    std::stringstream ss(str);
    int num;
    ss >> num;
    return (num);
}

std::string Utils::toString(const int &num)
{
    std::stringstream ss;
    ss << num;
    return (ss.str());
}

size_t Utils::size(const char *s)
{
	size_t i = 0;
	if (s == NULL)
		return 0;
	while (s[i] != '\0')
		++i;
	return i;
}
int Utils::countSubstring(const std::string& str, const std::string& sub)
{
    if (sub.length() == 0) 
        return 0;
    int count = 0;
    for (size_t offset = str.find(sub); offset != std::string::npos;offset = str.find(sub, offset + sub.length()))
        ++count;
    return count;
}


void Utils::deletespaces(std::string &s)
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


