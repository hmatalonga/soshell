#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <ctype.h>
#include <wait.h>
#include <time.h>
#include <sys/dir.h>
#include <errno.h>

typedef struct $
{
	int temp;
	char msg[100];
} data;

typedef struct
{
	char fonte[100], destino[100];
	int blockSize;
} arg_t;

int parse(char *buf, char **args);

void execute(char **args, int numargs);

int builtin (char **args, int numargs);

void bits(char *op1, char *op, char *op2);

void *socpth(void *args);

int proc_redirection(char **args, int numargs);

int fx (char **args);

int fnox (char **args);

/* constantes que podem tornar uteis*/

#define BG 0
#define FG 1

#define BUFFSIZE 512
#define FILE_MODE 0666
