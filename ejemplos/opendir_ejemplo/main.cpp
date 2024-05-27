/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoikoet <jgoikoet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 13:53:54 by jgoikoet          #+#    #+#             */
/*   Updated: 2024/05/16 14:15:07 by jgoikoet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <dirent.h>

int main() {
    const char* dirname = "/home/jgoikoet/Desktop";
    DIR *dir;
    //struct dirent *entry;

    // Abrir el directorio
    dir = opendir(dirname);
    if (!dir) {
        perror("Error al abrir el directorio");
        return 1;
    }

    // Leer las entradas del directorio
   /*  while ((entry = readdir(dir)) != NULL) {
        std::cout << entry->d_name << std::endl;
    } */

     // Leer las entradas del directorio de otra manera
    while (readdir(dir) != NULL) {
        std::cout << readdir(dir)->d_name << std::endl;
    }

    // Cerrar el directorio
    closedir(dir);

    return 0;
}
