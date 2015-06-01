/*
   execute . cria um processo progénito e executa um programa
*/
#include "shell.h"

int ultimo(int numargs, char **args)
{
    if (args[numargs-1][0] == '&') {
        args[numargs-1] = NULL;
        return BG;
    }
    return FG;
}

void execute (char **args, int numargs)
{
    int pid, status;

    int code = ultimo(numargs, args);

    if ((pid = fork ()) < 0)
    {				/* cria um processo progenito */
        perror ("forks");		/* NOTE: perror() produz uma pequema mensagem
        		 * de erro para o stream */
        exit (1);			/* estandardizado de erros que descreve o
        		 * ultimo erro encontrado */
        /* durante uma chamada ao sistema ou funcao duma biblioteca */
    }

    if (pid == 0)
    {
        int i, size;

        int *pipes = proc_pipelines(args, numargs, &size);

        // split pipes

        if (proc_redirection(args, numargs) == 1)
            exit(1);

        execvp (*args, args);	/* NOTE: as versoes execv() e
        		 * execvp() de execl() sao uteis
        		 * quando */
        perror (*args);		/* o numero de argumentos nao e. conhecido.
        		 * Os argumentos de  */
        exit (1);			/* execv() e execvp() sao o nome do ficheiro
        		 * a ser executado e um */
    }				/* vector de strings que contem os
    			 * argumentos. O ultimo argument */

    if (FG == code)
        while (wait (&status) != pid);
    
    return;
}