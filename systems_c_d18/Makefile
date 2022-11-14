all: d18 liblittlelib.so

d18: d18.c liblittlelib.so
	gcc -Wall -o d18 d18.c -llittlelib -L.

liblittlelib.so: littlelib.c littlelib.h
	gcc -fPIC -shared -o liblittlelib.so littlelib.c

clean:
	rm -f d18
	rm -f liblittlelib.so

exec: d18
	LD_LIBRARY_PATH=. ./d18