wordchains: wordchains.o Graph.o
	gcc -Wall -Werror -o wordchains wordchains.o Graph.o

wordchains.o: wordchains.c Graph.h
	gcc -Wall -Werror -c wordchains.c

WGraph.o: Graph.c Graph.h
	gcc -Wall -Werror -c Graph.c
