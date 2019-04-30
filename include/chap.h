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
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <netdb.h>
#include <errno.h>

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
};

// server.c
void start_client(struct flags_s *flags);

// error.c
void error(char *str);

#endif
