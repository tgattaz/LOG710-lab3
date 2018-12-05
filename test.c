#include "mem_handler.h"
#include <stdlib.h>
#include <stdio.h>

int choix_strategie() {
    int strategie_choice;
    printf("1:First-fit  2:Best-fit  3:Worst-fit  4:Next-fit \n");
    printf("Choisir une stratégie: ");
    scanf("%d", &strategie_choice);
    printf("\n");

    if ((strategie_choice > 4) || (strategie_choice < 1)) {
        printf("Valeur incorrecte\n");
        return 0;
    }

    return strategie_choice;
}

int choix_taille_mem() {
    int size_memory;
    printf("Saisir la taille initiale de la mémoire: ");
    scanf("%d", &size_memory);
    printf("\n");

    if ((size_memory > 100000) || (size_memory < 0)) {
        printf("Valeur incorrecte\n");
        return 0;
    }

    return size_memory;
}

int choix_action(node *root) {
    int action;

    if (n_bloc_alloues(root) != 0) {
        printf("1:Allocation mémoire  2:Libérer mémoire -1:Sortir");
    } else {
        printf("1:Allocation mémoire -1:Sortir");
    }

    printf("\nChoisir une action: ");
    scanf("%d", &action);
    printf("\n");

    return action;
}

void allocation_mem(node **root, node **last_node_placed, int strategie_choice, int size_memory) {
    if (size_memory == 0) {
        printf("Saisir la taille du nouveau bloc: ");
        scanf("%d", &size_memory);
        printf("\n");
    }

    if (strategie_choice == 1) {
        if (first_fit(root, size_memory) == 0) {
            printf("Pas de place disponible correspondant à la demande (%d)\n", size_memory);
        }
    } else if (strategie_choice == 2) {
        if (best_fit(root, size_memory) == 0) {
            printf("Pas de place disponible correspondant à la demande (%d)\n", size_memory);
        }
    } else if (strategie_choice == 3) {
        if (worst_fit(root, size_memory) == 0) {
            printf("Pas de place disponible correspondant à la demande (%d)\n", size_memory);
        }
    } else if (strategie_choice == 4) {
        if (next_fit(root, last_node_placed, size_memory) == 0) {
            printf("Pas de place disponible correspondant à la demande (%d)\n", size_memory);
        }
    }
}

node *liberation_mem(node **root, int bloc_choice) {

    if (bloc_choice == 0) {
        //affiche_etat_memoire(root);
        //printf("%d\n", (n_bloc_alloues(root) + n_bloc_libres(root) - 1));
//        if (bloc_choice > (n_bloc_alloues(root) + n_bloc_libres(root) - 1)) {
//            printf("Le bloc %d choisi n'existe pas.\n", bloc_choice);
//            printf("Bloc %d remplacé par le dernier bloc (%d)\n", bloc_choice,
//                   (n_bloc_alloues(root) + n_bloc_libres(root) - 1));
//            bloc_choice = (n_bloc_alloues(root) + n_bloc_libres(root) - 1);
//        }
//        if (bloc_choice < 0) {
//            printf("Bloc %d chosen doesn't exist. \n", bloc_choice);
//            printf("Bloc %d replaced by first bloc 0 \n", bloc_choice);
//            bloc_choice = 0;
//        }

        printf("Saisir le numéro du bloc à libérer: ");
        scanf("%d", &bloc_choice);
        printf("\n");

        int n_blocs = (n_bloc_alloues(*root) + n_bloc_libres(*root));
        if (bloc_choice >= 0 && bloc_choice <= n_blocs-1) {

            node *select_node = *root;
            for (int i = 0; i < bloc_choice; i++) {
                select_node = select_node->p_next;
            }

            if (select_node->value->state == 1) {
                return libere_mem(select_node);
            } else {
                printf("Le bloc choisi (%d) est déjà libre.\n", bloc_choice);
            }

        } else {
            printf("Le bloc choisi (%d) n'existe pas.\n", bloc_choice);
        }

        return NULL;


    } else if (bloc_choice > 0) {
        node *select_node = *root;
        for (int i = 0; i < bloc_choice; i++) {
            libere_mem(select_node);
            affiche_etat_memoire(*root);
            select_node = select_node->p_next;
        }

        return NULL;

    }
}

int main() {

    int continuing = 1;
    int action;
    int strategie_choice;
    int size_memory;
    int mode;
    int fois;
    int i;
    char ligne[80];
    FILE *fichier = NULL;

    printf("1:Test manuel 2:Script Automatique\n");
    printf("Choisir un mode de test: ");
    scanf("%d", &mode);
    printf("\n");

    switch (mode) {

        case 1:
            strategie_choice = choix_strategie();

            size_memory = choix_taille_mem();

            node *root = init_mem(size_memory);
            node *last_node_placed = root;

            while (continuing) {

                affiche_etat_memoire(root);
                affiche_parametres_memoire(root);

                action = choix_action(root);
                if (action == 1) {
                    allocation_mem(&root, &last_node_placed, strategie_choice, 0);
                } else if (action == 2) {
                    liberation_mem(&root, 0);
                } else if (action == -1) {
                    continuing = 0;
                    //free_all(root);
                }

            }
            break;

//        case 2:
//            printf("OKOKOKOKOK");
//            fichier = fopen("test.txt", "rt");
//
//            if (fichier != NULL) {
//                fgets(ligne, 80, fichier); /*fin de fichier non atteinte*/
//                sscanf(ligne, "%i,%i", &strategie_choice, &size_memory);
//                node *root = init_mem(size_memory);
//                node *last_node_placed = root;
//                while (fgets(ligne, 80, fichier) != NULL) {
//                    sscanf(ligne, "%i,%i,%i", &fois, &action, &size_memory);
//                    printf("%i,%i,%i\n", fois, action, size_memory);
//                    if (action == 1) {
//                        for (i = 0; i < fois; i++) {
//                            allocation_mem(root, last_node_placed, strategie_choice, size_memory);
//                        }
//                    } else if (action == 2) {
//                        liberation_mem(root, fois);
//                    }
//                }
//            }
//            fclose(fichier);
//            affiche_parametres_memoire(root);
//            affiche_etat_memoire(root);
//            break;

        default:
            printf("Choix de mode invalide");
            break;
    }
    return 0;
}


