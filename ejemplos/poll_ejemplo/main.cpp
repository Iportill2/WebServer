/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoikoet <jgoikoet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 17:29:55 by jgoikoet          #+#    #+#             */
/*   Updated: 2024/05/14 17:32:42 by jgoikoet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <poll.h>
#include <unistd.h>

int main() {
    struct pollfd fds[1];
    fds[0].fd = STDIN_FILENO; // Descriptor de archivo de entrada estándar
    fds[0].events = POLLIN;   // Esperar eventos de lectura

    std::cout << "Esperando entrada en stdin durante 5 segundos..." << std::endl;
    int resultado = poll(fds, 1, 5000); // Esperar durante 5 segundos

    std::cout << "Valgame!" << std::endl;

    if (resultado == -1)
    {
        perror("Error en poll()");
    } 
    else if (resultado)
    {
        if (fds[0].revents & POLLIN) {
            std::cout << "Se ha recibido entrada en stdin." << std::endl;
        }
    } else {
        std::cout << "Tiempo de espera agotado." << std::endl;
    }

    return 0;
}
