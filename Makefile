
CC = gcc
CFLAGS = -Wall -g
TARGET = newshell
OBJS = newshell.o builtins.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

newshell.o: newshell.c builtins.h
	$(CC) $(CFLAGS) -c newshell.c

builtins.o: builtins.c builtins.h
	$(CC) $(CFLAGS) -c builtins.c

clean:
	rm -f *.o $(TARGET)



