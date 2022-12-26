all: d27

d27: libdinos.so d27.o libgeodist.so
	gcc -Wall -o d27 d27.c -ldinos -lgeodist -lm -L. -lpthread

libdinos.so: libdinos.c libdinos.h
	gcc -Wall -fPIC -shared -o libdinos.so -lm libdinos.c 
	
libgeodist.so: libgeodist.c libgeodist.h
	gcc -Wall -fPIC -shared -o libgeodist.so -lm libgeodist.c

clean:
	rm -f *.o
	rm -f *.so
	rm -f d27
	rm -f *.bin

exec:
	LD_LIBRARY_PATH=. ./d27







