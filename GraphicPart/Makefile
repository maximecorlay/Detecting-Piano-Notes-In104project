CC = gcc

all: sdl.x

process.o : process.c
	$(CC) -c process.c -o process.o -lm -lgsl

sdl.o : sdl_new.c
	$(CC) -c sdl_new.c $(sdl2-config --cflags --libs) -o sdl.o

sdl.x : sdl.o process.o
	$(CC) -o sdl.x sdl.o process.o -lSDL2 -lm -lgsl
	
clean :
	rm -f process.o sdl.o

realclean : 
	rm -f sdl.x

