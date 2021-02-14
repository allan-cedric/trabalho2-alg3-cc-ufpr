/*
   ===
   Header file : 'table.h'
   Escrito por : Allan Cedric G. B. Alves da Silva
   Profile : Aluno de graduação do curso de Ciência da Computação (UFPR)
   GRR : 20190351
   ===
*/

#ifndef __TABLE_H__
#define __TABLE_H__

/* === Bibliotecas === */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* === Macros === */
#define MAX_SIZE_HASH_TABLE 11

/* === Estrutura de uma célula de dados da tabela Hash === */
typedef struct data_t
{
    int key, hash;
} data_t;

/* === Estrutura de indexação (slot) da tabela Hash === */
typedef struct hash_table_t
{
    data_t *data;
    char state, *tableId;
} hash_table_t;

/* === Estrutura que administra duas tabelas Hash === */
typedef struct cuckoo_hash_t
{
    hash_table_t *table_1, *table_2;
    int size_1, size_2;
} cuckoo_hash_t;

/* === Função hash (1) === */
/* Retorna um valor hash, seguindo essa função: h1(k) = k mod m. */
int hash_1(int key);

/* === Função hash (2) === */
/* Retorna um valor hash, seguindo essa função: h2(k) = ⌊m * (k * 0.9 − ⌊k * 0.9⌋)⌋. */
int hash_2(int key);

/* === Cria uma nova tabela Hash === */
/* Retorna um ponteiro para essa nova tabela. */
hash_table_t *newTable(int size, char *id);

/* === Inicializa as duas tabelas Hash com um certo tamanho === */
void initCuckooHash(cuckoo_hash_t *ch, int size);

/* === Destrói uma tabela Hash === */
/* Retorna NULL. */
hash_table_t *destroyTable(hash_table_t *table, int size);

/* === Destrói as duas tabelas Hash === */
void destroyCuckooHash(cuckoo_hash_t *ch);

/* === Cria uma nova célula de dados === */
/* Retorna um ponteiro para essa nova célula de dados. */
data_t *newKey(int key, int hash);

/* === Inserção de uma chave em alguma das duas tabelas Hash === */
void insertCuckooHash(cuckoo_hash_t *ch, int key);

/* === Busca uma certa chave nas tabelas Hash === */
/* Retorna um slot da tabela Hash onde se encontra essa certa chave, senão NULL. */
hash_table_t *searchCuckooHash(cuckoo_hash_t *ch, int key);

/* === Remove uma certa chave que pode estar nas tabelas Hash === */
void removeCuckooHash(cuckoo_hash_t *ch, int key);

#endif