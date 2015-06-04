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
#include <ncurses.h>


/* constantes que podem tornar uteis*/ 
  
#define BG 0
#define FG 1
  
#define BUFF_SIZE 512
#define STRING_SIZE 100
#define FILE_MODE 0666
#define HIST_FILE ".soshell_history"
#define HIST_SIZE 100


typedef struct $ 
{
    int temp;
    char msg[STRING_SIZE];
} data;
 
typedef struct 
{  
    char fonte[STRING_SIZE];
    char destino[STRING_SIZE];
    int blockSize;
} arg_t;


int parse (char *buf, char **args);

void execute (char **args, int numargs);

int builtin (char **args, int numargs);

void bits (char *op1, char *op, char *op2);

void *socpth (void *args);

int fx (char **args);

int fnox (char **args);

int proc_redirection (char **args, int numargs);

int *proc_pipelines(char **args, int numargs, int *size);

void add_history(char **args, int numargs);

char *get_history(char *args);