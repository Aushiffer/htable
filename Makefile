CC = gcc
CFLAGS = -g -lm -Wall -Wextra -pedantic -Werror
PROGRAM = htable

all: $(PROGRAM)

$(PROGRAM): hash_table.o prime.o main.o
	$(CC) -o $(PROGRAM) $^ $(CFLAGS)

main.o: main.c
	$(CC) -c $^ $(CFLAGS)

prime.o: prime.h prime.c
	$(CC) -c $^ $(CFLAGS)

hash_table.o: hash_table.h hash_table.c
	$(CC) -c $^ $(CFLAGS)

clean:
	rm -f *.o *.gch $(PROGRAM)