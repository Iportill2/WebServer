
# include <sstream>
# include <iostream>

int toInt(const std::string &str)
{
    std::stringstream ss(str);
    int num;
    ss >> num;
    return (num);
}

int main (int argc, char **argv)
{
    if (argc != 2)
        return 1;
    
    int i = toInt(argv[1]);

    std::cout << i * 2;;

    return 0;
}