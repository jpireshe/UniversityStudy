all: d24

d24: libdinos.o d24.o libgeodist.o
	gcc d24.o libdinos.o libgeodist.o -o d24 -lm

libdinos.o: libdinos.c libdinos.h
	gcc -Wall -fPIC -shared -lm libdinos.c -o libdinos.o

libgeodist.o: libgeodist.c libgeodist.h
	gcc -Wall -fPIC -shared -lm libgeodist.c -o libgeodist.o

d24.o: d24.c libdinos.h libgeodist.h
	gcc -Wall -fPIC -shared d24.c -o d24.o -lm

clean:
	rm -f *.o
	rm -f d24

exec:
	LD_LIBRARY_PATH=. ./d24