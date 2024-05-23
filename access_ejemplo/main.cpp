/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoikoet <jgoikoet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 13:26:47 by jgoikoet          #+#    #+#             */
/*   Updated: 2024/05/16 13:28:52 by jgoikoet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <unistd.h>

int main() {
    

    // Verificar si el archivo existe y si el proceso tiene permisos de lectura y escritura
    if (access("archivo.txt", R_OK | W_OK) == 0) {
        std::cout << "El archivo existe y tiene permisos de lectura y escritura" << std::endl;
    } else {
        std::cerr << "Error al acceder al archivo: " << std::endl;
        return 1;
    }

    return 0;
}
