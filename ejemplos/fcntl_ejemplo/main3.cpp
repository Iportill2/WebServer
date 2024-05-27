/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main3.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoikoet <jgoikoet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:53:18 by jgoikoet          #+#    #+#             */
/*   Updated: 2024/05/16 12:53:34 by jgoikoet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fcntl.h>
#include <unistd.h>

/*DUPLICAR FD*/

int main() {
    // Abrir un archivo
    int fd_orig = open("archivo.txt", O_RDONLY);
    if (fd_orig == -1) {
        perror("Error al abrir el archivo original");
        return 1;
    }

    // Duplicar el descriptor de archivo
    int fd_copy = fcntl(fd_orig, F_DUPFD, 0);
    if (fd_copy == -1) {
        perror("Error al duplicar el descriptor de archivo");
        close(fd_orig);
        return 1;
    }

    std::cout << "El descriptor de archivo se ha duplicado correctamente" << std::endl;

    // Cerrar los archivos
    close(fd_orig);
    close(fd_copy);

    return 0;
}
