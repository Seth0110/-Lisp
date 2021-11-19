CC=gcc
CFLAGS=-std=c99 -Wall -Werror $(INCS) $(LIBS) $(DEBUG)
DEBUG=-g
DEPS=ulisp.h
INCS=`pkg-config --cflags libedit`
LIBS=`pkg-config --libs libedit` -lm
OBJ=ulisp.o repl.o
PREFIX=/usr/local
LIB_PREFIX=/usr/share/ulisp

ulisp: repl.o ulisp.o
	$(CC) -o $@ $^ $(CFLAGS) -O2 $(DEBUG)

install: ulisp
	cp ulisp $(PREFIX)/bin
	mkdir -p $(LIB_PREFIX)
	cp ulisp.scm r7rs.scm cxr.scm sicp.scm $(LIB_PREFIX)

uninstall:
	rm $(PREFIX)/bin/ulisp
	rm $(LIB_PREFIX)/*.scm
	rmdir $(LIB_PREFIX)

clean:
	rm -f ulisp *.o
