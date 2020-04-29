#include <symboltable.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TAILLE_TABLE 10000

/** Structure elements table */
/* id       - nom du symbole */
/* adresse  - emplacement dans la memoire */
/* init     - verification s'il a ete initialise */
/* type     - constante ou pas */
/* depth    - profondeur des variables */

typedef struct {
    char *id;
    uint16_t adress;                // adresse = index dans la table /16bits
    int init;                       // 0 - non initialise, 1 - intitialise
    int type;                       // 0 - non constant, 1 - constante
    int depth;
} element;

typedef struct {
    int index;                      // index sur l'element actuel de la table
    element table[TAILLE_TABLE];    // structure de la table
} table;

// On cree la table et on met tous ses elements a 0
table global_table = {0};

// Fonction qui rajoute un element dans la table
void add_table(char *e_id, uint16_t e_adress, int e_init, int e_type, int e_depth) {
    element *p_new_element = &[global_table.table[global_table[index]]];
    strcpy(p_new_element -> id, id);
    p_new_element -> adress = e_adress;
    p_new_element -> init = e_init;
    p_new_element -> type = e_type;
    p_new_element -> depth = e_depth;

    global_table.index ++;
}





