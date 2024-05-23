#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <vector>
#include <cstring>

constexpr int MAX_EVENTS = 10;
constexpr int PORT = 8081;

int main() {
    // Crear un socket de escucha
    int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_fd == -1) {
        perror("Error al crear el socket de escucha");
        return 1;
    }

    // Configurar la dirección del servidor
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Enlazar el socket a la dirección y puerto especificados
    if (bind(listen_fd, reinterpret_cast<struct sockaddr*>(&server_addr), sizeof(server_addr)) == -1) {
        perror("Error al enlazar el socket");
        close(listen_fd);
        return 1;
    }

    // Escuchar en el socket
    if (listen(listen_fd, SOMAXCONN) == -1) {
        perror("Error al escuchar en el socket");
        close(listen_fd);
        return 1;
    }

    // Crear el objeto epoll
    int epoll_fd = epoll_create1(0);
    if (epoll_fd == -1) {
        perror("Error al crear el objeto epoll");
        close(listen_fd);
        return 1;
    }

    // Agregar el socket de escucha al conjunto de descriptores a ser monitoreados por epoll
    struct epoll_event event;
    event.events = EPOLLIN;
    event.data.fd = listen_fd;
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, listen_fd, &event) == -1) {
        perror("Error al agregar el socket de escucha al objeto epoll");
        close(listen_fd);
        close(epoll_fd);
        return 1;
    }

    // Vector para almacenar eventos
    std::vector<struct epoll_event> events(MAX_EVENTS);

    std::cout << "Servidor escuchando en el puerto " << PORT << std::endl;

    while (true) {
        // Esperar eventos en los descriptores de archivo monitoreados por epoll
        int num_events = epoll_wait(epoll_fd, events.data(), MAX_EVENTS, -1);
        if (num_events == -1) {
            perror("Error en epoll_wait");
            break;
        }

        // Procesar los eventos
        for (int i = 0; i < num_events; ++i) {
            if (events[i].data.fd == listen_fd) {
                // Nuevo cliente conectado
                struct sockaddr_in client_addr;
                socklen_t client_addr_len = sizeof(client_addr);
                int client_fd = accept(listen_fd, reinterpret_cast<struct sockaddr*>(&client_addr), &client_addr_len);
                if (client_fd == -1) {
                    perror("Error al aceptar la conexión del cliente");
                    continue;
                }

                // Configurar el nuevo socket de cliente como no bloqueante
                fcntl(client_fd, F_SETFL, fcntl(client_fd, F_GETFL) | O_NONBLOCK);

                // Agregar el socket de cliente al conjunto de descriptores a ser monitoreados por epoll
                event.events = EPOLLIN | EPOLLET; // EPOLLET para modo de borde
                event.data.fd = client_fd;
                if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_fd, &event) == -1) {
                    perror("Error al agregar el socket de cliente al objeto epoll");
                    close(client_fd);
                    continue;
                }

                std::cout << "Nuevo cliente conectado desde " << inet_ntoa(client_addr.sin_addr) << std::endl;
            } else {
                // Datos disponibles para lectura en un socket de cliente existente
                char buffer[1024];
                ssize_t bytes_read = recv(events[i].data.fd, buffer, sizeof(buffer), 0);
                if (bytes_read == -1) {
                    perror("Error al recibir datos del cliente");
                } else if (bytes_read == 0) {
                    // El cliente ha cerrado la conexión
                    std::cout << "Cliente desconectado" << std::endl;
                    epoll_ctl(epoll_fd, EPOLL_CTL_DEL, events[i].data.fd, nullptr);
                    close(events[i].data.fd);
                } else {
                    // Mostrar los datos recibidos del cliente
                    buffer[bytes_read] = '\0';
                    std::cout << "Datos recibidos del cliente (" << events[i].data.fd << "): " << buffer << std::endl;
                }
            }
        }
    }

    // Cerrar el socket de escucha y el objeto epoll antes de salir
    close(listen_fd);
    close(epoll_fd);

    return 0;
}
