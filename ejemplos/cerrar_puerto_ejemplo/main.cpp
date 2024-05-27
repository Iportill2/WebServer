#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    const int PORT = 8080;

    // Crear el socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Configurar opciones del socket
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Configurar dirección
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Vincular el socket al puerto
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Escuchar en el socket
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    std::cout << "Servidor en escucha en el puerto " << PORT << "..." << std::endl;

    // Aceptar una conexión entrante
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("accept");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Leer datos del cliente
    char buffer[1024] = {0};
    read(new_socket, buffer, 1024);
    std::cout << "Mensaje recibido: " << buffer << std::endl;

    // Responder al cliente
    const char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: 13\r\n\r\nHello, world!";
    write(new_socket, response, strlen(response));

    // Cerrar el socket del cliente
    close(new_socket);
    std::cout << "Socket del cliente cerrado." << std::endl;

    // Cerrar el socket del servidor
    if (close(server_fd) < 0) {
        perror("Error al cerrar el socket del servidor");
        exit(EXIT_FAILURE);
    }

    std::cout << "Socket del servidor cerrado y puerto liberado." << std::endl;

    return 0;
}
