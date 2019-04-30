/*
** EPITECH PROJECT, 2019
** Untitled (Workspace)
** File description:
** error
*/

#include "chap.h"

void error(char *str)
{
    printf("Error: %s.\nExit failure.\n", str);
    _exit(0);
}