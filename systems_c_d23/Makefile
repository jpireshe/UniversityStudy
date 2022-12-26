all: d23

d23: libdinos.o d23.o libgeodist.o
	gcc d23.o libdinos.o libgeodist.o -o d23 -lm

libdinos.o: libdinos.c libdinos.h
	gcc -Wall -fPIC -shared -lm libdinos.c -o libdinos.o

libgeodist.o: libgeodist.c libgeodist.h
	gcc -Wall -fPIC -shared -lm libgeodist.c -o libgeodist.o

d23.o: d23.c libdinos.h libgeodist.h
	gcc -Wall -fPIC -shared d23.c -o d23.o -lm

clean:
	rm -f *.o
	rm -f d23

exec:
	LD_LIBRARY_PATH=. ./d23