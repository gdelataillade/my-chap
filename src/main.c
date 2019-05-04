/*
** EPITECH PROJECT, 2019
** Untitled (Workspace)
** File description:
** main
*/

#include <getopt.h>
#include "chap.h"

const struct option long_options[] = {
    {"target", required_argument, NULL, 't'},
    {"port", required_argument, NULL, 'p'},
    {"password", required_argument, NULL, 'P'},
    {0, 0, 0, 0}
};

struct flags_s init_flags(void)
{
    struct flags_s flags;

    flags.password = NULL;
    flags.port = -1;
    flags.target = NULL;
    return flags;
}

char *convert_target(char *optarg)
{
    struct hostent *target = gethostbyname(optarg);

    if (!target) {
        printf("No such hostname: '%s'\n", optarg);
        exit(EXIT_FAILURE);
    }
    return (inet_ntoa(*((struct in_addr *)target->h_addr_list[0])));
}

void get_flags(int argc, char *argv[], struct flags_s *flags)
{
    int opt;
    int option_index = 0;

    while (1) {
        opt = getopt_long(argc, argv, "t:p:P:", long_options, &option_index);
        if (opt == -1)
            break;
        switch(opt) {
            case 't': flags->target = convert_target(optarg);
                break;
            case 'p': flags->port = atoi(optarg);
                break;
            case 'P': flags->password = optarg;
                break;
            default: error("getopt_long");
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc < 7)
        return (EXIT_FAILURE);
    struct flags_s flags = init_flags();

    get_flags(argc, argv, &flags);
    start_client(&flags);
    return (EXIT_SUCCESS);
}