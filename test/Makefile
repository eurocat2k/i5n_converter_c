CC	:= clang
CFLAGS	:= -g -Wall -Wextra -I../src/include
SRC1	:= test.c
OBJ1	:= test.o
BIN1	:= i5n
SRC2	:= indexof.c
OBJ2	:= indexof.o
BIN2	:= index
LIBS	:= ../lib/libi5n.a


all: i5n index

i5n: test.o
	$(CC) $(LIBS) test.o -o $@

index: indexof.o
	$(CC) $(LIBS) indexof.o -o $@

test.o:	test.c
	$(CC) $(CFLAGS) -c -o $@ $<

indexof.o: indexof.c
	$(CC) $(CFLAGS) -c -o $@ $<

test.c:
	touch $@

indexof.c:
	touch $@

clean:
	rm -f *.o
	rm -f i5n
	rm -f index
	rm -f *core
