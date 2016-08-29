TARGET = test

OBJS = test.o widgets.o ../printerr/printerr.o
CC = gcc

CFLAGS = -g -Wall
FLAGS = -L/opt/local/lib -I/opt/local/include
LFLAGS = -lSDL2 -lSDL2_image -lgphoto2

all: $(OBJS)
	export CPATH="/opt/local/include/"
	$(CC) $(FLAGS) $(OBJS) $(CFLAGS) $(LFLAGS) -o $(TARGET)

clean:
	rm $(OBJS)

run:
	./$(TARGET)
	@echo " "
