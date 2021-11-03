CC=gcc
AR=ar
fPIC=-fPIC
FLAGS=-Wall


all: slast

		


slast: slast.c 
		$(CC) $(FLAGS) slast.c -g -o slast


		



.PHONY:  slast all clean

clean:
		rm -f *.o *.a *.so slast

