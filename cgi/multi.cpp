
# include <sstream>
# include <iostream>

int toLong(const std::string &str)
{
    std::stringstream ss(str);
    long num;
    ss >> num;
    return (num);
}

int main (int argc, char **argv)
{
    if (argc != 2)
        return 1;
    
    long i = toLong(argv[1]);
    long result = i * 2; 
    std::cout << result;

    return 0;
}