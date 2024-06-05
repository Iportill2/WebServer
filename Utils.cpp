
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


