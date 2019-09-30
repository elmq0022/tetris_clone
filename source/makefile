TARGET = main
CC = gcc
CFLAGS = -g -Wall -I/usr/include/x86_64-linux-gnu -lallegro_primitives -lallegro


.PHONY: default all clean

default: $(TARGET)
all: default

OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
HEADERS = $(wildcard *.h)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) $(CFLAGS) -o $@
$@

clean:
	-rm -f *.o
	-rm -f $(TARGET)

run:
	./main
