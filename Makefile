compiler=gcc
cflags=-Wall


all: dbgalloc

dbgalloc.o: dbgalloc.c
	$(compiler) -c -fpic $(cflags) $^

dbgalloc: dbgalloc.o
	$(compiler) -shared $^ -o lib$@.so

clean:
	rm *.o *.so
