/* 
   Source file : 'teste_avl.c'
   Escrito por : Allan Cedric G.B. Alves da Silva
   Profile : Aluno de graduação do curso de Ciência da Computação (UFPR)
   GRR : 20190351
*/

#include "avl.h"

int main()
{
	/* Inicialização da AVL */
	printf("\nInicializando uma AVL...\n");
	AVL *rootAVL = createAVL();

	/* Criação do nodo raiz e preenchimento da AVL */
	if (emptyAVL(rootAVL))
	{
		printf("\nAVL está vazia!\n");
		rootAVL = insertNodeAVL(rootAVL, 1);
		printf("Criando nodo raiz com chave 1...\n");
		printf("Nodo raiz criado com sucesso!\n\n");

		printf("Inserindo nodo com chave 9...\n");
		rootAVL = insertNodeAVL(rootAVL, 9);
		printf("Inserindo nodo com chave 10...\n");
		rootAVL = insertNodeAVL(rootAVL, 10);
		printf("Inserindo nodo com chave 11...\n");
		rootAVL = insertNodeAVL(rootAVL, 11);
		printf("Inserindo nodo com chave 12...\n");
		rootAVL = insertNodeAVL(rootAVL, 12);
		printf("Inserindo nodo com chave 13...\n");
		rootAVL = insertNodeAVL(rootAVL, 13);
	}

	/* Impressão da AVL em cada formato */
	printf("\nImprimindo AVL...\n");
	printf("preOrder: ");
	printAVL(rootAVL, "pre");

	printf("\ninOrder: ");
	printAVL(rootAVL, "in");

	printf("\nposOrder: ");
	printAVL(rootAVL, "pos");

	/* Número de nodos da AVL e sua altura*/
	printf("\n\nNúmero de nodos da AVL: %i\n", numNodesAVL(rootAVL));
	printf("Altura da AVL: %i", heightNodeAVL(rootAVL));

	/* Elementos extremos: máximo e mínimo */
	AVL *genericNodeAVL;
	genericNodeAVL = maxKeyAVL(rootAVL);
	printf("\n\nMaior chave: %i", genericNodeAVL->key);
	genericNodeAVL = minKeyAVL(rootAVL);
	printf("\nMenor chave: %i\n", genericNodeAVL->key);

	/* Teste de busca de elementos na AVL */
	printf("\nBuscando a chave 4...\n");
	genericNodeAVL = searchAVL(rootAVL, 4);
	if (genericNodeAVL)
		printf("Chave ENCONTRADA: %i\n", genericNodeAVL->key);
	else
		printf("Chave NÃO encontrada\n");

	printf("\nBuscando a chave 12...\n");
	genericNodeAVL = searchAVL(rootAVL, 12);
	if (genericNodeAVL)
		printf("Chave ENCONTRADA: %i\n", genericNodeAVL->key);
	else
		printf("Chave NÃO encontrada\n");

	printf("\n\nRemovendo a chave 12...");
	rootAVL = removeNodeAVL(rootAVL, 12);
	printf("\npreOrder: ");
	printAVL(rootAVL, "pre");

	printf("\ninOrder: ");
	printAVL(rootAVL, "in");

	printf("\nposOrder: ");
	printAVL(rootAVL, "pos");

	printf("\n\nRemovendo a chave 13...");
	rootAVL = removeNodeAVL(rootAVL, 13);
	printf("\npreOrder: ");
	printAVL(rootAVL, "pre");

	printf("\ninOrder: ");
	printAVL(rootAVL, "in");

	printf("\nposOrder: ");
	printAVL(rootAVL, "pos");

	genericNodeAVL = NULL;

	/* Desalocação de memória da AVL */
	printf("\n\nDestruindo AVL...\n");
	rootAVL = destroyAVL(rootAVL);
	if (emptyAVL(rootAVL))
		printf("AVL destruída com sucesso\n\n");
	else
	{
		perror("AVL NÃO foi destruída com sucesso");
		exit(1);
	}

	return 0;
}
