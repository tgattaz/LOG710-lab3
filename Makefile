gestionnaire: mem_handler.o main.o
	gcc -o gestionnaire mem_handler.o main.o

mem_handler.o: mem_handler.c
	gcc -o mem_handler.o -c mem_handler.c -W

main.o: main.c mem_handler.h
	gcc -o main.o -c main.c -W 
