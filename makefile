CC=gcc
CFLAGS=-ansi -Wall -lm -std=c99
OBJ=avl.o table.o myht.o
EXEC=myht

all: myht clean

myht: $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) $(CFLAGS)

avl.o: ArvoreAVL/avl.h ArvoreAVL/avl.c
	$(CC) -c ArvoreAVL/avl.c $(CFLAGS)

table.o: CuckooHash/table.h CuckooHash/table.c
	$(CC) -c CuckooHash/table.c $(CFLAGS)

myht.o: ArvoreAVL/avl.h ArvoreAVL/avl.c CuckooHash/table.h CuckooHash/table.c
	$(CC) -c myht.c $(CFLAGS)

clean:
	-rm -f $(OBJ) *~

purge: clean
	-rm -f $(EXEC)