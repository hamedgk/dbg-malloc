compiler=gcc
cflags=-Wall


all: dbgalloc.o dbgalloc.so dbgalloc.a

dbgalloc.o: dbgalloc.c
	$(compiler) -c -fpic $(cflags) $^

dbgalloc.so: dbgalloc.o
	$(compiler) -shared $^ -o lib$@

dbgalloc.a: dbgalloc.o
	ar -rc lib$@ $^

install: dbgalloc.a dbgalloc.so
	install -c libdbgalloc.a /usr/local/lib
	install -c libdbgalloc.so /usr/local/lib
	install -c dbgalloc.h /usr/local/include


clean:
	rm -f *.o *.so *.a
