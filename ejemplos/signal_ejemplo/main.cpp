#include <iostream>
#include <csignal>
#include <unistd.h>

void signalHandler(int signum) {
    std::cout << "Se ha recibido la señal " << signum << std::endl;
    std::cout << "Presiona Ctrl+C para generar la señal SIGINT..." << std::endl;
    //exit(signum);  
}

int main() {
    // Configurar el manejador de señales para SIGINT
    signal(SIGINT, signalHandler);

    std::cout << "Presiona Ctrl+C para generar la señal SIGINT..." << std::endl;

    // Ejecutar un bucle infinito
    while(true) {
        sleep(1); // Hacer que el programa duerma durante un segundo
    }

    return 0;
}
