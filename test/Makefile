CC	:= clang
CFLAGS	:= -g -Wall -Wextra -I../src/include -mcpu=x86-64
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
