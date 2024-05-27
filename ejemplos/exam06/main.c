/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoikoet <jgoikoet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:18:34 by jgoikoet          #+#    #+#             */
/*   Updated: 2024/05/22 17:23:09 by jgoikoet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>

// para conectarse: nc localhost 8080

typedef struct client
{
    int fd;
    int id;
}   client;

void err(char *s)
{
    write(2, s, strlen(s));
    exit(1);
}

int main(int c, char **v)
{
    if (c != 2)
        err("Wrong number of arguments\n");

    int maxfd, sockfd, nextid = 0;
    fd_set readyfds, activefds;
    char buff[200000], msg_buff[200000];
    struct sockaddr_in servaddr;
    client clients[200];

    bzero(&servaddr, sizeof(servaddr));
    bzero(&clients, sizeof(clients));

    FD_ZERO(&activefds);

    servaddr.sin_family = AF_INET; 
	servaddr.sin_port = htons(atoi(v[1]));
	servaddr.sin_addr.s_addr = htonl(2130706433); //127.0.0.1

    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd == -1)
        err("Fatal error\n");

    if ((bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr))) != 0)
        err("Fatal error\n");

    if (listen(sockfd, 10) != 0)
        err("Fatal error\n");

    maxfd = sockfd;

    FD_SET(sockfd, &activefds);

    while (32)
    {
        readyfds = activefds;

        if (select(maxfd + 1, &readyfds, NULL, NULL, NULL) < 0)
            err("Fatal error\n");
        
        for (int i = 0; i <= maxfd; i++)
        {
            if (!FD_ISSET(i, &readyfds))
                continue;

            bzero(buff, sizeof(buff));

            if (i == sockfd)
            {
                int clifd = accept(sockfd, NULL, NULL);	
	            if (clifd < 0)
                    err("Fatal error\n");

                FD_SET(clifd, &activefds);
                if (clifd > maxfd)
                    maxfd = clifd;

                clients[clifd].id = nextid++;
                clients[clifd].fd = clifd;

                sprintf(buff, "server: client %d just arrived\n", clients[clifd].id);
                for (int j = 0; j < 200; j++)
                {
                    if (clients[j].fd && clients[j].fd != clifd)
                        send(clients[j].fd, buff, strlen(buff), 0);
                }
            }
            else
            {
                bzero(msg_buff, sizeof(msg_buff));

                int bytes = recv(i, buff, sizeof(buff) - 1, 0);
                if (bytes <= 0)
                {
                    sprintf(msg_buff, "server: client %d just left\n", clients[i].id);
                    for (int j = 0; j < 200; j++)
                    {
                        if (clients[j].fd && clients[j].fd != i)
                            send(clients[j].fd, msg_buff, strlen(msg_buff), 0);
                    }
                    FD_CLR(i, &activefds);
                    close(i);
                }
                else
                {
                    sprintf(msg_buff, "client %d: ", clients[i].id);
                    for (int j = 0; j < 200; j++)
                    {
                        if (clients[j].fd && clients[j].fd != i)
                        {
                            send(clients[j].fd, msg_buff, strlen(msg_buff), 0);
                            for (int k = 0; buff[k]; k++)
                            {
                                if (buff[k] == '\n' && buff[k + 1])
                                {
                                    send(clients[j].fd, "\n", 1, 0);
                                    send(clients[j].fd, msg_buff, strlen(msg_buff), 0);
                                }
                                else
                                    send(clients[j].fd, &buff[k], 1, 0);
                            }
                        }
                    }
                }
            }
        }
    }
    return(0);
}