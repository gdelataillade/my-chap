/*
** EPITECH PROJECT, 2019
** Untitled (Workspace)
** File description:
** send
*/

#include "chap.h"

void send_msg(struct client_s *client, char *msg)
{
    struct packet_s packet;

    init_packet(&packet, client->flags.target,
        client->flags.port, strlen(msg));
    if (sendto(client->sockfd, packet.data, packet.iph.tot_len, 0,
        (struct sockaddr *)&client->my_addr, sizeof(client->my_addr)) < 0) {
            error("sendto");
        }
    (void)msg;
}