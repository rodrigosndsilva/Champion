CC=gcc
CFLAGS=-c -Wall
LDFLAGS=-pthread -Wall -Wextra
SOURCES=main.c functions.c commands.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=../../build/player

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@