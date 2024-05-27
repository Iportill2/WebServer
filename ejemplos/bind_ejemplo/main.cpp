/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoikoet <jgoikoet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:59:28 by jgoikoet          #+#    #+#             */
/*   Updated: 2024/05/15 13:59:47 by jgoikoet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {
    // Crear un socket TCP IPv4
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("Error al crear el socket");
        return 1;
    }

    // Definir la dirección a la cual asociar el socket
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY; // Escuchar en todas las interfaces
    addr.sin_port = htons(8080); // Número de puerto

    // Asociar el socket a la dirección y puerto especificados
    if (bind(sockfd, reinterpret_cast<struct sockaddr*>(&addr), sizeof(addr)) == -1) {
        perror("Error al asociar el socket");
        close(sockfd);
        return 1;
    }

    std::cout << "Socket asociado correctamente" << std::endl;

    // Cerrar el socket antes de salir
    close(sockfd);

    return 0;
}
