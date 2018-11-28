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

    if(prev_node != NULL && prev_node->value->state == 0){
        lib_node->value->address = prev_node->value->address;
        lib_node->value->size += prev_node->value->size;

        lib_node->p_prev = prev_node->p_prev;
        lib_node->p_prev->p_next = lib_node;
        free(prev_node->value);
        free(prev_node);
    }
    if (next_node != NULL && next_node->value->state == 0) {
        lib_node->value->size += next_node->value->size;

        lib_node->p_next = next_node->p_next;
        lib_node->p_next->p_prev = lib_node;
        free(next_node->value);
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
    long phys_addr = memory_root->value->address + pOctet;

    while (p_mem != NULL && !find && p_mem->value->address <= phys_addr) {

        if (p_mem->value->state == 1) {
            if (phys_addr >= p_mem->value->address && phys_addr < (p_mem->value->address + p_mem->value->size)) {
                find = 1;
            }
        }

        p_mem = p_mem->p_next;

    }

    return find;
}


void affiche_etat_memoire(node *memory_root) {
    node *p_mem = memory_root;
    int n_memory_blocks = 0;
    printf("Liste des blocs memoires : \n");

    while (p_mem != NULL) {
        printf("-> Bloc memoire %d : \n", n_memory_blocks);
        printf("Adresse : %lu | ", p_mem->value->address);
        printf(" Etat : %u | ", p_mem->value->state);
        printf(" Taille : %u\n\n", p_mem->value->size);
        n_memory_blocks += 1;

        p_mem = p_mem->p_next;

    }

}

void affiche_parametres_memoire(node *root) {

    printf("Nombre de blocs libres: %u\n", n_bloc_libres(root));
    printf("Nombre de blocs alloués: %u\n", n_bloc_alloues(root));
    printf("Mémoire libre: %u\n", mem_libre(root));
    printf("Taille du plus grand bloc libre: %u \n", mem_pgrand_libre(root));

    int size_small = 10;
    printf("Nombre de blocs libres de taille inférieur à %u: %u \n\n", size_small, mem_small_free(root, size_small));

}

node *first_fit(node *memory_root, int size) {
    node *p_mem = memory_root;

    while (p_mem != NULL) {

        if (p_mem->value->state == 0 && p_mem->value->size >= size) {
            if (p_mem->value->address == memory_root->value->address) {
                memory_root = allou_mem(size, p_mem);
            } else {
                allou_mem(size, p_mem);
            }
            return memory_root;

        }

        p_mem = p_mem->p_next;
    }

    return memory_root;
}

node *best_fit(node *memory_root, int size) {
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
        if (best_node->value->address == memory_root->value->address) {
            memory_root = allou_mem(size, best_node);
        } else {
            allou_mem(size, best_node);
        }
    }

    return memory_root;
}

node *worst_fit(node *memory_root, int size) {

    node *p_mem = memory_root;
    node *worst_node = NULL;
    int max_delta = 0;
    int delta;

    while (p_mem != NULL) {

        if (p_mem->value->state == 0) {

            delta = abs(size - p_mem->value->size);

            if (delta >= max_delta) {
                max_delta = delta;
                worst_node = p_mem;
            }

        }

        p_mem = p_mem->p_next;
    }

    if (worst_node != NULL) {
        if (worst_node->value->address == memory_root->value->address) {
            memory_root = allou_mem(size, worst_node);
        } else {
            allou_mem(size, worst_node);
        }
    }

    return memory_root;

}

node *next_fit(node *memory_root, node *previous_starting_node, int size) {

    node *p_mem = previous_starting_node;

    while (p_mem->p_next != previous_starting_node) {

        if (p_mem->value->state == 0 && p_mem->value->size >= size) {

            if (p_mem->value->address == memory_root->value->address) {
                memory_root = allou_mem(size, p_mem);
            } else {
                allou_mem(size, p_mem);
            }

            return memory_root;

        }

        if (p_mem->p_next == NULL) {
            p_mem = memory_root;
        } else {
            p_mem = p_mem->p_next;
        }
    }

    return memory_root;

}


void free_all(node *memory_root){

    node *p_mem = memory_root;
    node *next_node;

    while(p_mem != NULL){
        next_node = p_mem->p_next;

        free(p_mem->value);
        free(p_mem);

        p_mem = next_node;
    }
}


int main() {

    int continuing = 1;
    int strategie_choice;
    int size_memory;
    int return_remove_add_choice=0;

    printf("1. First-fit  2. Best-fit  3. Worst-fit  4. Next-fit \n");
    printf("Enter the value of the strategie you want to use : ");
    scanf("%d", &strategie_choice);
    if((strategie_choice > 4) || (strategie_choice < 1)){
        printf("please use a valid anwser \n");
        return 0;
    }
    printf("\nEnter the total size memory you need : ");
    scanf("%d", &size_memory);
    if((size_memory > 100000) || (size_memory < 0)){
        printf("please use a valid anwser \n");
        return 0;
    }

    node *root = init_mem(size_memory);

    while(continuing){

        printf("1. Add  2. Remove  -1. Stop \n");
        printf("Enter the value of the choice  you want to use : ");
        scanf("%d", &return_remove_add_choice);

        //STOP
        if(return_remove_add_choice == -1){
            continuing = 0;
        }
        //REMOVE
        else if(return_remove_add_choice == 2){
            printf("Enter the address you want to remove: ");
            //libere_mem(node *lib_node);
        }
        //ADD
        else if(return_remove_add_choice == 1){

            printf("Enter the new memorie size you want to use: ");
            scanf("%d", &size_memory);

            if(mem_pgrand_libre(root) < size_memory){
                printf("There is not a place for the size you ask for %d\n", size_memory);
            }
            else{

        
                if(strategie_choice == 1){
                    root = first_fit(root, size_memory);

                }else if(strategie_choice == 2){
                    root = best_fit(root, size_memory);
                }else if(strategie_choice == 3){
                    root = worst_fit(root, size_memory);
                }else if(strategie_choice == 4){
                    //TODO need to handle the last used node
                    root = next_fit(root, size_memory, root);
                
                }
            }
        }
        affiche_parametres_memoire(root);
        affiche_etat_memoire(root);

    }

    free_all(root);
    return 0;
}
