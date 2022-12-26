all: d25

d25: libdinos.so d25.o libgeodist.so
	gcc -Wall -o d25 d25.c -ldinos -lgeodist -lm -L.

libdinos.so: libdinos.c libdinos.h
	gcc -Wall -fPIC -shared -o libdinos.so -lm libdinos.c 
	
libgeodist.so: libgeodist.c libgeodist.h
	gcc -Wall -fPIC -shared -o libgeodist.so -lm libgeodist.c

clean:
	rm -f *.o
	rm -f *.so
	rm -f d25
	rm -f *.bin

exec:
	LD_LIBRARY_PATH=. ./d25






