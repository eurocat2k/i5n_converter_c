CC=clang
CFLAGS=-g -O2 -I./include -static
OBJS=i5n.o
LOBJS=i5n.o
LIBNAME=libi5n.a

.o.c:
	$(CC) $(CFLAGS) -c -o $@ $^

all: $(OBJS)
	ar rcs $(LIBNAME) $(OBJS)

clean:
	rm -f *.o
	rm -f *.a
