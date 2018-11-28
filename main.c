#include "mem_handler.h"

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

int allocation_mem(node *root, int strategie_choice){
    int size_memory;
    int return_val_strat =0;

    printf("\nEnter the new memorie size you want to use: ");
    scanf("%d", &size_memory);
    if(size_memory < 0){
        return 0;
    }
    else{
        if(strategie_choice == 1){
            return_val_strat = first_fit(&root, size_memory);
        }else if(strategie_choice == 2){
            return_val_strat = best_fit(root, size_memory);
        }else if(strategie_choice == 3){
            return_val_strat = worst_fit(root, size_memory);
        }else if(strategie_choice == 4){
            return_val_strat = next_fit(root, size_memory,root);     
        }
    }
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

node *choix_bloc(node *root){
    int continuing = 1;
    int bloc_choice;
    int i=0;

    affiche_etat_memoire(root);
    printf("Enter the number of free bloc you want to modify :"); 
    scanf("%d", &bloc_choice);

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
    int bloc_choice;
    int size_memory;
    
    size_memory=choix_taille_mem();
    node *root = init_mem(size_memory);

    printf("\n!!IF YOU WANT TO STOP USING THE PROGRAM ANSWER -1!!!\n");

    while(continuing){
        affiche_parametres_memoire(root);
        action = choix_action(root);
        
        if(action==1){
            strategie_choice=choix_strategie();
            allocation_mem(root,strategie_choice);
        }
        else if(action==2){
            choix_bloc(root);
        }  
        else if(action==-1){
            continuing = 0;
        } 
    }

    free_all(root);
    return 0;
}

