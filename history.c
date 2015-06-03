#include "shell.h"

void get_history(char *args)
{
    int i;
    if (strcmp(args, "!") == 0)
    {
        // return last cmd
    }
    else if (sscanf(args, "-%d", &i) == 1)
    {
        // return n cmd
    }
    else
    {
        fprintf(stderr, "Invalid format\n");
        return;
    }
}