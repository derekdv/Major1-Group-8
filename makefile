CC=gcc
CFLAGS=-Wall

all: bitwisemenu

bitwisemenu: major1.o parity.o
	$(CC) $(CFLAGS) -o bitwisemenu major1.o parity.o

major1.o: major1.c major1.h
	$(CC) $(CFLAGS) -c major1.c

parity.o: parity.c major1.h
	$(CC) $(CFLAGS) -c parity.c

clean:
	rm -f *.o bitwisemenu
