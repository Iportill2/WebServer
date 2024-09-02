
#include "Cgi.hpp"
pid_t Cgi::child_pid = -1; // Inicialización estática
bool Cgi::alarm_triggered = false; // Inicialización estática

Cgi::Cgi(std::string bd, int f, std::string exename, srv Server)
    : body(bd), fd(f), exe_name(exename), value(""), result(""), server(Server) 
{
    std::cout << "Body en cgi: " << "\"" << body << "\"" << std::endl;

    if (parse() == false)
        return;
    if (exec() == false)
        return;

    std::cout << "Result: " << "\"" << result << "\"" << std::endl;
}

Cgi::~Cgi() {}

bool Cgi::tienePermisosDeEjecucion(const std::string& rutaArchivo) 
{
    struct stat info;

    if (stat(rutaArchivo.c_str(), &info) != 0) 
    {
        std::cerr << "Error: No se pudo obtener la información del archivo." << std::endl;
        return false;
    }

    return (info.st_mode & S_IXUSR) || (info.st_mode & S_IXGRP) || (info.st_mode & S_IXOTH);
}

bool Cgi::parse() 
{
    value = body.substr(7);
    std::cout << "Value en cgi: " << "\"" << value << "\"" << std::endl;

    if (tienePermisosDeEjecucion(exe_name)) 
        return true; 
    else 
    {
        Error r(403, fd, server);
        return false;
    }
}

void Cgi::handle_alarm(int sig) 
{
    std::cout << "JAMON" << std::endl;
    (void)sig;
    alarm_triggered = true;
    if (child_pid != -1) 
        kill(child_pid, SIGTERM); // Usar SIGTERM para permitir limpieza
}


bool Cgi::exec() {
    int id;
    char* args[] = {(char*)exe_name.c_str(), (char*)value.c_str(), NULL};

    int pipefd[2];
    if (pipe(pipefd) == -1) {
        std::cerr << "Error en pipe: " << strerror(errno) << std::endl;
        return false;
    }

    signal(SIGALRM, handle_alarm);

    id = fork();

    if (id == 0) {
        // Proceso hijo
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        execve(args[0], args, NULL);
        std::cerr << "Error: No se pudo ejecutar el archivo" << std::endl;
        exit(1);
    } else if (id > 0) {
        // Proceso padre
        child_pid = id;
        close(pipefd[1]);

        alarm(1);

        int status;
        pid_t ret;
        bool child_exited = false;

        while (!child_exited) 
        {
            ret = waitpid(id, &status, WNOHANG);

            if (ret == -1) 
            {
                std::cerr << "Error en waitpid: " << strerror(errno) << std::endl;
                break;
            }

            if (ret == id) {
                child_exited = true;
            }

            usleep(100000);
        }

        alarm(0);

        if (alarm_triggered) {
            sendResult("salio del bucle de forma manual");
            return false;
        } else {
            ssize_t count = read(pipefd[0], res, sizeof(res) - 1);
            if (count < 0) {
                std::cerr << "Error en read: " << strerror(errno) << std::endl;
                return false;
            }
            res[count] = '\0';
            close(pipefd[0]);
            result = res;
            wait(NULL);
            sendResult(result);
            return true;
        }
    } else {
        std::cerr << "Error en fork: " << strerror(errno) << std::endl;
        return false;
    }
}

void Cgi::sendResult(const std::string& content) {
    std::string httpResponse = "HTTP/1.1 200 OK\r\n";
    httpResponse += "Content-Type: text/html\r\n";
    httpResponse += "\r\n";

    httpResponse += "<!DOCTYPE html>";
    httpResponse += "<html lang=\"es\">";

    httpResponse += "<head>";
    httpResponse += "<meta charset=\"UTF-8\">";
    httpResponse += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
    httpResponse += "<title>Resultado</title>";
    httpResponse += "</head>";

    httpResponse += "<body>";
    httpResponse += "<h2>Resultado: " + content + "</h2>";
    httpResponse += "<img src=\"/landing_page/cgi/nu.jpg\" alt=\"Imagen de un Ñu\">";
    httpResponse += "<p><a href=\"/landing_page\">Volver a la página de inicio</a></p>";
    httpResponse += "</body>";
    httpResponse += "</html>";

    write(fd, httpResponse.c_str(), httpResponse.size());
}
/* Cgi::Cgi(std::string  bd, int f, std::string exename, srv Server) : body(bd), fd(f), exe_name(exename), server(Server)
{
    std::cout << "Body en cgi: " << "\"" << body << "\"" << std::endl;
    
    if(parse() == 0)
        return;
    exec();
    sendResult();
    std::cout << "Result: " << "\"" << result << "\"" << std::endl << std::endl << std::endl << std::endl << std::endl;
}

Cgi::~Cgi(){}
bool Cgi::tienePermisosDeEjecucion(const std::string& rutaArchivo) 
{
    struct stat info;

    // Obtener la información del archivo
    if (stat(rutaArchivo.c_str(), &info) != 0) {
        std::cerr << "Error: No se pudo obtener la información del archivo." << std::endl;
        return false;
    }

    // Verificar si el archivo es ejecutable por el usuario actual
    if ((info.st_mode & S_IXUSR) ||  // El propietario del archivo tiene permiso de ejecución
        (info.st_mode & S_IXGRP) ||  // El grupo tiene permiso de ejecución
        (info.st_mode & S_IXOTH)) {  // Otros tienen permiso de ejecución
        return access(rutaArchivo.c_str(), X_OK) == 0;
    }

    return false;
}

bool Cgi::parse()
{
    value = body.substr(7);//numero= el tamaño es 7
    std::cout << "Value en cgi: " << "\"" << value << "\"" << std::endl;
    
    if (tienePermisosDeEjecucion(exe_name)) 
    {
        return(std::cout << "El usuario actual tiene permisos de ejecución sobre el archivo." << std::endl,true);
    } 
    else 
    {
        Error r(403, fd, server);
        return(false);
    }
}

void Cgi::exec()
{

    int id;
    char* args[] = {(char*)exe_name.c_str(), (char*)value.c_str(), NULL};

    int pipefd[2];

    pipe(pipefd);

    id = fork();

    if (id == 0)
    {
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        execve(args[0], args, NULL);
        std::cout << std::endl << std::endl;
        Error r(500, fd, server);
        //std::cerr << "Error: No se pudo ejecutar el archivo" << std::endl;
        exit(1); // Terminar el proceso hijo si execve falla
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
    httpResponse += "<img src=\"/landing_page/cgi/nu.jpg\" alt=\"Imagen de un Ñu\">";
    httpResponse += "<p><a href=\"/landing_page\">Volver a la página de inicio</a></p>";
    httpResponse += "</body>";
    httpResponse += "</html>";

    // Enviar la respuesta HTTP al cliente
    write(fd, httpResponse.c_str(), httpResponse.size());
} */
