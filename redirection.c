#include "shell.h"

int proc_redirection(char **args, int numargs) {
	int fd;

	if (numargs < 3) return 0;

	//stderr
	if (strcmp(args[numargs-2], "2>") == 0) {
		fd = creat(args[numargs-1], FILE_MODE);
		if (fd < 0) {
			perror("Error");
			return 1;
		}
		dup2(fd, 2);
		close(fd);
		args[numargs-2] = NULL;
		numargs -= 2;		
	}

	if (numargs < 3) return 0;
	
	//stdout
	if (strcmp(args[numargs-2], ">>") == 0) {
		fd = open(args[numargs-1], O_WRONLY | O_APPEND);
		if (fd < 0) fd = creat(args[numargs-1], FILE_MODE);
		if (fd < 0) {
			perror("Error");
			return 1;
		}
		dup2(fd, 1);
		close(fd);
		args[numargs-2] = NULL;
		numargs -= 2;				
	}
	else if (strcmp(args[numargs-2], ">") == 0) {
		fd = creat(args[numargs-1], FILE_MODE);
		if (fd < 0) {
			perror("Error");
			return 1;
		}
		dup2(fd, 1);
		close(fd);
		args[numargs-2] = NULL;
		numargs -= 2;		
	}	

	if (numargs <= 1) return 0;

	//stin
	if (strcmp(args[numargs-2], "<") == 0) {
		fd = open(args[numargs-1], O_RDONLY);
		if (fd < 0) {
			perror("Error");
			return 1;
		}
		dup2(fd, 0);
		close(fd);
		args[numargs-2] = NULL;
		numargs -= 2;			
	}

	return 0;
}