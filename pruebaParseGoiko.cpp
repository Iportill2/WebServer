

# include "dependences.hpp"

struct vars
{
    std::string listen;
    std::string server_name;
    std::string body_size;
    std::string root;

    std::vector<std::string> location;
};

void pruebaParseGoiko(std::string & s)
{
    std::cout   << std::endl;

    std::string line;
    std::istringstream stream(s);
    vars v;

    while (std::getline(stream, line)) 
	{
		std::istringstream lineStream(line);
		std::string key;

		lineStream >> key;

        if (key == "listen")
        {
            lineStream >> v.listen;
            if (v.listen[v.listen.size() - 1] == ';')
                v.listen = v.listen.substr(0, v.listen.size() - 1);
        }
        if (key == "server_name")
        {
            lineStream >> v.server_name;
            if (v.server_name[v.server_name.size() - 1] == ';')
                v.server_name = v.server_name.substr(0, v.server_name.size() - 1);
        }

        if (key == "body_size")
        {
            lineStream >> v.body_size;
            if (v.body_size[v.body_size.size() - 1] == ';')
                v.body_size = v.body_size.substr(0, v.body_size.size() - 1);
        }
        if (key == "location")
        {
            std::string loc;
            loc = line + '\n';
            while (1)
            {
                std::getline(stream, line);
                loc += line + '\n';
                if (line.find('}') != std::string::npos)
                {
                    v.location.push_back(loc);
                    break;
                }
            }
        }

	} 
    std::cout << "listen: " << "\"" << v.listen <<  "\"" << std::endl;
    std::cout << "Server name: " << "\"" << v.server_name <<  "\"" << std::endl;
    std::cout << "body size: " << "\"" << v.body_size <<  "\"" << std::endl;
    std::cout << "location 1: " << "\"" << v.location[0] <<  "\"" << std::endl;
    std::cout << "location 2: " << "\"" << v.location[1] <<  "\"" << std::endl;

    std::cout   << std::endl;
}