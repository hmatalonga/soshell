#include "shell.h"

void lowlevelcopy(int in, int out, int blockSize) {
	char buf[blockSize];
	int n;

	while ((n = read(in, buf, blockSize)) > 0)
		write(out, buf, n);
}

void *socpth(void *args) {
	arg_t *agt = (arg_t *)args;

	int fdin = open(agt->fonte, O_RDONLY);
	
	if (fdin < 0) {
		perror("Error opening the file...\n");
		return NULL;
	}

	int fdout = creat(agt->destino, FILE_MODE);

	// start timer
	clock_t start = clock(), diff;
	lowlevelcopy(fdin, fdout, agt->blockSize);
	diff = clock() - start;
	// stop

	int sec = diff * 1000 / CLOCKS_PER_SEC / 1000;

	printf("file %s copied to %s in time %d seconds\n", agt->fonte, agt->destino, sec);

	//free memory
	free(args);

	return NULL;
}