CC=gcc
CFLAGS=-I. -lm -ledit -g
DEPS=lisp.h
OBJ=lisp.o repl.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

repl: repl.o lisp.o
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f repl *.o
