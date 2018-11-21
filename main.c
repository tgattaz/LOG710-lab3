#include "main.h"

node *init_mem(int size_memory) {

    bloc *bloc = malloc(sizeof(bloc));
    bloc->size = size_memory;
    bloc->address = (int) malloc((size_t) size_memory);
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

int libere_mem() {
    return 0;
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

    int n_free_blocks_under_size = 1000000; // Maybe change this to const, var or DEFINE
    node *p_mem = memory_root;

    while (p_mem != NULL) {

        if (p_mem->value->state == 0) {
            if (p_mem->value->size < max_taille_petit) {
                n_free_blocks_under_size = p_mem->value->size;
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


void affiche_etat_memoire(){



}

void affiche_parametres_memoire(){


}
int main() {
    printf("Initialisation de la mémoire :\n\n");
    node *root = init_mem(1000);

    printf("Nombre de bloc(s) : %u\n", n_bloc_alloues(root) + n_bloc_libres(root));
    printf("Memoire libre : %u\n", mem_libre(root));

    printf("Adresse : %u\n", root->value->address);
    printf("Etat : %u\n", root->value->state);
    printf("Taille : %u\n", root->value->size);

    printf("Octet %u alloué ? %u\n", 26, mem_est_alloue(root->p_prev, 26));

    printf("\nAllocation d'un bloc mémoire :\n\n");
    allou_mem(300, root);
    node *new_root = root->p_prev; // TODO : le gestionnaire devra memoriser/mettre a jour la racine a chaque ajout/liberation

    printf("Nombre de bloc(s) : %u\n", n_bloc_alloues(new_root) + n_bloc_libres(new_root));
    printf("Memoire libre : %u\n", mem_libre(new_root));

    printf("Premier bloc :\n");
    printf("Adresse : %u\n", new_root->value->address);
    printf("Etat : %u\n", new_root->value->state);
    printf("Taille : %u\n", new_root->value->size);
    printf("Seconds bloc :\n");
    printf("Adresse : %u\n", new_root->p_next->value->address);
    printf("Etat : %u\n", new_root->p_next->value->state);
    printf("Taille : %u\n", new_root->p_next->value->size);

    printf("Octet %u alloué ? %u\n", 26, mem_est_alloue(root->p_prev, 26));

    return 0;
}
