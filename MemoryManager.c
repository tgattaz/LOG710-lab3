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

int main() {

}

void initmem(int size) {
  struct bloc *bloc = malloc(sizeof(bloc));
	bloc->size = memSize;
	bloc->offset = 0;
	bloc->data = NULL;

	root = malloc(sizeof(node));
	root->value = bloc;
	root->previous = NULL;
	root->next = NULL;
}
