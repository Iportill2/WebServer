
# include "Load.hpp"

Load::Load(Request * r, int f, std::string & url) : rq(r), fd(f), _url(url)
{
    //createTextFile();
}


bool    Load::createFile()
{
    std::string path = _url + "/" + rq->getUpFileName();
    //std::string path = "uploaded_files/" + rq->getUpFileName();
    std::cout << "path:" << path << std::endl;

    std::ofstream file(path.c_str(), std::ios::out | std::ios::binary);

    if (file.is_open())
    {
        file << rq->getUpFileContent();
        file.close();
    }
    else
        return (Error(500, fd), false);
    
    if (file.fail())
        return (Error(500, fd), false);

    return true;
}

Load::~Load(){}

