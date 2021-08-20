CC=gcc
CFLAGS=-std=c99 -Wall -Werror $(INCS) $(LIBS) -g
DEPS=ulisp.h
INCS=`pkg-config --cflags libedit`
LIBS=`pkg-config --libs libedit`
OBJ=ulisp.o repl.o
PREFIX=/usr/local

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

ulisp: repl.o ulisp.o
	$(CC) -o $@ $^ $(CFLAGS)

install: ulisp
	cp ulisp $(PREFIX)/bin

uninstall:
	rm $(PREFIX)/bin/ulisp

clean:
	rm -f ulisp *.o
