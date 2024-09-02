
#include "Error.hpp"

Error::Error(int er, int fdescriptor, srv & server)
{
    std::cout << "\nE\n";
    sendError(server, er, fdescriptor);
}

Error::~Error() {}

std::string Error::status(int error, srv & server)
{
    return server.arErr[0].defaultErMap[error];
}
std::string Error::toString(const int &num)
{
    std::stringstream s;
    s << num;
    return (s.str());
}

void    Error::sendError(srv & server, int error, int fd)
{
    std::string httpResponse = status(error,server);
    //write(1, httpResponse.c_str(), httpResponse.size());
    write(fd, httpResponse.c_str(), httpResponse.size());
}