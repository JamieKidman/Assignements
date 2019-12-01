CC=gcc
CFLAGS=-I. -lpthread -g
DEPS = structs.h queue.h
OBJ = scheduler.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

OS: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)