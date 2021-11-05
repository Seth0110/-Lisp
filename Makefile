CC=gcc
CFLAGS=-std=c99 -Wall -Werror $(INCS) $(LIBS)
DEPS=ulisp.h
INCS=`pkg-config --cflags libedit`
LIBS=`pkg-config --libs libedit` -lm
OBJ=ulisp.o repl.o
PREFIX=/usr/local

ulisp: repl.o ulisp.o
	$(CC) -o $@ $^ $(CFLAGS) -O2

debug: repl.o ulisp.o
	$(CC) -o ulisp $^ $(CFLAGS) -g

install: ulisp
	cp ulisp $(PREFIX)/bin

uninstall:
	rm $(PREFIX)/bin/ulisp

clean:
	rm -f ulisp *.o
