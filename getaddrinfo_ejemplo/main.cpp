/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoikoet <jgoikoet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:10:04 by jgoikoet          #+#    #+#             */
/*   Updated: 2024/05/15 17:14:31 by jgoikoet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h> // Para inet_ntop()
#include <cstring>     // Para memset()

int main() {
    const char* host = "www.example.com";
    const char* service = "http";

    struct addrinfo hints;
    struct addrinfo *result, *rp;

    // Establecer criterios para la resolución de direcciones
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;    // Permitir IPv4 o IPv6
    hints.ai_socktype = SOCK_STREAM; // Socket de flujo TCP
    hints.ai_flags = 0;
    hints.ai_protocol = 0;          // Cualquier protocolo

    // Realizar la resolución de direcciones
    int status = getaddrinfo(host, service, &hints, &result);
    if (status != 0) {
        std::cerr << "Error en getaddrinfo: " << gai_strerror(status) << std::endl;
        return 1;
    }

    // Iterar sobre los resultados obtenidos
    for (rp = result; rp != nullptr; rp = rp->ai_next) {
        // Imprimir la dirección IP y el número de puerto
        char addr_str[INET6_ADDRSTRLEN];
        void *addr;
        if (rp->ai_family == AF_INET) { // IPv4
            struct sockaddr_in *ipv4 = reinterpret_cast<struct sockaddr_in*>(rp->ai_addr);
            addr = &(ipv4->sin_addr);
        } else { // IPv6
            struct sockaddr_in6 *ipv6 = reinterpret_cast<struct sockaddr_in6*>(rp->ai_addr);
            addr = &(ipv6->sin6_addr);
        }
        inet_ntop(rp->ai_family, addr, addr_str, INET6_ADDRSTRLEN);
        std::cout << "Dirección IP: " << addr_str << std::endl;

        // Obtener el número de puerto
        uint16_t port;
        if (rp->ai_family == AF_INET) {
            struct sockaddr_in *ipv4 = reinterpret_cast<struct sockaddr_in*>(rp->ai_addr);
            port = ntohs(ipv4->sin_port);
        } else {
            struct sockaddr_in6 *ipv6 = reinterpret_cast<struct sockaddr_in6*>(rp->ai_addr);
            port = ntohs(ipv6->sin6_port);
        }
        std::cout << "Número de puerto: " << port << std::endl;
    }

    // Liberar la memoria asignada por getaddrinfo
    freeaddrinfo(result);

    return 0;
}

