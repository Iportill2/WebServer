/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoikoet <jgoikoet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 20:19:06 by jgoikoet          #+#    #+#             */
/*   Updated: 2024/05/14 20:20:54 by jgoikoet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

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

    // Búfer para almacenar los datos recibidos
    char buffer[1024] = {0};

    // Recibir datos del servidor
    ssize_t bytes_received = recv(sockfd, buffer, sizeof(buffer), 0);
    if (bytes_received == -1) {
        perror("Error al recibir datos");
        close(sockfd);
        return 1;
    }

    // Imprimir los datos recibidos
    std::cout << "Datos recibidos del servidor: " << buffer << std::endl;

    // Cerrar el socket antes de salir
    close(sockfd);

    return 0;
}
