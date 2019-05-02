/*
** EPITECH PROJECT, 2017
** 
** File description:
** .h file for 
*/

#ifndef PROJECT_H
#define PROJECT_H

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <openssl/sha.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <netdb.h>
#include <errno.h>
#include <string.h>

#define PACKET_SIZE         1024
#define PROTOCOL_MISMATCH   "Protocol Mismatch"

struct flags_s
{
    char *target;
    int port;
    char *password;
};

struct client_s
{
    struct flags_s flags;
    struct sockaddr_in my_addr;
    int sockfd;
    char *key;
};

struct packet_s
{
    struct iphdr iph;
    struct udphdr updh;
    char data[PACKET_SIZE];
};

// client.c
void start_client(struct flags_s *flags);

// error.c
void error(char *str);

// send.c
void send_msg(struct client_s *client, char *msg);

// receive.c
void receive(struct client_s *client);

// fill_header.c
void init_packet(struct packet_s *packet,
    const char *target, int port, size_t length);

#endif
