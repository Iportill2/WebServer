/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoikoet <jgoikoet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:04:14 by jgoikoet          #+#    #+#             */
/*   Updated: 2024/05/21 16:43:49 by jgoikoet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sys/select.h>
#include <unistd.h>

int main() 
{
    fd_set conjunto_descriptores;
    FD_ZERO(&conjunto_descriptores);
    FD_SET(STDIN_FILENO, &conjunto_descriptores);

    struct timeval tiempo_espera;
    tiempo_espera.tv_sec = 5; // 5 segundos
    tiempo_espera.tv_usec = 0;

    std::cout << "Esperando entrada en stdin durante 5 segundos..." << std::endl;
    int resultado = select(STDIN_FILENO + 1, &conjunto_descriptores, NULL, NULL, &tiempo_espera);

    if (resultado == -1) {
        perror("Error en select()");
    } else if (resultado) {
        std::cout << "Se ha recibido entrada en stdin." << std::endl;
    } else {
        std::cout << "Tiempo de espera agotado." << std::endl;
    }

    return 0;
}
