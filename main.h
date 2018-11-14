#include <stdio.h>
#include <stdlib.h>

typedef struct bloc {
	int size;
	int adress;
	int state;
} bloc;

struct node
{
	struct bloc* value
    struct node* p_next;
    struct node* p_prev;
} node;


struct node* init_mem(int size_memory);
int allou_mem(int size_bloc, struct node *current_node);
int n_bloc_libres();
int n_bloc_alloues();
int mem_libre();
int mem_pgrand_libre();
int mem_small_free(int max_taille_petit);
int mem_est_alloue(int pOctet);
