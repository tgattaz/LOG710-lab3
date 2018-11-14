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
    int data;
  	struct bloc *valeur;
    struct node *p_next;
    struct node *p_prev;
};

struct node *root = NULL;

void initmem(int size_memory){
  struct bloc *bloc = malloc(sizeof(bloc));
	bloc->size = memSize;
	bloc->offset = 0;
	bloc->data = NULL;

	root = malloc(sizeof(node));
	root->value = bloc;
	root->previous = NULL;
	root->next = NULL;

}

int allouem(int size_memory)


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

//chercher adr phys d'un espace memoire de la taille demandé par init mem et on ne touche plus a
int main() {
    printf("Hello, World!\n");
    return 0;
}
