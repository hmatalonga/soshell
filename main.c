#include "shell.h"

char prompt[STRING_SIZE]; // prompt header output
int pos_x;
int pos_y;

void *f(void *args)
{
    data *x = (data *)args;
    sleep(x->temp);
    printf("%s\n", x->msg);
    pthread_exit(NULL);
    return NULL;
}

int main ()
{
    int len;
    int numargs;
    char buf[1024]; // a command buffer
    char *args[64]; // max of 64 arguments

    strcpy (prompt, "SOSHELL:$ ");

    while (1)
    {
        fprintf (stdout, "%s", prompt);

        if (fgets(buf, 1023, stdin) == NULL)
        {
            printf ("\n");
            exit (0);
        }

        len = strlen(buf);
        
        if ( 1==len )
            continue;   // string is only \n
        if ( buf[len-1] == '\n' )
            buf[len-1] = '\0';

        numargs = parse (buf, args);    // particiona a string em argumentos

        if (!builtin (args, numargs))            
            execute (args, numargs);    // executa o comando
    }

    return 0;
}

int builtin (char **args, int numargs)
{

    if (strcmp (args[0], "exit") == 0)
    {
        add_history(args, numargs);
        exit (0);
        return 1;
    }
    else if (strcmp (args[0], "help") == 0)
    {
        add_history(args, numargs);
        fprintf(stderr, "HELP\n");
        return 1;
    }
    else if (strncmp(args[0], "!", 1) == 0)
    {
        char *buf = get_history(args[0]+1);

        builtin(args, parse(buf, args));

        return 1;
    }
    else if (strncmp (args[0], "PS1=", 4) == 0)
    {
        add_history(args, numargs);
        strcpy(prompt, args[0]+4);
        return 1;
    }
    else if (strcmp (args[0], "cd") == 0)
    {
        char *userRaiz = getenv("HOME");
     
        add_history(args, numargs);

        if (args[1] != NULL) {
            if (strcmp(args[1], "~") == 0)
                chdir(userRaiz);
            else
                if (chdir(args[1]) < 0)
                    perror("Directoria inexistente\n");
        }
        else
            chdir(userRaiz);
        return 1;
    }
    else if (strcmp(args[0],"socp") == 0)
    {
        if (numargs == 3) {
            int fdin = open(args[1], FILE_MODE);
            int fdout = creat(args[2], FILE_MODE);
            int n, size = atoi(args[3]);
            void *buf = malloc(size);

            add_history(args, numargs);

            while ((n = read(fdin, buf, BUFF_SIZE)) > 0)
            {
                if (write(fdout, buf, n) != n)
                    perror("Erro de escrita!\n");
            }
            if (n < 0)
                perror("Erro de leitura!\n");  
        }      

        return 1;
    }
    else if (strcmp(args[0],"bits") == 0) {
        if (numargs == 4) {
            add_history(args, numargs);
            bits(args[1], args[2], args[3]);
        }
        else
            perror("Número de argumentos inválidos\n");
        return 1;
    }
    else if (strcmp(args[0], "alarm") == 0) {
        pthread_t t;

        if (numargs == 3) {
            add_history(args, numargs);
            data *tmp = (data *) malloc(sizeof(data));
            tmp->temp = atoi(args[1]);
            strcpy(tmp->msg, args[2]);
            pthread_create(&t, NULL, f, tmp);
        }
        else
            perror("Número de argumentos inválidos\n");        
        return 1;
    }
    else if (strcmp(args[0], "socpth") == 0) {
        pthread_t th;

        if (numargs == 4) {
            arg_t *arguments = (arg_t *) malloc(sizeof(arg_t));

            if (arguments == NULL) return 1;

            add_history(args, numargs);

            strcpy(arguments->fonte, args[1]);
            strcpy(arguments->destino, args[2]);
            arguments->blockSize = atoi(args[3]);
            
            pthread_create(&th, NULL, socpth, (void *)arguments);
        }
        else
            perror("Número de argumentos inválidos\n");        

        return 1;
    }
    else if (strcmp(args[0], "myls") == 0) {        
        DIR *dp;
        struct dirent *dirp;
        
        if (numargs != 2) 
            perror("Número de argumentos inválidos\n");
        else {
            if ((dp = opendir(args[1])) == NULL)
                fprintf(stderr, "Can’t open %s\n", args[1]);
            else {
                add_history(args, numargs);
                while ((dirp = readdir(dp)) != NULL)
                    printf("%s\n", dirp->d_name);
                closedir(dp);
            }
        }

        return 1;
    }
    else if (strcmp(args[0], "fx") == 0) {
        add_history(args, numargs);
        fx(args);
        return 1;
    }
    else if (strcmp(args[0], "fnox") == 0) {
        add_history(args, numargs);
        fnox(args);
        return 1;
    }

    //devolver 0 indique que não há comnando embutido

    return 0;
}
