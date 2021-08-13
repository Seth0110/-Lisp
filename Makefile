CC=gcc
CFLAGS=-I. -lm -ledit -g
DEPS=ulisp.h
OBJ=ulisp.o repl.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

repl: repl.o ulisp.o
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f repl *.o
