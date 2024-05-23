#include <iostream>
#include <arpa/inet.h> // Para htons

int main() {
    unsigned short puerto_local = 8080;
    unsigned short puerto_convertido = htons(puerto_local);//convertido es: 36895
    std::cout << "Puerto local convertido a network byte order: " << puerto_convertido << std::endl;
    return 0;
}
