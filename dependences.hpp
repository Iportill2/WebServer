/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dependences.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoikoet <jgoikoet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:25:48 by jgoikoet          #+#    #+#             */
/*   Updated: 2024/05/22 17:18:32 by jgoikoet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
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

# include <stdio.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <iostream>
# include <cstdlib>
# include <fstream>
# include <sstream>
# include <unistd.h>
# include <sys/select.h>
# include <stdbool.h>

#include <signal.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <string>
# include <iostream>
# include <sstream>
# include <vector>
# include <map>

# include "Config.hpp"
# include "Server.hpp"