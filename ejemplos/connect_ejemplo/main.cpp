/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoikoet <jgoikoet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:10:56 by jgoikoet          #+#    #+#             */
/*   Updated: 2024/05/15 14:11:04 by jgoikoet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    // Crear un socket TCP IPv4
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("Error al crear el socket");
        return 1;
    }

    // Definir la dirección del servidor al que se desea conectar
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Dirección IP del servidor
    server_addr.sin_port = htons(8080); // Número de puerto del servidor

    // Conectar el socket al servidor
    if (connect(sockfd, reinterpret_cast<struct sockaddr*>(&server_addr), sizeof(server_addr)) == -1) {
        perror("Error al conectar al servidor");
        close(sockfd);
        return 1;
    }

    std::cout << "Conexión establecida correctamente con el servidor" << std::endl;

    // Cerrar el socket antes de salir
    close(sockfd);

    return 0;
}
