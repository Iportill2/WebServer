/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoikoet <jgoikoet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:00:43 by jgoikoet          #+#    #+#             */
/*   Updated: 2024/05/13 16:57:57 by jgoikoet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ListeningSocket.hpp"

int main()
{
    std::cout << "Arrancandolo..." << std::endl;
    
    std::cout << "Binding Socket..." << std::endl; 
    HDE::BindingSocket bs = HDE::BindingSocket(AF_INET, SOCK_STREAM, 0, 8080, INADDR_ANY);

    std::cout << "Listening Socket..." << std::endl;
    HDE::ListeningSocket ls = HDE::ListeningSocket(AF_INET, SOCK_STREAM, 0, 8090, INADDR_ANY, 10);

    std::cout << "Esito total!" << std::endl;
}

/* int main() {
    std::cout << "Arrancando..." << std::endl;
    
    std::cout << "Creando y escuchando en el puerto 8080..." << std::endl; 
    HDE::ListeningSocket ls = HDE::ListeningSocket(AF_INET, SOCK_STREAM, 0, 8080, INADDR_ANY, 10);

    std::cout << "Éxito total!" << std::endl;
} */