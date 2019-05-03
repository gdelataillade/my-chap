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
    unsigned char hash[SHA256_DIGEST_LENGTH] = {0};
    SHA256_CTX sha256;
    char *output_buffer = {0};
    char tmp[256];

    strcpy(tmp, client->key);
    strcat(tmp, client->flags.password);
    output_buffer = calloc(1, sizeof(char) * ((SHA256_DIGEST_LENGTH * 2) + 1));
    if (!output_buffer)
        error("phase three - calloc");
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, tmp, strlen(tmp));
    SHA256_Final(hash, &sha256);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i)
        sprintf(output_buffer + (i * 2), "%02x", hash[i]);
    output_buffer[64] = 0;
    send_msg(client, output_buffer);
    free(output_buffer);
}

void phase_four(struct client_s *client)
{
    receive(client);
    if (!strncmp(client->key, "KO", 2))
        puts("KO");
    else
        printf("Secret: '%s'\n", client->key);
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
    phase_three(&client);
    phase_four(&client);
}