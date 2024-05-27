/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoikoet <jgoikoet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:47:38 by jgoikoet          #+#    #+#             */
/*   Updated: 2024/05/16 12:49:27 by jgoikoet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fcntl.h>
#include <unistd.h>

/*ESTABLECE EL FILE DESCRIPTOR COMO NO BLOQUEANTE*/

int main() {
    // Abrir un archivo
    int fd = open("archivo.txt", O_RDONLY);
    if (fd == -1) {
        perror("Error al abrir el archivo");
        return 1;
    }

    // Obtener los flags de estado del descriptor de archivo
    int flags = fcntl(fd, F_GETFL);
    if (flags == -1) {
        perror("Error al obtener los flags de estado");
        close(fd);
        return 1;
    }

    // Establecer el descriptor de archivo como no bloqueante
    flags |= O_NONBLOCK;
    if (fcntl(fd, F_SETFL, flags) == -1) {
        perror("Error al establecer el descriptor de archivo como no bloqueante");
        close(fd);
        return 1;
    }

    std::cout << "El descriptor de archivo se ha establecido como no bloqueante" << std::endl;

    // Cerrar el archivo
    close(fd);

    return 0;
}
