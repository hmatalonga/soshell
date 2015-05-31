#include "shell.h"

void bits(char *op1, char *op, char *op2)
{
	int n1 = atoi(op1);
	int n2 = atoi(op2);

	if (n1 == 0 || n2 == 0)
		return;

	if (strcmp(op, "&") == 0)
		fprintf(stdout, "%u\n", n1 & n2);
	else if (strcmp(op, "^") == 0)
		fprintf(stdout, "%u\n", n1 ^ n2);
	else if (strcmp(op, "|") == 0)
		fprintf(stdout, "%u\n", n1 | n2);

	return;
}