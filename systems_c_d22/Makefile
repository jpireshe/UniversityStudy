all: d22

d22: libdinos.o d22.o
	gcc d22.o libdinos.o -o d22

libdinos.o: libdinos.c libdinos.h
	gcc -Wall -fPIC -shared libdinos.c -o libdinos.o

d22.o: d22.c libdinos.h
	gcc -Wall -fPIC -shared d22.c -o d22.o 

clean:
	rm -f *.o
	rm -f d22

exec:
	LD_LIBRARY_PATH=. ./d22