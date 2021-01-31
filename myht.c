#include "CuckooHash/table.h"
#include "ArvoreAVL/avl.h"

/* Função para imprimir as duas tabelas Hash em ordem */
void printCuckooHashTables(CUCKOO_HASH *ch, AVL *rootAVL);

int main()
{
    /* Inicialização das duas tabelas Hash */
    CUCKOO_HASH cuckooHash;
    initCuckooHash(&cuckooHash);

    /* Incialização de uma árvore AVL (Vai servir para o output dos dados das tabelas Hash) */
    AVL *rootAVL;
    rootAVL = createAVL();

    /* Inputs nas tabelas Hash */
    char opInput;
    int keyInput, ret;
    ret = fscanf(stdin, "%c %i", &opInput, &keyInput);
    fgetc(stdin);
    while (ret != EOF)
    {
        if (ret < 2 || (opInput != 'i' && opInput != 'r'))
        {
            perror("Error: Invalid input");
            for (int i = 0; i < 2 - ret; i++)
                fgetc(stdin);
        }
        else if (opInput == 'i')
        {
            insertCuckooHash(&cuckooHash, keyInput);
            rootAVL = insertNodeAVL(rootAVL, keyInput);
        }
        else if (opInput == 'r')
        {
            removeCuckooHash(&cuckooHash, keyInput);
            rootAVL = removeNodeAVL(rootAVL, keyInput);
        }

        ret = fscanf(stdin, "%c %i", &opInput, &keyInput);
        fgetc(stdin);
    }

    /* Output esperado */
    printCuckooHashTables(&cuckooHash, rootAVL);

    /* Destruição das duas tabelas Hash */
    destroyCuckooHash(&cuckooHash);
    rootAVL = destroyAVL(rootAVL);
    return 0;
}

void printCuckooHashTables(CUCKOO_HASH *ch, AVL *rootAVL)
{
    if (rootAVL)
    {
        printCuckooHashTables(ch, rootAVL->left);
        index_t *dataToPrint = searchCuckooHash(ch, rootAVL->key);
        fprintf(stdout, "%i,%s,%i\n", dataToPrint->data->key, dataToPrint->tableId, dataToPrint->data->hash);
        printCuckooHashTables(ch, rootAVL->right);
    }
}