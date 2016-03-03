.PHONY: all clean valgrind quickgrind debug

CC=gcc
CFLAGS=-pthread

all: bouncer

bouncer: queue.o bouncer.c
	$(CC) $(CFLAGS) -o bouncer queue.o bouncer.c

queue.o: queue.c
	$(CC) $(CFLAGS) -c queue.c

clean:
	rm -f *.o
	rm -f bouncer


