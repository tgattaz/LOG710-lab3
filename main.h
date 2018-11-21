#include <stdio.h>
#include <stdlib.h>


typedef struct bloc {
    int size;
    u_long address;
    int state;
} bloc;

typedef struct node {
    bloc *value;
    struct node *p_prev;
    struct node *p_next;
} node;


node *init_mem(int size_memory);

node *allou_mem(int size_bloc, struct node *free_node);

node *libere_mem(node *node_to_liberate);

int n_bloc_libres(node *memory_root);

int n_bloc_alloues(node *memory_root);

int mem_libre(node *memory_root);

int mem_pgrand_libre(node *memory_root);

int mem_small_free(node *memory_root, int max_taille_petit);

int mem_est_alloue(node *memory_root, int pOctet);

void affiche_etat_memoire(node *memory_root);

void affiche_parametres_memoire(node *root);

int first_fit(node *memory_root, int size);

int best_fit(node *memory_root, int size);

int worst_fit(node *memory_root, int size);

int next_fit(node *memory_root, int size);
