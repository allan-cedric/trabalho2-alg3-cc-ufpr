/*
   ===
   Source file : 'table.c'
   Escrito por : Allan Cedric G. B. Alves da Silva
   Profile : Aluno de graduação do curso de Ciência da Computação (UFPR)
   GRR : 20190351
   ===
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

hash_table_t *newTable(int size, char *id)
{
    hash_table_t *table = (hash_table_t *)malloc(sizeof(hash_table_t) * size);
    if (!table)
    {
        perror("Memory allocation error!");
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

void initCuckooHash(cuckoo_hash_t *ch, int size)
{
    ch->size_1 = size;
    ch->size_2 = ch->size_1;

    ch->table_1 = newTable(ch->size_1, "T1");
    ch->table_2 = newTable(ch->size_2, "T2");
}

hash_table_t *destroyTable(hash_table_t *table, int size)
{
    while (size--)
    {
        if (table[size].data)
            free(table[size].data);
        table[size].data = NULL;
    }
    free(table);
    table = NULL;
    return table;
}

void destroyCuckooHash(cuckoo_hash_t *ch)
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
        perror("Memory allocation error!");
        exit(1);
    }
    newData->key = key;
    newData->hash = hash;
    return newData;
}

void insertCuckooHash(cuckoo_hash_t *ch, int key)
{
    hash_table_t *existingKey = searchCuckooHash(ch, key);
    if (existingKey)
        return;

    int index = hash_1(key);
    if (ch->table_1[index].data)
    {
        /* === Salva a chave que houve a colisão === */
        int currentKey = ch->table_1[index].data->key;
        int newIndex = hash_2(currentKey);

        /* === Libera a posição para alocar a nova chave === */
        free(ch->table_1[index].data);
        ch->table_1[index].data = NULL;

        /* === Não há colisão na segunda tabela Hash === */
        ch->table_2[newIndex].data = newKey(currentKey, newIndex);
        ch->table_2[newIndex].state = 'F';
    }
    ch->table_1[index].data = newKey(key, index);
    ch->table_1[index].state = 'F';
}

hash_table_t *searchCuckooHash(cuckoo_hash_t *ch, int key)
{
    int index = hash_1(key);
    if (ch->table_1[index].state == 'E')
        return NULL;
    else if (ch->table_1[index].data && ch->table_1[index].data->key == key)
        return &(ch->table_1[index]);
    else
    {
        index = hash_2(key);
        if (ch->table_2[index].data && ch->table_2[index].data->key == key)
            return &(ch->table_2[index]);
        return NULL;
    }
}

void removeCuckooHash(cuckoo_hash_t *ch, int key)
{
    hash_table_t *keyToRemove = searchCuckooHash(ch, key);
    if (keyToRemove)
    {
        free(keyToRemove->data);
        keyToRemove->data = NULL;
        keyToRemove->state = 'R';
    }
}
