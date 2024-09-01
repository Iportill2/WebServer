
# include <sstream>
# include <iostream>
# include <unistd.h>

int toInt(const std::string &str)
{
    std::stringstream ss(str);
    int num;
    ss >> num;
    return (num);
}

std::string getStdInput()
{
    std::string numero;
    std::getline(std::cin, numero);
    return numero;
}

void    sendResult(int n)
{
	(void)n;
    /* int outPipe[2];
	pipe(outPipe);
    dup2(outPipe[1], 1);
    dup2(outPipe[0], 0);
    close(outPipe[0]);
	close(outPipe[1]); */
	std::cout << n << std::endl;
	//close(1);
	//close(0);
	//write(1, "hola", 4);
}

int main ()
{
    //std::cerr << "Buenas tarde biesvenido al marasvilloso mundos de las magia" << std::endl;
    std::string number;

    if (getenv("QUERY_STRING"))
	{
		std::cerr << std::endl << "*******GET**********" << std::endl;
        number =  getenv("QUERY_STRING");
	}
    else
	{
		std::cerr << std::endl << "*******POST**********" << std::endl;
        number = getStdInput();
	}

    std::cerr << std::endl << "QUERY_STRING en cgi = " << number << std::endl;
    //std::cerr << std::endl << "Resultado = " << toInt(number) * 2 << std::endl;
	sendResult(toInt(number) * 2);

    return 0;
}