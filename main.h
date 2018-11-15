#include <stdio.h>
#include <stdlib.h>


typedef struct bloc {
	int size;
	int address;
	int state;
} bloc;

typedef struct node {
	bloc* value;
    struct node* p_prev;
    struct node* p_next;
} node;


node* init_mem(int size_memory);
node* allou_mem(int size_bloc, struct node *free_node);
int n_bloc_libres(node* memory_root);
int n_bloc_alloues(node* memory_root);
int mem_libre(node* memory_root);
int mem_pgrand_libre(node* memory_root);
int mem_small_free(node* memory_root, int max_taille_petit);
int mem_est_alloue(node* memory_root, int pOctet);
