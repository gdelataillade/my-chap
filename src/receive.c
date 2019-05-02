/*
** EPITECH PROJECT, 2019
** Untitled (Workspace)
** File description:
** receive
*/

#include "chap.h"

void receive(struct client_s *client)
{
    char buff[1024];
    struct sockaddr_storage sender;
    socklen_t size = sizeof(sender);
    size_t ret = recvfrom(client->sockfd, &buff, sizeof(buff), 0,
        (struct sockaddr *)&sender, &size);

    ret = recvfrom(client->sockfd, &buff, sizeof(buff), 0,
        (struct sockaddr *)&sender, &size);
    printf("server: [%s] of size %ld\n", buff, ret);
}