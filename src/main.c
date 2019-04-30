/*
** EPITECH PROJECT, 2019
** Untitled (Workspace)
** File description:
** main
*/

#include "chap.h"

struct client_s init_struct(void)
{
    struct client_s client;

    client.password = NULL;
    client.port = -1;
    client.target = NULL;
    return client;
}

int main(int argc, char *argv[])
{
    int option_index = 0;
    int opt;
    struct client_s client = init_struct();

    while (1) {
        opt = getopt_long(argc, argv, "t:p:P:", long_options, &option_index);
        if (opt == -1)
            break;
        switch(opt) {
            case 't':
                client.target = optarg;
                break;
            case 'p':
                client.port = atoi(optarg);
                break;
            case 'P':
                client.password = optarg;
                break;
            default:
                puts("Wrong args\n");
                exit(1);
        }
    }
    printf("target: %s\n", client.target);
    printf("port: %d\n", client.port);
    printf("password: %s\n", client.password);
    return 0;
}