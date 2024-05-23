/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoikoet <jgoikoet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:29:00 by jgoikoet          #+#    #+#             */
/*   Updated: 2024/05/15 17:45:30 by jgoikoet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <netdb.h>

int main() {
    const char* protocol_name = "tcp"; // Nombre del protocolo TCP

    // Obtener información sobre el protocolo TCP
    struct protoent *proto = getprotobyname(protocol_name);
    if (proto == nullptr) {
        std::cerr << "Error: Protocolo no encontrado" << std::endl;
        return 1;
    }

    std::cout << "Nombre del protocolo: " << proto->p_name << std::endl;
    std::cout << "Número del protocolo: " << proto->p_proto << std::endl;

    for(int i = 0; proto->p_aliases[i] != NULL; i++)
        std::cout << "Alias del protocolo: " << proto->p_aliases[i] << std::endl;

    return 0;
}
