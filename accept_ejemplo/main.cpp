/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoikoet <jgoikoet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 19:37:55 by jgoikoet          #+#    #+#             */
/*   Updated: 2024/05/14 19:39:26 by jgoikoet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    // Crear un socket TCP IPv4
    int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_fd == -1) {
        perror("Error al crear el socket");
        return 1;
    }

    // Configurar la dirección del servidor
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);

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

    std::cout << "Servidor escuchando en el puerto 8080." << std::endl;

    // Esperar una conexión entrante
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    int client_fd = accept(listen_fd, reinterpret_cast<struct sockaddr*>(&client_addr), &client_addr_len);
    if (client_fd == -1) {
        perror("Error al aceptar la conexión del cliente");
        close(listen_fd);
        return 1;
    }

    std::cout << "Conexión aceptada desde " << inet_ntoa(client_addr.sin_addr) << std::endl;

    // Cerrar el socket de escucha antes de salir
    close(listen_fd);

    return 0;
}
