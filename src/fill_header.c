/*
** EPITECH PROJECT, 2019
** chap (Workspace)
** File description:
** fill_header
*/

#include "chap.h"

void init_ip_header(struct iphdr *iphdr, const char *target, size_t length)
{
    iphdr->ihl = 5;
    iphdr->version = 4;
    iphdr->tos = 16;
    iphdr->tot_len = sizeof(struct iphdr) + sizeof(struct udphdr) + length;
    iphdr->id = htons(54321);
    iphdr->ttl = 64;
    iphdr->protocol = 17;
    iphdr->saddr = 0;
    iphdr->daddr = inet_addr(target);
    iphdr->check = 0;
    iphdr->frag_off = 0;
}

void init_udp_header(struct udphdr *udphdr, int port, size_t length)
{
    udphdr->source = htons(15000);
    udphdr->dest = htons(port);
    udphdr->len = htons(sizeof(struct udphdr) + length);
}

void init_packet(struct packet_s *packet, const char *target, int port,
    size_t length)
{
    init_ip_header(&packet->iph, target, length);
    init_udp_header(&packet->updh, port, length);
}