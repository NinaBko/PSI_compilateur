#include "symboltable.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TAILLE_TABLE 100

/** Structure elements table */
/* id       - nom du symbole */
/* adresse  - emplacement dans la memoire */
/* init     - verification s'il a ete initialise */
/* type     - constante ou pas */
/* depth    - profondeur des variables */

typedef struct s_element {
    char *id;
    u_int16_t adress;               // adresse = index dans la table /16bits
    int init;                       // 0 - non initialise, 1 - intitialise
    int type;                       // 0 - non constant, 1 - constante
    int depth;
} element;

typedef struct s_table {
    u_int16_t index;                      // index sur le premier element vide
    element table[TAILLE_TABLE];    // structure de la table
} table;

// On cree la table et on met tous ses elements a 0
table global_table = {0};

// Fonction qui trouve le bon element et renvoie un pointeur sur la ligne de la table
element* get_element(char *id) {
    u_int16_t index = global_table.index;
    element *element_trouve = malloc(sizeof(element_trouve));
    element_trouve = NULL;
    // on parcourt en partant de la fin de la table
    while (index >= 0) {
        if (strcmp(global_table.table[index].id, id) == 0) {
            element_trouve = &global_table.table[index];
            index = -1;
        } else {
            index --;
        }
    }
    return element_trouve;
}

// Fonction qui rajoute un element dans la table
void add_table(char *e_id, int e_init, int e_type, int e_depth) {
    // Check if a double definition exists
    element* element_cmp = get_element(e_id);
    if (element_cmp -> depth == e_depth) {
        printf("ERREUR: double definition !");
    }
    else {
        element e;
        strcpy(e.id, e_id);
        e.adress = global_table.index;
        e.init = e_init;
        e.type = e_type;
        e.depth = e_depth;
        global_table.table[global_table.index] = e;
        global_table.index ++;
    }  
}

// Gestion de la profondeur 
void erase_depth() {
    u_int16_t index = global_table.index;
    int act_depth = global_table.table[index].depth;
    while (global_table.table[index].depth == act_depth) {
        global_table.index --;
    }
}

void print_table() {
    printf("Table des symboles \n");
    printf("**********************************************\n");
    printf("Format: | id | adress | init | type | depth |\n");
    int i;
    for (i = 0; i < global_table.index; i++) {
        printf("| %s | %d | %d | %d | %d |\n", global_table.table[i].id, global_table.table[i].adress, global_table.table[i].init, global_table.table[i].type, global_table.table[i].depth);
        printf("**********************************************\n");
    }
}

