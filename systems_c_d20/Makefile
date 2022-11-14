all: d20

d20: libdinos.o d20.o
	gcc d20.o libdinos.o -o d20

libdinos.o: libdinos.c libdinos.h
	gcc -Wall -fPIC -shared libdinos.c -o libdinos.o

d20.o: d20.c libdinos.h
	gcc -Wall -fPIC -shared d20.c -o d20.o 

clean:
	rm -f *.o
	rm -f d20

exec:
	LD_LIBRARY_PATH=. ./d20