/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoikoet <jgoikoet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 20:11:32 by jgoikoet          #+#    #+#             */
/*   Updated: 2024/05/14 20:16:28 by jgoikoet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring> 

int main() {
    // Crear un socket TCP IPv4
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("Error al crear el socket");
        return 1;
    }

    // Conectar el socket a un servidor
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Dirección IP del servidor
    server_addr.sin_port = htons(8080); // Puerto del servidor
    if (connect(sockfd, reinterpret_cast<struct sockaddr*>(&server_addr), sizeof(server_addr)) == -1) {
        perror("Error al conectar al servidor");
        close(sockfd);
        return 1;
    }

    // Datos a enviar
    const char* message = "¡Hola, servidor!";

    // Enviar datos al servidor
    ssize_t bytes_sent = send(sockfd, message, strlen(message), 0);
    if (bytes_sent == -1) {
        perror("Error al enviar datos");
        close(sockfd);
        return 1;
    }

    std::cout << "Datos enviados al servidor." << std::endl;

    // Cerrar el socket antes de salir
    close(sockfd);

    return 0;
}
