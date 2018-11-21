#include "main.h"

node *init_mem(int size_memory) {

    bloc *bloc = malloc(sizeof(bloc));
    bloc->size = size_memory;
    bloc->address = (u_long) malloc((size_t) size_memory);
    bloc->state = 0;

    node *root = malloc(sizeof(node));
    root->value = bloc;
    root->p_prev = NULL;
    root->p_next = NULL;

    return root;
}

// WHY I USED MALLOC :
// You are returning a (pointer to a ) local variable. That can cause (and probably will cause) undefined behaviour,
// because the value will be "gone" once the function ends.
// Either use malloc() to allocate the buffer, or change the function to accept a buffer and just fill it.
node *allou_mem(int new_block_size, node *free_node) {

    node *pNode = NULL;

    if (new_block_size == free_node->value->size) {
        pNode = free_node;
        free_node->value->state = 1;
    } else {
        bloc *new_bloc = malloc(sizeof(bloc));
        new_bloc->size = new_block_size;
        new_bloc->address = free_node->value->address;
        new_bloc->state = 1;

        free_node->value->address += new_block_size;
        free_node->value->size -= new_block_size;

        node *new_node = malloc(sizeof(node));
        pNode = new_node;
        new_node->value = new_bloc;
        new_node->p_prev = free_node->p_prev;
        new_node->p_next = free_node;

        if (free_node->p_prev != NULL) { // What if free_node have a predecessor ?
            free_node->p_prev->p_next = new_node;
        }

        free_node->p_prev = new_node;
    }

    return pNode;
}

node *libere_mem(node *lib_node) {
    
    lib_node->value->state = 0;

    node *prev_node = lib_node->p_prev;
    node *next_node = lib_node->p_next;

    if(prev_node->value->state == 0){
        lib_node->value->address = prev_node->value->address;
        lib_node->value->size += prev_node->value->size;

        lib_node->p_prev = prev_node->p_prev;
        lib_node->p_prev->p_next = lib_node;
        free(prev_node);
    }
    if(next_node->value->state == 0){
        lib_node->value->size += next_node->value->size;

        lib_node->p_next = next_node->p_next;
        lib_node->p_next->p_prev = lib_node;
        free(next_node);
    }

    return lib_node;
}

int n_bloc_libres(node *memory_root) {

    int n_free_block = 0;
    node *p_mem = memory_root;

    while (p_mem != NULL) {

        if (p_mem->value->state == 0) {
            n_free_block += 1;
        }

        p_mem = p_mem->p_next;

    }

    return n_free_block;
}

int n_bloc_alloues(node *memory_root) {

    int n_used_block = 0;
    node *p_mem = memory_root;

    while (p_mem != NULL) {

        if (p_mem->value->state == 1) {
            n_used_block += 1;
        }

        p_mem = p_mem->p_next;

    }

    return n_used_block;
}

int mem_libre(node *memory_root) {

    int free_mem_size = 0;
    node *p_mem = memory_root;

    while (p_mem != NULL) {

        if (p_mem->value->state == 0) {
            free_mem_size += p_mem->value->size;
        }

        p_mem = p_mem->p_next;

    }

    return free_mem_size;
}

// A tester
int mem_pgrand_libre(node *memory_root) {

    int max_free_block_size = 0;
    node *p_mem = memory_root;

    while (p_mem != NULL) {

        if (p_mem->value->state == 0) {
            if (p_mem->value->size > max_free_block_size) {
                max_free_block_size = p_mem->value->size;
            }
        }

        p_mem = p_mem->p_next;

    }

    return max_free_block_size;

}

// A tester
int mem_small_free(node *memory_root, int max_taille_petit) {

    int n_free_blocks_under_size = 0;
    node *p_mem = memory_root;

    while (p_mem != NULL) {

        if (p_mem->value->state == 0) {
            if (p_mem->value->size < max_taille_petit) {
                n_free_blocks_under_size += 1;
            }
        }

        p_mem = p_mem->p_next;

    }

    return n_free_blocks_under_size;
}

// Works but is it pretty enough ?
int mem_est_alloue(node *memory_root, int pOctet) {

    int find = 0;
    node *p_mem = memory_root;

    while (p_mem != NULL && !find && p_mem->value->address <= pOctet) {

        if (p_mem->value->state == 1) {
            if (pOctet >= p_mem->value->address && pOctet < (p_mem->value->address + p_mem->value->size)) {
                find = 1;
            }
        }

        p_mem = p_mem->p_next;

    }

    return find;
}


void affiche_etat_memoire(node *memory_root){
    node *p_mem = memory_root;
     int n_memory_blocks = 0;  
     printf("Liste des blocs memoires : ");

    while (p_mem != NULL) {
        printf("-> Bloc memoire %d : \n", n_memory_blocks);
        printf("Adresse : %lu | ", p_mem->value->address);
        printf(" Etat : %u | ", p_mem->value->state);
        printf(" Taille : %u\n\n", p_mem->value->size);
        n_memory_blocks += 1;

        p_mem = p_mem->p_next;

    }

}

void affiche_parametres_memoire(node *root){

    printf("Nombre de blocs libres: %u\n", n_bloc_libres(root));
    printf("Nombre de blocs alloués: %u\n", n_bloc_alloues(root));
    printf("Mémoire libre: %u\n", mem_libre(root));
    printf("Taille du plus grand bloc libre: %u \n", mem_pgrand_libre(root)); 

    int size_small = 10;
    printf("Nombre de blocs libres de taille inférieur à %u: %u \n", size_small, mem_small_free(root, size_small));

}

int first_fit(node *memory_root, int size) {
    node *p_mem = memory_root;

    while (p_mem != NULL) {

        if (p_mem->value->state == 0 && p_mem->value->size >= size) {
            allou_mem(size, p_mem);
            return 0;
        }

        p_mem = p_mem->p_next;
    }

    return -1;
}

int best_fit(node *memory_root, int size) {
    node *p_mem = memory_root;
    node *best_node = NULL;
    int min_delta = 1000000000;
    int delta;

    while (p_mem != NULL) {

        if (p_mem->value->state == 0) {

            delta = abs(p_mem->value->size - size);

            if (delta <= min_delta) {
                min_delta = delta;
                best_node = p_mem;
            }

        }

        p_mem = p_mem->p_next;
    }

    if (best_node != NULL) {
        allou_mem(size, memory_root);
        return 0;
    }

    return -1;
}

int worst_fit(node *memory_root, int size) {

    node *p_mem = memory_root;
    node *best_node = NULL;
    int max_delta = 0;
    int delta;

    while (p_mem != NULL) {

        if (p_mem->value->state == 0) {

            delta = abs(size - p_mem->value->size);

            if (delta >= max_delta) {
                max_delta = delta;
                best_node = p_mem;
            }

        }

        p_mem = p_mem->p_next;
    }

    if (best_node != NULL) {
        allou_mem(size, memory_root);
        return 0;
    }

    return -1;

}

int next_fit(node *memory_root, int size) {

}

int main() {

    printf("Initialisation de la mémoire :\n\n");
    node *root = init_mem(1000);
    affiche_etat_memoire(root);

    printf("\nAllocation d'un bloc mémoire :\n\n");

    if (worst_fit(root, 300) == 0) {
        affiche_etat_memoire(root->p_prev);
    } else {
        printf("No empty space");
    }

    printf("Octet %u alloué ? %u\n", 26, mem_est_alloue(root->p_prev, 26));

    return 0;
}
