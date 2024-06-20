
# include "Load.hpp"

Load::Load(std::string  bd, int f) : body(bd), fd(f)
{
    std::cout << "Body en Load: " << "\"" << body << "\"" << std::endl;
    //parse();
    //exec();
    sendResult();
    //std::cout << "Result: " << "\"" << result << "\"" << std::endl << std::endl << std::endl << std::endl << std::endl;
}

Load::~Load(){}

void Load::parse()
{
    value = body.substr(5);
    std::cout << "Value en Load: " << "\"" << value << "\"" << std::endl;
}

void Load::exec()
{
    int id;
    char* args[] = {(char*)"ia.out", (char*)value.c_str(), NULL};

    int pipefd[2];

    pipe(pipefd);

    id = fork();

    if (id == 0)
    {
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        execve("Load/./ia.out", args, NULL);
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

/* std::string Load::getResult()
{
    return (result);
} */

/* void Load::sendResult()
{
    Error r(403, fd);
} */

void Load::sendResult()
{
    std::string httpResponse = "HTTP/1.1 200 OK\r\n";
   	httpResponse += "Content-Type: text/plain\r\n";
  	httpResponse += "\r\n";

    httpResponse += "<!DOCTYPE html>";
    httpResponse += "<html lang=\"es\">";

    httpResponse += "<head>";
    httpResponse += "<meta charset=\"UTF-8\">";
    httpResponse += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
    httpResponse += "<title>Magia!</title>";
    httpResponse += "</head>";

    httpResponse += "<body>";
    httpResponse += "</body>";
    httpResponse += "</html>";

    //std::string prueba = "MAMON";
    //write (fd, prueba.c_str(), sizeof(prueba));

    write (fd, httpResponse.c_str(), httpResponse.size());
    //std::cout << "-----------hola------------" << std::endl;
}