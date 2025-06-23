CC=gcc
CFLAGS=-Wall

all: mainmenu

mainmenu: major1.o parity.o rotate.o
	$(CC) $(CFLAGS) -o mainmenu major1.o parity.o rotate.o

major1.o: major1.c major1.h
	$(CC) $(CFLAGS) -c major1.c

parity.o: parity.c major1.h
	$(CC) $(CFLAGS) -c parity.c

rotate.o: rotate.c major1.h
	$(CC) $(CFLAGS) -c rotate.c

clean:
	rm -f *.o mainmenu
