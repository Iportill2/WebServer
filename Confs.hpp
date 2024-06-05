
#pragma once

#include "dependences.hpp"
#include <string>
#include <vector>
#include <map>
struct loc
{
	std::string file;
	std::string root;
	std::vector<std::string> methods;
};


class Confs
{
	public:

		std::string host;
		std::string server_name;
		int			port;
		int			body_size;

		std::map<std::string, loc> location;
};