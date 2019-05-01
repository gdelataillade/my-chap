/*
** EPITECH PROJECT, 2019
** Untitled (Workspace)
** File description:
** client
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

void phase_one(struct client_s *client)
{
    // send "client hello" to server
    send(client, "client hello");
}

void phase_two(struct client_s *client)
{
    // receive challenge from server
    receive(client);
}

void phase_three(struct client_s *client)
{
    // encrypt and send answer to server
}

void phase_four(struct client_s *client)
{
    // receive answer from server that indicates if authentification was
    // successfull or not
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
    phase_one(&client);
    phase_two(&client);
    phase_three(&client);
    phase_four(&client);
    print_client_info(&client);
}   