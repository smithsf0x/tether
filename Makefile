TARGET = tether

OBJS = main.o lib/tether/tether.o
CC = gcc

CFLAGS = -Wall
LFLAGS = -lSDL2

all: $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(LFLAGS) -o $(TARGET)

clean:
	rm $(OBJS) $(TARGET)

run:
	./$(TARGET)
