CC=gcc
AR=ar
fPIC=-fPIC
FLAGS=-Wall


all: ex1

		


ex1: Ex1.c 
		$(CC) $(FLAGS) Ex1.c -o ex1


		



.PHONY:  ex1 clean all

clean:
		rm -f *.o *.a *.so example

