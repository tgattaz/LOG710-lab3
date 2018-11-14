#include "main.h"

struct node* init_mem(int size_memory){

  	struct bloc *bloc = malloc(sizeof(bloc));
	bloc->size = size_memory;
	bloc->adress = 0;
	bloc->state = 0;

	struct node *root = malloc(sizeof(node));
	root->value = bloc;
	root->p_prev = NULL;
	root->p_next = NULL;

	return root;
}

int allou_mem(int size_bloc, struct node *current_node){

	if(size_bloc == current_node->value->size){
		current_node->value->state = 1;	
	}
	else{
			struct node *new_node;

			struct bloc *new_bloc = NULL;
			new_bloc->size = size_bloc;
			new_bloc->state =1;
			new_bloc->adress = current_node->value->adress;

			current_node->value->adress = current_node->valeur->adress + size_bloc;

			current_node->p_prev->p_next = new_node;
			
			new_node->p_prev = current_node->p_prev; 
			new_node->p_next = current_node;
			new_node->value = nouveau_bloc;

			current_node->p_prev = new_node;
	}


	return 0;
}

int n_bloc_libres(){

	return 0;
}

int n_bloc_alloues(){


	return 0;
}


int mem_libre(){


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

	//struct node* root = init_mem(1000);
}
