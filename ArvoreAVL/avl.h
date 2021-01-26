/* 
   Header file : 'avl.h'
   Escrito por : Allan Cedric G.B. Alves da Silva
   Profile : Aluno de graduação do curso de Ciência da Computação (UFPR)
   GRR : 20190351
*/

#ifndef AVL_H
#define AVL_H

/*
  Setup para o algoritmo de remoção, pode escolher pelo formato com sucessor ou antecessor
*/

/* Comente essa linha imediatamente abaixo para usar o sucessor, por default está configurado para antecessor */
#define _PREDECESSOR_

#ifndef _PREDECESSOR_
#define _SUCESSOR_
#endif

#ifndef _PREDECESSOR_
#ifndef _SUCESSOR_
#define _PREDECESSOR_
#endif
#endif

/*
  Bibliotecas
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 
  Estrutura de dado de um nodo (p/ AVL) com chave simples => int
*/
typedef struct node_t
{
  struct node_t *left;
  struct node_t *right;
  struct node_t *parent;
  int height;
  int key;
} AVL;

/* Avalia se a AVL está vazia(1) ou não(0) */
int emptyAVL(AVL *root);

/* Cria a AVL */
AVL *createAVL();

/* Cria um novo nodo */
AVL *newNode(int key);

/* Insere um novo nodo */
AVL *insertNodeAVL(AVL *root, int key);

/* Imprime AVL com 3 opções possíveis: "pre", "in" ou "pos" */
void printAVL(AVL *root, const char *op);

/* Destrói a AVL */
AVL *destroyAVL(AVL *root);

/* Busca na AVL. Retorna um ponteiro para o nodo buscado, caso contrário NULL */
AVL *searchAVL(AVL *node, int key);

/* Retorna um ponteiro para o nodo que contém a MENOR chave */
AVL *minKeyAVL(AVL *node);

/* Retorna um ponteiro para o nodo que contém a MAIOR chave */
AVL *maxKeyAVL(AVL *node);

/* Retorna o número de nodos da AVL */
int numNodesAVL(AVL *node);

/* Remove um nodo da AVL */
AVL *removeNodeAVL(AVL *root, int key);

/* Retorna a altura de um certo node */
int heightNodeAVL(AVL *node);

/* Retorna o fator de balanceamento de um certo nodo */
int balanceFactorAVL(AVL *node);

/* Retorna o maior valor entre 2 valores */
int largest(int x, int y);

/* Rotação simples a direita (Caso Esquerda-Esquerda) */
AVL *LLRotationAVL(AVL *root);

/* Rotação simples a esquerda (Caso Direita-Direita) */
AVL *RRRotationAVL(AVL *root);

/* Rotação dupla a direita (Caso Esquerda-Direita) */
AVL *LRRotationAVL(AVL *root);

/* Rotação dupla a esquerda (Caso Direita-Esquerda) */
AVL *RLRotationAVL(AVL *root);

#endif
