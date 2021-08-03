CC=gcc
CFLAGS=-I. -lm -ledit -g
DEPS=lisp.h
OBJ=test.o lisp.o repl.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

repl: repl.o lisp.o
	$(CC) -o $@ $^ $(CFLAGS)

test: test.o lisp.o
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f test repl *.o
