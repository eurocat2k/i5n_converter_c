CC=clang
ARFLAGS=rcsv
CFLAGS=-g -O2 -I./include -static
SRC=i5n.c
OBJF=i5n.o
LIBNAME=libi5n.a

all: libi5n.a

libi5n.a: i5n.o
	ar rvcs $@ i5n.o
	mkdir -p ../lib
	cp $@ ../lib

i5n.o: i5n.c
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	rm -f *.o
	rm -f *.a
	rm -f *.core
	rm -f ../lib/*

