#include "main.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct bloc {
	int size;
	int offset; //adresse
	void *data;
} bloc;

struct node
{
	struct bloc *valeur;
    struct node *p_next;
    struct node *p_prev;
} node;

struct node *root = NULL;

void initmem(int size_memory){
  struct bloc *bloc = malloc(sizeof(bloc));
	bloc->size = size_memory;
	bloc->offset = 0;
	bloc->data = NULL;

	root = malloc(sizeof(node));
	root->valeur = bloc;
	root->p_prev = root;
	root->p_next = root;

}

int allouem(int size_memory){



	return 0;
}

int nbloclibres(){

	return 0;
}

int nblocalloues(){


	return 0;
}


int memlibre(){


	return 0;
}


int mem_pgrand_libre(){


	return 0;

}

int mem_small_free(int max_taille_petit){

	return 0;
}


int mem_est_alloue(int pOctet){

	return 0;
}

int main() {
    printf("Hello, World!\n");
    return 0;
}