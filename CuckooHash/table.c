/* 
   Source file : 'table.c'
   Escrito por : Allan Cedric G. B. Alves da Silva
   Profile : Aluno de graduação do curso de Ciência da Computação (UFPR)
   GRR : 20190351
*/

#include "table.h"

int hash_1(int key)
{
    return key % MAX_SIZE_HASH_TABLE;
}

int hash_2(int key)
{
    return (int)floor(MAX_SIZE_HASH_TABLE * (key * 0.9 - floor(key * 0.9)));
}

index_t *newTable(int size, char *id)
{
    index_t *table = (index_t *)malloc(sizeof(index_t) * size);
    if (!table)
    {
        perror("Memory allocation error! - 'newTable()'");
        exit(1);
    }
    while (size--)
    {
        table[size].data = NULL;
        table[size].state = 'E';
        table[size].tableId = id;
    }
    return table;
}

void initCuckooHash(CUCKOO_HASH *ch)
{
    ch->size_1 = MAX_SIZE_HASH_TABLE;
    ch->size_2 = ch->size_1;

    ch->table_1 = newTable(ch->size_1, "T1");
    ch->table_2 = newTable(ch->size_2, "T2");
}

index_t *destroyTable(index_t *table, int size)
{
    while (size--)
    {
        free(table[size].data);
        table[size].data = NULL;
    }
    free(table);
    table = NULL;
    return table;
}

void destroyCuckooHash(CUCKOO_HASH *ch)
{
    if (ch->table_1)
        ch->table_1 = destroyTable(ch->table_1, ch->size_1);
    if (ch->table_2)
        ch->table_2 = destroyTable(ch->table_2, ch->size_2);
}

data_t *newKey(int key, int hash)
{
    data_t *newData = (data_t *)malloc(sizeof(data_t));
    if (!newData)
    {
        perror("Memory allocation error! - 'newKey()'");
        exit(1);
    }
    newData->key = key;
    newData->hash = hash;
    return newData;
}

void insertCuckooHash(CUCKOO_HASH *ch, int key)
{
    int index = hash_1(key);
    if (ch->table_1[index].data)
    {
        int currentKey = ch->table_1[index].data->key;

        /* Não aceita chaves duplicadas */
        if (currentKey == key)
            return;

        int newIndex = hash_2(currentKey);

        free(ch->table_1[index].data);
        ch->table_1[index].data = NULL;

        /* Não há colisão na segunda tabela Hash */
        ch->table_2[newIndex].data = newKey(currentKey, newIndex);
        ch->table_2[newIndex].state = 'F';
    }
    ch->table_1[index].data = newKey(key, index);
    ch->table_1[index].state = 'F';
}

index_t *searchCuckooHash(CUCKOO_HASH *ch, int key)
{
    int index = hash_1(key);
    if (ch->table_1[index].state == 'E')
        return NULL;
    else if (ch->table_1[index].state == 'F' && ch->table_1[index].data->key == key)
        return &(ch->table_1[index]);
    else
    {
        index = hash_2(key);
        if (ch->table_2[index].data && ch->table_2[index].data->key == key)
            return &(ch->table_2[index]);
        return NULL;
    }
}

void removeCuckooHash(CUCKOO_HASH *ch, int key)
{
    index_t *keyToRemove = searchCuckooHash(ch, key);
    if (keyToRemove)
    {
        free(keyToRemove->data);
        keyToRemove->data = NULL;
        keyToRemove->state = 'R';
    }
}
