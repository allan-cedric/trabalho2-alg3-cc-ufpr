CC=gcc
CFLAGS=-ansi -Wall
OBJ=avl.o teste_avl.o
EXEC=teste_avl

all: teste_avl clean

teste_avl: $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) $(CFLAGS)

avl.o: avl.h avl.c
	$(CC) -c avl.c $(CFLAGS)

teste_avl.o: avl.h avl.c
	$(CC) -c teste_avl.c $(CFLAGS)

clean:
	-rm -f $(OBJ) *~

purge: clean
	-rm -f $(EXEC)