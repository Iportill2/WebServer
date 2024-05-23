#include <iostream>
#include <fcntl.h>
#include <unistd.h>


/*CHEQUEA PERMISOS (FLAGS)*/

int main() {
    // Abrir un archivo
    int fd = open("archivo.txt", 4);
    if (fd == -1) {
        perror("Error al abrir el archivo");
        return 1;
    }

    // Obtener los flags de estado del descriptor de archivo
    int flags = fcntl(fd, F_GETFL);
    if (flags == -1) {
        perror("Error al obtener los flags de estado");
        close(fd);
        return 1;
    }

    std::cout << "flags: " << flags << std::endl;
    // Comprobar si el archivo está en modo de solo lectura
    if (flags & O_RDONLY) {
        std::cout << "El archivo está en modo de solo lectura" << std::endl;
    }
    else if (flags & O_WRONLY) {
        std::cout << "El archivo está en modo de solo escritura" << std::endl;
    }
    else if (flags & O_RDWR) {
        std::cout << "El archivo está en modo de lectura y escritura" << std::endl;
    }
    else
        std::cout << "El archivo está en algun modo extraño del orto" << std::endl;
    // Cerrar el archivo
    close(fd);

    return 0;
}
