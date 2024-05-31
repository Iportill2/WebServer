#include "dependences.hpp"

location::location()
{
    std::cout << "Default location Constructor" << std::endl;
}
location::~location()
{
    std::cout << "location Destructor" << std::endl;
}
/* void createLocations(const srv& newServer) 
{
    for(int i = 0; i < newServer.locationCount; ++i) 
	{
        location.push_back(location());

		std::cout << MAGENTA << "Location: " << i << WHITE << std::endl;
    }
    // Ahora tienes un vector de instancias de Location
    // Hacer algo con las instancias de Location...
} */