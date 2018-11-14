#include <stdio.h>

struct node* initmem(int size_memory);
int allouem(int size_memory);
int nbloclibres();
int nblocalloues();
int memlibre();
int mem_pgrand_libre();
int mem_small_free(int max_taille_petit);
int mem_est_alloue(int pOctet);
