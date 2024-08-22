
#include "Cgi.hpp"

Cgi::Cgi(std::string  bd, int f) : body(bd), fd(f)
{
    std::cout << "Body en cgi: " << "\"" << body << "\"" << std::endl;
    parse();
    exec();
    sendResult();
    std::cout << "Result: " << "\"" << result << "\"" << std::endl << std::endl << std::endl << std::endl << std::endl;
}

Cgi::~Cgi(){}

void Cgi::parse()
{
    value = body.substr(7);
    std::cout << "Value en cgi: " << "\"" << value << "\"" << std::endl;
}

void Cgi::exec()
{
    int id;
    char* args[] = {(char*)"a.out", (char*)value.c_str(), NULL};

    int pipefd[2];

    pipe(pipefd);

    id = fork();

    if (id == 0)
    {
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        execve("cgi/./ia.out", args, NULL);
        std::cout << std::endl << std::endl;
    }
    else
    {
        
        ssize_t count = read(pipefd[0], res, sizeof(res) - 1);
        res[count] = '\0';
        close(pipefd[0]);
        std::string r(res);
        result = r;
        wait(NULL);
    }

}

/* std::string Cgi::getResult()
{
    return (result);
} */

/* void Cgi::sendResult()
{
    Error r(403, fd);
} */

void Cgi::sendResult()
{
    std::string httpResponse = "HTTP/1.1 200 OK\r\n";
   	httpResponse += "Content-Type: text/html\r\n";
  	httpResponse += "\r\n";

    httpResponse += "<!DOCTYPE html>";
    httpResponse += "<html lang=\"es\">";

    httpResponse += "<head>";
    httpResponse += "<meta charset=\"UTF-8\">";
    httpResponse += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
    httpResponse += "<title>Magia!</title>";
    httpResponse += "</head>";

    httpResponse += "<body>";
    httpResponse += "<h2>Resultado: " + result + "</h2>";
    httpResponse += "<img src= \"nu.jpg\">";
    httpResponse += "</body>";
    httpResponse += "</html>";

    //std::string prueba = "MAMON";
    //write (fd, prueba.c_str(), sizeof(prueba));

    write (fd, httpResponse.c_str(), httpResponse.size());
    //std::cout << "-----------hola------------" << std::endl;
}