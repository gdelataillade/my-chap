/*
** EPITECH PROJECT, 2019
** Untitled (Workspace)
** File description:
** server
*/

#include "chap.h"

int inet_aton(const char *cp, struct in_addr *inp);

void print_client_info(struct client_s *client)
{
    printf("target: %s\n", client->flags.target);
    printf("port: %d\n", client->flags.port);
    printf("password: %s\n", client->flags.password);
    printf("sockfd: %d\n", client->sockfd);
}

struct client_s init_client(struct flags_s flags)
{
    struct client_s client;

    client.flags = flags;
    client.my_addr.sin_family = AF_INET;
    client.my_addr.sin_port = htons(flags.port);
    return client;
}

void start_client(struct flags_s *flags)
{
    struct client_s client;

    client.sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
    if (client.sockfd == -1)
        error("socket failed");
    client = init_client(*flags);
    if (!inet_aton(client.flags.target, &client.my_addr.sin_addr))
        error("inet_aton failed");
    print_client_info(&client);
}   