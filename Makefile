compiler=gcc
cflags=-Wall $(cmacros)
prefix ?= /usr/local


all: dbgalloc.o dbgalloc.so dbgalloc.a

dbgalloc.o: dbgalloc.c dbg_list.c
	$(compiler) -c -fpic $(cflags) $^

dbgalloc.so: dbgalloc.o dbg_list.o
	$(compiler) -shared $^ -o lib$@

dbgalloc.a: dbgalloc.o dbg_list.o
	ar -rc lib$@ $^

install: dbgalloc.a dbgalloc.so
	mkdir -p $(prefix)/lib $(prefix)/include
	install -c libdbgalloc.a $(prefix)/lib
	install -c libdbgalloc.so $(prefix)/lib
	install -c dbgalloc.h dbg_list.h $(prefix)/include

uninstall:
	rm -fv $(prefix)/lib/libdbgalloc.a $(prefix)/lib/libdbgalloc.so $(prefix)/include/dbgalloc.h $(prefix)/include/dbg_list.h 


clean:
	rm -fv *.o *.so *.a
