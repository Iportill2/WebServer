/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dependences.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoikoet <jgoikoet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:25:48 by jgoikoet          #+#    #+#             */
/*   Updated: 2024/06/20 17:12:14 by jgoikoet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEPENDECES_HPP
# define DEPENDECES_HPP

# include <algorithm>
# include <arpa/inet.h>
# include <cctype>
# include <csignal>
# include <cstdlib>
# include <cstring>
# include <dirent.h>
# include <fcntl.h>
# include <fstream>
# include <iostream>
# include <limits>
# include <map>
# include <netinet/in.h>
# include <set>
# include <signal.h>
# include <sstream>
# include <stdbool.h>
# include <stack>
# include <stdexcept>
# include <stdio.h>
# include <string>
# include <sys/select.h>
# include <sys/socket.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <vector>
//COLORES
# define RED "\033[31m" ///////////
# define RST "\033[0m" ////////////
# define GREEN "\033[32m" ///////////
# define YELLOW "\033[33m" ///////////
# define BLUE "\033[34m" ///////////
# define MAGENTA "\033[35m" ///////////
# define CYAN "\033[36m" ///////////
# define WHITE "\033[37m" ///////////
# define BLACK "\033[30m" ///////////

# define BOLDBLACK "\033[1m\033[30m" ///////////
# define BOLDRED "\033[1m\033[31m" ///////////
# define BOLDGREEN "\033[1m\033[32m" ///////////
# define BOLDYELLOW "\033[1m\033[33m" ///////////
# define BOLDBLUE "\033[1m\033[34m" ///////////
# define BOLDMAGENTA "\033[1m\033[35m" ///////////
# define BOLDCYAN "\033[1m\033[36m" ///////////
# define BOLDWHITE "\033[1m\033[37m" ///////////

int autoindex(std::string path);

#endif