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

/* Estrutura de uma célula da tabela Hash */
typedef struct cell_t{
    int key;
    char state;
}cell_t;

/* Estrutura de uma tabela Hash */
typedef struct hashTable_t{
    cell_t **table;
    int size; 
}HASH_TABLE;

/* Função hash (1) */
int hash_1(int key, int tableSize);

/* Função hash (2) */
int hash_2(int key, int tableSize);

/* Inicializa uma tabela Hash com um certo tamanho */
void initTable(HASH_TABLE *ht, int tableSize);

#endif