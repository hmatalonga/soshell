#include "shell.h"

int *proc_pipelines(char **args, int numargs, int *size)
{
    int *pipes = NULL;
    int i;

    *size = 0;

    for (i = 0; i < numargs; i++)
    {
        if (strcmp(args[i], "|") == 0)
        {
            pipes = (int *) malloc(++(*size)*sizeof(int));
            
            if (pipes == NULL)
                return NULL;

            pipes[*size-1] = i; // copy index of current pipe
        }            
    }

    return pipes;
}