CC=gcc
CFLAGS=-I. -lm -g
DEPS=lisp.h
OBJ=main.o lisp.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f main *.o
