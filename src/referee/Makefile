CC=gcc
CFLAGS=-c -Wall
LDFLAGS=-pthread -Wall -Wextra -g
SOURCES=main.c commands.c functions.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=../../build/referee

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@