#include "shell.h"

char *get_last_cmd()
{
    FILE *fp = fopen(HIST_FILE, "r");
    char buf[BUFF_SIZE];

    if (fp == NULL)
    {
        fprintf(stderr, "No history file found\n");
        return NULL;
    }

    while (!feof(fp))
        fscanf(fp, "%s\n", buf);

    fclose(fp);
    fprintf(stderr, "%s\n", buf);

    return buf;
}

char *get_nth_cmd(int index)
{
    FILE *fp = fopen(HIST_FILE, "r");
    char buf[BUFF_SIZE];
    int i = index, aux = 0;

    if (fp == NULL)
    {
        fprintf(stderr, "No history file found\n");
        return NULL;
    }

    if (i > 0) // forward history
    {
        while (i-- && !feof(fp))
            fscanf(fp, "%s\n", buf);        
    }
    else // backwards history
    {
        while (!feof(fp)) // get the number of lines in the history file
        {
            fscanf(fp, "%s\n", buf);
            aux++;
        }
        
        rewind(fp);
        i = aux + index;

        while (i-- && !feof(fp))
            fscanf(fp, "%s\n", buf);    
    }

    fclose(fp);

    if (i == 0)
        fprintf(stderr, "%s\n", buf);
    else
        fprintf(stderr, "Invalid command index\n");

    return buf;
}

void add_history(char **args, int numargs)
{
    FILE *fp = fopen(HIST_FILE, "a");
    int i = 0;

    if (fp == NULL)
        return;

    for (; i < numargs-1; i++)
        fprintf(fp, "%s ", args[i]);
    fprintf(fp, "%s\n", args[numargs-1]);

    fclose(fp);

    return;
}

char *get_history(char *args)
{
    int i;

    if (strcmp(args, "!") == 0)
        return get_last_cmd();
    else if (sscanf(args, "%d", &i) == 1)
        return get_nth_cmd(i);
    else if (sscanf(args, "-%d", &i) == 1)
        return get_nth_cmd(-1*i);
    else
    {
        fprintf(stderr, "Invalid format\n");
        return NULL;
    }
}