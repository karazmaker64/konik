
CC = gcc
CFLAGS = -g
OBJECTS = postscript.o

TARGET = konik

default: $(TARGET)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $*.o

konik: konik.c postscript.h postscript.o
	$(CC) $(CFLAGS) konik.c $(OBJECTS) -lm -o konik

clean:
	rm -f *.o

