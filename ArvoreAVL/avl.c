/* 
   Source file : 'avl.c'
   Escrito por : Allan Cedric G.B. Alves da Silva
   Profile : Aluno de graduação do curso de Ciência da Computação (UFPR)
   GRR : 20190351
*/

#include "avl.h"

int emptyAVL(AVL *root)
{
	return (root == NULL);
}

AVL *createAVL()
{
	return NULL;
}

AVL *newNode(int key)
{
	AVL *node = (AVL *)malloc(sizeof(AVL));
	if (!node)
	{
		perror("Not enough memory to create a new node! - 'newNode()'");
		exit(1);
	}
	node->left = NULL;
	node->right = NULL;
	node->parent = NULL;
	node->height = 0;
	node->key = key;
	return node;
}

/* 
	Método de inserção em uma árvore AVL:

	Foi realizado recursivamente, e o princípio
	desse algoritmo é inserir um novo nodo como folha.
*/
AVL *insertNodeAVL(AVL *root, int key)
{
	if (!root)
		return newNode(key);
	if (key < root->key)
	{
		root->left = insertNodeAVL(root->left, key);
		root->left->parent = root; /* Ajusta o pai */
		/* Balanceamento */
		root->height = largest(heightNodeAVL(root->left), heightNodeAVL(root->right)) + 1;
		if (balanceFactorAVL(root) == 2)
		{
			if (key < root->left->key)
				return LLRotationAVL(root);
			return LRRotationAVL(root);
		}
	}
	else if (key > root->key)
	{
		root->right = insertNodeAVL(root->right, key);
		root->right->parent = root; /* Ajusta o pai */
		/* Balanceamento */
		root->height = largest(heightNodeAVL(root->left), heightNodeAVL(root->right)) + 1;
		if (balanceFactorAVL(root) == 2)
		{
			if (key > root->right->key)
				return RRRotationAVL(root);
			return RLRotationAVL(root);
		}
	}
	return root;
}

void printAVL(AVL *root, const char *op)
{
	if (!root)
		return;

	/* PRE-ORDER */
	if (!strcmp(op, "pre"))
	{
		printf("%i ", root->key);
		printAVL(root->left, "pre");
		printAVL(root->right, "pre");
	}
	/* IN-ORDER */
	else if (!strcmp(op, "in"))
	{
		printAVL(root->left, "in");
		printf("%i ", root->key);
		printAVL(root->right, "in");
	}
	/* POS-ORDER */
	else if (!strcmp(op, "pos"))
	{
		printAVL(root->left, "pos");
		printAVL(root->right, "pos");
		printf("%i ", root->key);
	}
	else
		perror("Not a valid argument for 'op' - 'printAVL()'");
}

AVL *destroyAVL(AVL *root)
{
	if (!root)
		return root;

	destroyAVL(root->left);
	destroyAVL(root->right);
	free(root);
	root = NULL;
	return root;
}

AVL *searchAVL(AVL *root, int key)
{
	if (!root || root->key == key)
		return root;

	if (key > root->key)
		return (searchAVL(root->right, key));
	return (searchAVL(root->left, key));
}

AVL *minKeyAVL(AVL *root)
{
	if (!root || !root->left)
		return root;
	return minKeyAVL(root->left);
}

AVL *maxKeyAVL(AVL *root)
{
	if (!root || !root->right)
		return root;
	return maxKeyAVL(root->right);
}

int numNodesAVL(AVL *root)
{
	if (!root)
		return 0;
	return (numNodesAVL(root->left) + numNodesAVL(root->right) + 1);
}

/*
	Método de remoção em uma árvore AVL:

	A implementação desse algoritmo ficou
	muito parecida com o método de inserção.
	A estratégia de deleção de um nodo possui
	o tratamento para 0, 1 ou 2 filhos.
*/
AVL *removeNodeAVL(AVL *root, int key)
{
	if (!root)
		return root;
	if (key < root->key)
	{
		root->left = removeNodeAVL(root->left, key);
		/* Balanceamento */
		root->height = largest(heightNodeAVL(root->left), heightNodeAVL(root->right)) + 1;
		if (balanceFactorAVL(root) == 2)
		{
			if (heightNodeAVL(root->right->left) <= heightNodeAVL(root->right->right))
				return RRRotationAVL(root);
			return RLRotationAVL(root);
		}
	}
	else if (key > root->key)
	{
		root->right = removeNodeAVL(root->right, key);
		/* Balanceamento */
		root->height = largest(heightNodeAVL(root->left), heightNodeAVL(root->right)) + 1;
		if (balanceFactorAVL(root) == 2)
		{
			if (heightNodeAVL(root->left->right) <= heightNodeAVL(root->left->left))
				return LLRotationAVL(root);
			return LRRotationAVL(root);
		}
	}
	else
	{
		/* Remoção de um nodo com 1 ou nenhum filho */
		if (!root->left || !root->right)
		{
			AVL *nodeToRemove = root;
			root = (root->left ? root->left : root->right);
			if (root) /* Ajusta possível pai */
				root->parent = nodeToRemove->parent;
			free(nodeToRemove);
			nodeToRemove = NULL;
		}
		/* Remoção de um nodo com 2 filhos */
		else
		{
#ifdef _SUCESSOR_
			/* 
				Pega o sucessor, copia a chave do sucessor no nodo alvo de remoção 
				e direciona a remoção para o nodo sucessor.
			*/
			AVL *nodeSuccessor = minKeyAVL(root->right);
			root->key = nodeSuccessor->key;
			root->right = removeNodeAVL(root->right, root->key);
			/* Balanceamento */
			root->height = largest(heightNodeAVL(root->left), heightNodeAVL(root->right)) + 1;
			if (balanceFactorAVL(root) == 2)
			{
				if (heightNodeAVL(root->left->right) <= heightNodeAVL(root->left->left))
					return LLRotationAVL(root);
				return LRRotationAVL(root);
			}
#endif
#ifdef _PREDECESSOR_
			/* 
				Pega o antecessor, copia a chave do antecessor no nodo alvo de remoção 
				e direciona a remoção para o nodo antecessor. 
			*/
			AVL *nodePredecessor = maxKeyAVL(root->left);
			root->key = nodePredecessor->key;
			root->left = removeNodeAVL(root->left, root->key);
			/* Balanceamento */
			root->height = largest(heightNodeAVL(root->left), heightNodeAVL(root->right)) + 1;
			if (balanceFactorAVL(root) == 2)
			{
				if (heightNodeAVL(root->right->left) <= heightNodeAVL(root->right->right))
					return RRRotationAVL(root);
				return RLRotationAVL(root);
			}
#endif
		}
	}
	return root;
}

int heightNodeAVL(AVL *node)
{
	if (!node)
		return -1;
	return node->height;
}

int balanceFactorAVL(AVL *node)
{
	return abs(heightNodeAVL(node->left) - heightNodeAVL(node->right));
}

int largest(int x, int y)
{
	return (x > y ? x : y);
}

AVL *LLRotationAVL(AVL *root)
{
	/* Tratamento de novos filhos */
	AVL *node = root->left;
	root->left = node->right;
	node->right = root;

	/* Tratamento de novos pais */
	node->parent = root->parent;
	root->parent = node;
	if (root->left)
		root->left->parent = root;

	/* Reajuste de alturas */
	root->height = largest(heightNodeAVL(root->left), heightNodeAVL(root->right)) + 1;
	node->height = largest(heightNodeAVL(node->left), root->height) + 1;

	/* Retorna a nova raiz dessa árvore rotacionada */
	return node;
}

AVL *RRRotationAVL(AVL *root)
{
	/* Tratamento de novos filhos */
	AVL *node = root->right;
	root->right = node->left;
	node->left = root;

	/* Tratamento de novos pais */
	node->parent = root->parent;
	root->parent = node;
	if (root->right)
		root->right->parent = root;

	/* Reajuste de alturas */
	root->height = largest(heightNodeAVL(root->left), heightNodeAVL(root->right)) + 1;
	node->height = largest(root->height, heightNodeAVL(node->right)) + 1;

	/* Retorna a nova raiz dessa árvore rotacionada */
	return node;
}

AVL *LRRotationAVL(AVL *root)
{
	/* Sistema de rotação dupla: primeiro para a esquerda depois para direita */
	root->left = RRRotationAVL(root->left);
	return LLRotationAVL(root);
}

AVL *RLRotationAVL(AVL *root)
{
	/* Sistema de rotação dupla: primeiro para a direita depois para esquerda */
	root->right = LLRotationAVL(root->right);
	return RRRotationAVL(root);
}
