# Declare compiler tools and flags
CC		= g++
WFLAGS	= -Wall -Wextra -Wzero-as-null-pointer-constant
CFLAGS	= -I/usr/include -I./src
LDLIBS	= -lGL -lSDL2 -ldl -lSDL2_image

# Build the main executable
all:
	$(CC) -g -o main src/main.cpp ./src/glad.c $(CFLAGS) $(LDLIBS) $(WFLAGS)


# Helper target that cleans up build artifacts
clean:
	rm main
