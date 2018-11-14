#include "main.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct bloc {
	int size;
	int offset; //adresse
	int etat;
} bloc;

struct node
{
	struct bloc *valeur;
    struct node *p_next;
    struct node *p_prev;
} node;


struct node* initmem(int size_memory){

  	struct bloc *bloc = malloc(sizeof(bloc));
	bloc->size = size_memory;
	bloc->offset = 0;
	bloc->etat = 0;

	struct node *root = malloc(sizeof(node));
	root->valeur = bloc;
	root->p_prev = NULL;
	root->p_next = NULL;

	return root;
}

int allouem(int size_bloc){
	struct node *nodecourrant = root;
	struct bloc *bloccourant = bloccourant->etat;

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

	struct node* root = initmem(1000);
}
