/*
** EPITECH PROJECT, 2017
** 
** File description:
** .h file for 
*/

#ifndef PROJECT_H
#define PROJECT_H

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include <stdio.h>

// Structures:
struct option long_options[] = {
    {"target", required_argument, NULL, 't'},
    {"port", required_argument, NULL, 'p'},
    {"password", required_argument, NULL, 'P'},
    {0, 0, 0, 0}
};

struct client_s
{
    char *target;
    int port;
    char *password;
};

// Prototypes:

#endif
