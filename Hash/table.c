/* 
   Source file : 'table.c'
   Escrito por : Allan Cedric G. B. Alves da Silva
   Profile : Aluno de graduação do curso de Ciência da Computação (UFPR)
   GRR : 20190351
*/

#include "table.h"

int hash_1(int key, int tableSize)
{
    return key % tableSize;
}

int hash_2(int key, int tableSize)
{
    return (int)floor(tableSize * (key * 0.9 - floor(key * 0.9)));
}

void initTable(HASH_TABLE *ht, int tableSize)
{
    ht->size = tableSize;
    ht->table = (cell_t **)malloc(sizeof(cell_t) * ht->size);
    if (!ht->table)
    {
        perror("Not enough memory to create a hash table! - 'initTable()'");
        exit(1);
    }

    while (tableSize--)
        ht->table[tableSize] = NULL;
}