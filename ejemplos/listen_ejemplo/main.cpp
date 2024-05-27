/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoikoet <jgoikoet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 19:55:35 by jgoikoet          #+#    #+#             */
/*   Updated: 2024/05/14 19:55:39 by jgoikoet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

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

    // Marcar el socket como un socket de escucha y especificar el tamaño máximo de la cola de conexiones pendientes
    if (listen(listen_fd, SOMAXCONN) == -1) {
        perror("Error al escuchar en el socket");
        close(listen_fd);
        return 1;
    }

    std::cout << "Servidor escuchando en el puerto 8080." << std::endl;

    // Cerrar el socket de escucha antes de salir
    close(listen_fd);

    return 0;
}
