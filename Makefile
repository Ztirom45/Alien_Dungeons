# Declare compiler tools and flags
CC      = g++
CFLAGS += -I/usr/include -I./src
LDLIBS  = -lGL -lSDL2 -ldl -lSDL2_image


# Build the main executable
all:
	$(CC)  -o main src/main.cpp ./src/glad.c $(CFLAGS) $(LDLIBS)


# Helper target that cleans up build artifacts
clean:
	rm main
