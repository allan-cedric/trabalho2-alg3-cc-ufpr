/*
   ===
   Source file : 'myht.c'
   Escrito por : Allan Cedric G. B. Alves da Silva
   Profile : Aluno de graduação do curso de Ciência da Computação (UFPR)
   GRR : 20190351
   ===
*/

/* === Bibliotecas === */
#include "CuckooHash/table.h"
#include "ArvoreAVL/avl.h"

/* === Aloca os elementos de uma tabela Hash em uma árvore AVL === */
void hashTableToAVL(hash_table_t *table, int sizeTable, AVL **rootAVL);

/* === Imprimi as duas tabelas Hash com auxílio de uma árvore AVL === */
void printCuckooHashTables(cuckoo_hash_t *ch, AVL *rootAVL);

/* === Programa principal === */
int main()
{
    /* === Inicialização das duas tabelas Hash === */
    cuckoo_hash_t cuckooHash;
    initCuckooHash(&cuckooHash, MAX_SIZE_HASH_TABLE);

    /* === Inicialização de uma árvore AVL (Vai servir para o output dos dados das tabelas Hash) === */
    AVL *rootAVL;
    rootAVL = createAVL();

    /* === Inputs nas tabelas Hash === */
    char opInput;
    int keyInput, ret;
    ret = fscanf(stdin, "%c %i", &opInput, &keyInput);
    fgetc(stdin);
    while (ret != EOF)
    {
        if (ret < 2 || (opInput != 'i' && opInput != 'r'))
        {
            perror("Error: Invalid input");
            int i;
            for (i = 0; i < 2 - ret; i++)
                fgetc(stdin);
        }
        else if (opInput == 'i')
            insertCuckooHash(&cuckooHash, keyInput);
        else if (opInput == 'r')
            removeCuckooHash(&cuckooHash, keyInput);

        ret = fscanf(stdin, "%c %i", &opInput, &keyInput);
        fgetc(stdin);
    }

    /* === Realização de um parsing nas tabelas Hash, a fim de imprimí-las a partir de uma árvore AVL === */
    hashTableToAVL(cuckooHash.table_1, cuckooHash.size_1, &rootAVL);
    hashTableToAVL(cuckooHash.table_2, cuckooHash.size_2, &rootAVL);

    /* === Output esperado === */
    printCuckooHashTables(&cuckooHash, rootAVL);

    /* === Destruição das duas tabelas Hash e da árvore AVL === */
    destroyCuckooHash(&cuckooHash);
    rootAVL = destroyAVL(rootAVL);

    return 0;
}

void hashTableToAVL(hash_table_t *table, int sizeTable, AVL **rootAVL)
{
    data_t *data;
    int i;
    for (i = 0; i < sizeTable; i++)
    {
        data = table[i].data;
        if (data)
            *rootAVL = insertNodeAVL(*rootAVL, data->key);
    }
}

void printCuckooHashTables(cuckoo_hash_t *ch, AVL *rootAVL)
{
    if (rootAVL)
    {
        printCuckooHashTables(ch, rootAVL->left);
        hash_table_t *dataToPrint = searchCuckooHash(ch, rootAVL->key);
        fprintf(stdout, "%i,%s,%i\n", dataToPrint->data->key, dataToPrint->tableId, dataToPrint->data->hash);
        printCuckooHashTables(ch, rootAVL->right);
    }
}