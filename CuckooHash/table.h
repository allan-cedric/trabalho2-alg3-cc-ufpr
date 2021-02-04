/* 
   Header file : 'table.h'
   Escrito por : Allan Cedric G. B. Alves da Silva
   Profile : Aluno de graduação do curso de Ciência da Computação (UFPR)
   GRR : 20190351
*/

#ifndef TABLE_H
#define TABLE_H

/* Bibliotecas */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Macros */
#define MAX_SIZE_HASH_TABLE 11

/* Estrutura de uma célula de dados da tabela Hash. */
typedef struct data_t
{
    int key, hash;
} data_t;

/* Estrutura de indexação (slot) da tabela Hash. */
typedef struct index_t
{
    data_t *data;
    char state, *tableId;
} index_t;

/* Estrutura que administra duas tabelas Hash. */
typedef struct cuckooHash_t
{
    index_t *table_1, *table_2;
    int size_1, size_2;
} CUCKOO_HASH;

/* Função hash (1). */
int hash_1(int key);

/* Função hash (2). */
int hash_2(int key);

/* Cria uma nova tabela Hash. */
index_t *newTable(int size, char *id);

/* Inicializa as duas tabelas Hash com um certo tamanho. */
void initCuckooHash(CUCKOO_HASH *ch, int size);

/* Destrói uma tabela Hash. */
index_t *destroyTable(index_t *table, int size);

/* Destrói as duas tabelas Hash. */
void destroyCuckooHash(CUCKOO_HASH *ch);

/* Cria uma nova célula de dados com uma chave. */
data_t *newKey(int key, int hash);

/* Inserção de uma chave em alguma das duas tabelas Hash. */
void insertCuckooHash(CUCKOO_HASH *ch, int key);

/* 
    Busca uma certa chave nas tabelas Hash. 
    Se encontrar, retorna um slot da tabela Hash onde se encontra essa certa chave, senão NULL. 
*/
index_t *searchCuckooHash(CUCKOO_HASH *ch, int key);

/* Remove uma certa chave que pode estar nas tabelas Hash */
void removeCuckooHash(CUCKOO_HASH *ch, int key);

#endif