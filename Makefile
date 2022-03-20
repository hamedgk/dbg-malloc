compiler=gcc
cflags=-Wall $(cmacros)
prefix ?= /usr/local


all: dbgalloc.o dbgalloc.so dbgalloc.a

dbgalloc.o: dbgalloc.c
	$(compiler) -c -fpic $(cflags) $^

dbgalloc.so: dbgalloc.o
	$(compiler) -shared $^ -o lib$@

dbgalloc.a: dbgalloc.o
	ar -rc lib$@ $^

install: dbgalloc.a dbgalloc.so
	mkdir -p $(prefix)/lib $(prefix)/include
	install -c libdbgalloc.a $(prefix)/lib
	install -c libdbgalloc.so $(prefix)/lib
	install -c dbgalloc.h $(prefix)/include

uninstall:
	rm -fv $(prefix)/lib/libdbgalloc.a $(prefix)/lib/libdbgalloc.so $(prefix)/include/dbgalloc.h


clean:
	rm -fv *.o *.so *.a
