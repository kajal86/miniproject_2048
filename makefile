project: 2048.o Highscore.o 
	cc 2048.o Highscore.o -o project -lncurses
2048.o: 2048.c 
	cc -Wall -c 2048.c
Highscore.o: Highscore.c
	cc -Wall -c Highscore.c
