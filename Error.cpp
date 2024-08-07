
#include "Error.hpp"
std::string Error::ErrorPage404 = "";

Error::Error(int er, int fdescriptor, srv server): error(er), fd(fdescriptor) 
{

/*     if(!server.arErr.empty())
        ErrorPage404 = server.arErr.ErrorRoot; */
    sendError(server);
    //std::cout << "server.arErr[0].defaultErMap[error]= " << server.arErr[0].defaultErMap[error] << "\n";
}

Error::~Error() {}

std::string Error::status(int error, srv server)
{
    return server.arErr[0].defaultErMap[error];
}
std::string Error::toString(const int &num)
{
    std::stringstream s;
    s << num;
    return (s.str());
}

void    Error::sendError(srv server)
{
    std::string httpResponse = status(error,server);
    write(fd, httpResponse.c_str(), httpResponse.size());
}