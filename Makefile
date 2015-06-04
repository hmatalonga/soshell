#A Simple Example Makefile for soshell
# 
# Alvo: Dependencias
# tab Action 1
# tab Action 2
#
#Variaveis: Compiler, compiler flags, libraries to link, name of of object files
#
CC=gcc
FLAGS=-c -Wall
LIBS=-lm -lpthread -lncurses
OBS=main.o execute.o parse.o bits.o socpth.o ls.o fx.o redirection.o pipelines.o history.o stack.o
 
#Alvo por defeito é o primeiro 
all : soshell
 
main.o : shell.h main.c
	$(CC) $(FLAGS) main.c
execute.o : shell.h execute.c
	$(CC) $(FLAGS) execute.c
parse.o : shell.h parse.c
	$(CC) $(FLAGS) parse.c
bits.o : shell.h bits.c
	$(CC) $(FLAGS) bits.c
socpth.o : shell.h socpth.c
	$(CC) $(FLAGS) socpth.c	
ls.o : shell.h ls.c
	$(CC) $(FLAGS) ls.c
fx.o : shell.h fx.c
	$(CC) $(FLAGS) fx.c
redirection.o : shell.h redirection.c
	$(CC) $(FLAGS) redirection.c
pipelines.o : shell.h pipelines.c
	$(CC) $(FLAGS) pipelines.c
history.o : shell.h history.c
	$(CC) $(FLAGS) history.c
stack.o : shell.h stack.c
	$(CC) $(FLAGS) stack.c
soshell : $(OBS)
	$(CC) -o soshell $(OBS) $(LIBS)
clean limpar:
	rm -f soshell *.o
