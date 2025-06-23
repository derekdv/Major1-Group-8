CC=gcc
CFLAGS=-Wall

all: mainmenu

mainmenu: major1.o clz.o rotate.o parity.o
	$(CC) $(CFLAGS) -o mainmenu major1.o clz.o rotate.o parity.o

major1.o: major1.c major1.h
	$(CC) $(CFLAGS) -c major1.c

clz.o: clz.c major1.h
	$(CC) $(CFLAGS) -c clz.c

rotate.o: rotate.c major1.h
	$(CC) $(CFLAGS) -c rotate.c

parity.o: parity.c major1.h
	$(CC) $(CFLAGS) -c parity.c

clean:
	rm -f *.o mainmenu
