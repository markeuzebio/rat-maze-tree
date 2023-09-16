all: main.o arvore.o labirinto.o
	@gcc main.o labirinto.o arvore.o -o exe
	@rm *.o
main.o: main.c
	@gcc -c main.c -Wall
labirinto.o: labirinto.c labirinto.h
	@gcc -c labirinto.c -Wall
arvore.o: arvore.c arvore.h
	@gcc -c arvore.c -Wall
