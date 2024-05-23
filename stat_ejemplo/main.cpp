#include <iostream>
#include <sys/stat.h>

int main() {
    const char* filename = "archivo.txt";
    struct stat filestat;

    // Obtener información sobre el archivo
    if (stat(filename, &filestat) == 0) {
        std::cout << "Tamaño del archivo: " << filestat.st_size << " bytes" << std::endl;
        std::cout << "Permisos del archivo: " << (filestat.st_mode & 0777) << std::endl;
        std::cout << "Fecha de última modificación: " << ctime(&filestat.st_mtime);
        std::cout << "ID del usuario: " << filestat.st_uid << std::endl;
    } else {
        perror("Error al obtener información sobre el archivo");
        return 1;
    }

    return 0;
}
