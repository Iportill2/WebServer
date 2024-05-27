#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>

#define PORT 8081
#define BUFFER_SIZE 1024

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE];
    fd_set readfds;

    // Crear socket del servidor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Configurar el socket del servidor
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Vincular el socket del servidor a la dirección y puerto especificados
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Poner el servidor en modo escucha
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    std::cout << "Servidor escuchando en el puerto " << PORT << std::endl;

    while (true) {
        // Limpiar el conjunto de descriptores de archivo
        FD_ZERO(&readfds);

        // Agregar el descriptor de archivo del servidor al conjunto
        FD_SET(server_fd, &readfds);
        int max_sd = server_fd;

        // Esperar actividad en el descriptor de archivo del servidor
        int activity = select(max_sd + 1, &readfds, NULL, NULL, NULL);

        if ((activity < 0) && (errno != EINTR)) {
            std::cerr << "select error" << std::endl;
        }

        // Si algo sucede en el socket del servidor, es una nueva conexión
        if (FD_ISSET(server_fd, &readfds)) {
            if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
                perror("accept");
                exit(EXIT_FAILURE);
            }

            std::cout << "Nueva conexión, socket fd es " << new_socket << ", ip es: " << inet_ntoa(address.sin_addr) << ", puerto: " << ntohs(address.sin_port) << std::endl;

            // Leer datos del cliente
            int valread = read(new_socket, buffer, BUFFER_SIZE);
            if (valread < 0) {
                perror("read");
                close(new_socket);
            } else {
                buffer[valread] = '\0';
                std::cout << "Recibido: " << buffer << std::endl;
            }

            // Cerrar el socket del cliente
            close(new_socket);
        }
    }

    return 0;
}
