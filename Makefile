#vars
CC = g++
CFLAGS = -lm 
CFLAGS += -I/usr/include
LDLIBS = -Llib -lSDL2 -lSDL2main -lSDL2_image

CFILES = src/main.cpp
CTESTFILES = src/test.cpp
OUTFILE = bin/main
all:
	$(CC) $(CFILES) -o $(OUTFILE) $(CFLAGS) $(LDLIBS)

test:
	$(CC) $(CTESTFILES) -o $(OUTFILE) $(CFLAGS) $(LDLIBS)

clean:
	rm bin/main


