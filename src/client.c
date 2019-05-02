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

struct client_s init_client(struct flags_s flags, int sockfd)
{
    struct client_s client;

    client.sockfd = sockfd;
    client.flags = flags;
    client.my_addr.sin_family = AF_INET;
    client.my_addr.sin_port = htons(flags.port);
    return client;
}

void phase_one(struct client_s *client)
{
    send_msg(client, "client hello");
}

void phase_two(struct client_s *client)
{
    receive(client);
}

void phase_three(struct client_s *client)
{
    char *str = strcat(client->key, client->flags.password);
    char *outputBuffer = malloc(sizeof(char) * (SHA256_DIGEST_LENGTH * 2));
    unsigned char hash[SHA256_DIGEST_LENGTH] = {0};
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, str, strlen(str));
    SHA256_Final(hash, &sha256);
    int i = 0;
    
    while (i < SHA256_DIGEST_LENGTH) {
        sprintf(outputBuffer + (i * 2), "%02x", hash[i]);
        i += 1;
    }
    client->key = outputBuffer;
    send_msg(client, client->key);
}

void phase_four(struct client_s *client)
{
    // receive answer from server that indicates if authentification was
    // successfull or not
    receive(client);
}

void start_client(struct flags_s *flags)
{
    struct client_s client;
    int opt = 1;

    client.sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
    if (client.sockfd < 0)
        error("socket");
    client = init_client(*flags, client.sockfd);
    if (!inet_aton(client.flags.target, &client.my_addr.sin_addr))
        error("inet_aton");
    if (setsockopt(client.sockfd, IPPROTO_IP, IP_HDRINCL, &opt, sizeof(int)) < 0)
        error("setsockopt");
    phase_one(&client);
    phase_two(&client);
    printf("hash key: [%s]\n", client.key);
    phase_three(&client);
    phase_four(&client);
}