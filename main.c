#include "mem_handler.h"
#include <stdlib.h>
#include <stdio.h>
int compteur=0;

int choix_strategie(){
    int strategie_choice;
    printf("1. First-fit  2. Best-fit  3. Worst-fit  4. Next-fit \n");
    printf("Enter the value of the strategie you want to use : ");
    scanf("%d", &strategie_choice);
    if((strategie_choice > 4) || (strategie_choice < 1)){
        printf("please use a valid anwser \n");
        return 0;
    }
    return strategie_choice;
}

int choix_taille_mem(){
    int size_memory;
    printf("\nEnter the total size memory you need : ");
    scanf("%d", &size_memory);
    if((size_memory > 100000) || (size_memory < 0)){
        printf("please use a valid anwser \n");
        return 0;
    }
    return size_memory;
}

int choix_action(node *root){
    int action;

    if (n_bloc_alloues(root)!=0){
        printf("1. Allocation mémoire  2. Libérer mémoire -1. Sortir"); 
        printf("\nEnter the action you want to do : "); 
        scanf("%d", &action);
    }
    else{
        printf("1. Allocation mémoire -1. Sortir"); 
        printf("\nEnter the action you want to do : "); 
        scanf("%d", &action);
    }    
    return action;
}

void allocation_mem(node **root, node **last_node_placed, int strategie_choice, int size_memory){
    if(size_memory==0){
        printf("\nEnter the new memorie size you want to use: ");
        scanf("%d", &size_memory);
    }
    if(strategie_choice == 1){
        if (first_fit(root, size_memory) == 0) {
            printf("There is not a place for the size you ask for %d\n", size_memory);
	    compteur+=1;
        }
    } else if (strategie_choice == 2) {
        if (best_fit(root, size_memory) == 0) {
            printf("There is not a place for the size you ask for %d\n", size_memory);
	    compteur+=1;
        }
    } else if (strategie_choice == 3) {
        if (worst_fit(root, size_memory) == 0) {
            printf("There is not a place for the size you ask for %d\n", size_memory);
	    compteur+=1;
        }
    } else if (strategie_choice == 4) {
        if (next_fit(root, last_node_placed, size_memory) == 0) {
            printf("There is not a place for the size you ask for %d\n", size_memory);
	    compteur+=1;
        }
    }
    }



void liberation_mem(node *root, int bloc_choice){
    int i=0;

    if(bloc_choice==-1){

        //printf("%d\n",(n_bloc_alloues(root)+n_bloc_libres(root)-1));

        printf("Enter the number of free bloc you want to modify :"); 
        scanf("%d", &bloc_choice);

        /*if(bloc_choice>(n_bloc_alloues(root)+n_bloc_libres(root)-1)){
            printf("Bloc %d chosen doesn't exist. \n", bloc_choice);        
            printf("Bloc %d replaced by last bloc %d \n", bloc_choice, (n_bloc_alloues(root)+n_bloc_libres(root)-1)); 
            bloc_choice=(n_bloc_alloues(root)+n_bloc_libres(root)-1);
        }
        if(bloc_choice<0){
            printf("Bloc %d chosen doesn't exist. \n", bloc_choice);        
            printf("Bloc %d replaced by first bloc 0 \n", bloc_choice); 
            bloc_choice=0;
        }*/

    }
	node *select_node = root;
	for(int i = 0; i< bloc_choice;i++){
	    select_node = select_node->p_next;    
	}
	libere_mem(select_node);

}
        




int main() {
    
    int continuing = 1;
    int action;
    int strategie_choice;
    int size_memory;
    int parametre;

    int mode;
    int fois;
    int i;
    char ligne[80];
    FILE* fichier = NULL;
    int param[2] = {0}; // Tableau des paramètres nécessaires pour lancer le test

    printf("1. Utilisation 2.Script Automatique"); 
    printf("\nEnter the mode you want: "); 
    scanf("%d", &mode);

    switch(mode) {

      case 1  :
        printf("\n!!IF YOU WANT TO STOP USING THE PROGRAM ANSWER -1!!!!\n");
        strategie_choice=choix_strategie();
        size_memory=choix_taille_mem();
        node *root = init_mem(size_memory);
        node *last_node_placed = root;
        while(continuing){
            affiche_parametres_memoire(root);
            affiche_etat_memoire(root);
            action = choix_action(root);
            if(action==1){
                allocation_mem(&root, &last_node_placed, strategie_choice,0);
            }
            else if(action==2){
                liberation_mem(root,-1);
            }  
            else if(action==-1){
                continuing = 0;
                free_all(root);
            } 
        }
        break; 
	
      case 2  :
        fichier = fopen("test.txt", "r");
        if (fichier != NULL){
            fgets(ligne, 80, fichier); /*fin de fichier non atteinte*/
            sscanf(ligne,"%i,%i",&strategie_choice,&size_memory);
            node *root = init_mem(size_memory);
            node *last_node_placed = root;
            while ( fgets(ligne, 80, fichier) != NULL ){
                sscanf(ligne,"%i,%i",&action,&parametre);
                printf("%i,%i\n",action,parametre);
                i=0;
                if(action==1){
   		    allocation_mem(&root, &last_node_placed,strategie_choice,parametre);
                }
                else if(action==2){
                    liberation_mem(root,parametre);
                }  
            }
        }
        fclose(fichier);
        affiche_parametres_memoire(root);
        affiche_etat_memoire(root);
        printf(" - Nombre de blocs libres : %d\n", n_bloc_libres(root));
        break; 
    }

    printf("\n - Le nombre de erreurs survenues : %d\n", compteur);


    return 0;
}


