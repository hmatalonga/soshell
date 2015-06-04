#include "shell.h"

mystack *read_history()
{
    FILE *fp = fopen(HIST_FILE, "r");
    char buf[BUFF_SIZE];
    mystack *s = NULL;

    if (fp == NULL)
    {
        fprintf(stderr, "No history file found\n");
        return NULL;
    }

    while (fgets(buf, BUFF_SIZE, fp) != NULL)
        s = append(s, buf);

    fclose(fp);
    return s;
}

char *get_last_cmd()
{
    mystack *s = read_history(), *r = NULL;

    while (s != NULL)
    {
        r = push(r, s->value);
        s = s->next;
    }

    if (r != NULL)
    {
        fprintf(stderr, "%s", r->value);
        return r->value;
    }

    return NULL;
}

char *get_nth_cmd(int index)
{
    mystack *s = read_history(), *r = NULL;
    int i = index;

    while (s != NULL)
    {
        r = push(r, s->value);
        s = s->next;
    }

    if (i > 0) // forward history
    {
        i--;
        while (s != NULL && i > 0)
        {
            i--;
            s = s->next;
        }    
    }
    else // backwards history
    {
        i++;
        while (r != NULL && i < 0)
        {
            i++;
            r = r->next;
        }         
    }

    if (index > 0)
    {
        if (s != NULL && i == 0)
        {
            fprintf(stderr, "%s", s->value);
            return s->value;
        }
    }
    else
    {
        if (r != NULL && i == 0)
        {
            fprintf(stderr, "%s", r->value);
            return r->value;
        }
    }

    return NULL;
}

char *get_exp_cmd(char *match)
{
    mystack *s = read_history(), *r = NULL;
    int found = 0;

    while (s != NULL)
    {
        r = push(r, s->value);
        s = s->next;
    }

    while (r != NULL)
    {
        if (strstr(r->value, match) != NULL)
        {
            found = 1;
            break;
        }
        r = r->next;
    }

    if (found)
    {
        fprintf(stderr, "%s", r->value);
        return r->value;
    }
    
    return NULL;
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
    char s1[BUFF_SIZE], s2[BUFF_SIZE];

    if (strcmp(args, "!") == 0)
        return get_last_cmd();
    else if (sscanf(args, "%d", &i) == 1)
        return get_nth_cmd(i);
    else if (sscanf(args, "-%d", &i) == 1)
        return get_nth_cmd(-1*i);
    else if (sscanf(args, "%s", &s1) == 1)
        return get_exp_cmd(s1);
    else
    {
        fprintf(stderr, "Invalid format\n");
        return NULL;
    }
}