NAME=i5n
NAME1=indexOf
CC=clang
OBJS=test.o
OBJS1=indexOf.o
CFLAGS=-g -O2 -Wall -Wextra -I../src/include
LIBS= -L../src -li5n

all: $(NAME) $(NAME1)
	touch *.c

.o.c:
	$(CC) $(CFLAGS) -c $@ $^

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS) # -L../src -li5n
	mv $(NAME) $(NAME).exe

$(NAME1): $(OBJS1)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS) # -L../src -li5n
	mv $(NAME1) $(NAME1).exe

clean:
	rm -f *.O *.exe
	#cd ../src && make clean
