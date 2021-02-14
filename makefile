CC=gcc
CFLAGS=-ansi -Wall -Wextra -g
LDLIBS=-lm
OBJS=ArvoreAVL/avl.o CuckooHash/table.o myht.o
EXEC=myht

all: myht clean

myht: $(OBJS)

ArvoreAVL/avl.o: ArvoreAVL/avl.h ArvoreAVL/avl.c
CuckooHash/table.o: CuckooHash/table.h CuckooHash/table.c
myht.o: ArvoreAVL/avl.h CuckooHash/table.h myht.c

clean:
	-rm -f $(OBJS) *~

purge: clean
	-rm -f $(EXEC)