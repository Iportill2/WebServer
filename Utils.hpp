#pragma once
# include "dependences.hpp"
class Utils
{
    public:
        static bool         isFile(const char* path);
        static bool         isDirectory(const char* path);
        static std::string  toString(const int &num);
        static int          toInt(const std::string &str);
};