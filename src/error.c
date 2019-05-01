/*
** EPITECH PROJECT, 2019
** Untitled (Workspace)
** File description:
** error
*/

#include "chap.h"

void error(char *str)
{
    printf("Exit failure: %s failed.\n", str);
    _exit(84);
}