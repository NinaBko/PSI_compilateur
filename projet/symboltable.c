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
    u_int16_t adress;                // adresse = index dans la table /16bits
    int init;                       // 0 - non initialise, 1 - intitialise
    int type;                       // 0 - non constant, 1 - constante
    int depth;
} element;

typedef struct s_table {
    int index;                      // index sur le premier element vide
    element table[TAILLE_TABLE];    // structure de la table
} table;

// On cree la table et on met tous ses elements a 0
table global_table = {0};

// Fonction qui rajoute un element dans la table
void add_table(char *e_id, u_int16_t e_adress, int e_init, int e_type, int e_depth) {
    // Check if a double definition exists
    element new_element = global_table.table[global_table.index];
    element *p_new_element = &new_element;
    strcpy(p_new_element -> id, e_id);
    p_new_element -> adress = e_adress;
    p_new_element -> init = e_init;
    p_new_element -> type = e_type;
    p_new_element -> depth = e_depth;

    global_table.index ++;
}

// Fonction qui trouve le bon element et renvoie un pointeur sur la ligne de la table
element* get_element(char *id) {
    int index = global_table.index;
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

// Gestion de la profondeur 
void erase_depth() {
    int index = global_table.index;
    int act_depth = global_table.table[index].depth;
    while (global_table.table[index].depth == act_depth) {
        global_table.index --;
    }
}

