#include "shell.h"

int fx (char **args) {
    struct stat var;

    if (args[1] == NULL) return 1;

    if ((stat(args[1], &var)) < 0) perror("Error");

    if (!((var.st_mode & S_IFREG) == S_IFREG)) return 1;

    var.st_mode = var.st_mode | S_IXUSR;
    
    chmod(args[1], var.st_mode);

    return 0;
}

int fnox (char **args) {
    struct stat var;

    if (args[1] == NULL) return 1;

    if ((stat(args[1], &var)) < 0) perror("Error");

    if (!((var.st_mode & S_IFREG) == S_IFREG)) return 1;

    var.st_mode = (var.st_mode) & ~(S_IXUSR);
    
    chmod(args[1], var.st_mode);

    return 0;
}