/*
** EPITECH PROJECT, 2019
** Untitled (Workspace)
** File description:
** receive
*/

#include "chap.h"

char *strdup(const char *s);

void receive(struct client_s *client)
{
    struct packet_s packet;
    memset(&packet, 0, sizeof(struct packet_s));
    struct sockaddr_storage sender;
    socklen_t size = sizeof(sender);
    size_t ret = recvfrom(client->sockfd, &packet, sizeof(struct packet_s), 0,
        (struct sockaddr *)&sender, &size);

    memset(packet.data, 0, 1024);
    ret = recvfrom(client->sockfd, &packet, sizeof(struct packet_s), 0,
        (struct sockaddr *)&sender, &size);
    if ((int)ret < 0)
        error("recvfrom");
    if (!strcmp(packet.data, PROTOCOL_MISMATCH)) {
        printf("%s\n", packet.data); // return KO ?
        _exit(0);
    }
    client->key = strdup(packet.data);
    if (!packet.data)
        error("hash key is null");
    client->key = strcpy(client->key, packet.data);
}