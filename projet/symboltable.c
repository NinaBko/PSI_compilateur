#include "symboltable.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#define TAILLE_TABLE 1000

/** Structure elements table */
/* id       - nom du symbole */
/* adresse  - emplacement dans la memoire */
/* init     - verification s'il a ete initialise */
/* type     - constante ou pas */
/* depth    - profondeur des variables */

typedef struct s_element {
    char* id;
    uint16_t adress;               // adresse = index dans la table /16bits
    int init;                       // 0 - non initialise, 1 - intitialise
    int type;                       // 0 - non constant, 1 - constante
    int depth;
} element;

typedef struct s_table {
    uint16_t index;                  // index sur le premier element vide
    element table[TAILLE_TABLE];    // structure de la table
} table;

// On cree la table et on met tous ses elements a 0
table global_table = {0};

// On initialise la table
void init() {
    for (int i = 0; i < TAILLE_TABLE; i++) {
        global_table.table[i].id = "";
        global_table.table[i].adress = 0;
        global_table.table[i].init = 0;
        global_table.table[i].type = 0;
        global_table.table[i].depth = 0;
    }
}

// Fonction qui trouve le bon element et renvoie un pointeur sur la ligne de la table
element* get_element(char *e_id) {
    uint16_t index = global_table.index;
    int found = 0;
    // on parcourt en partant de la fin de la table
    while (index > 0) {
        if (strcmp(global_table.table[index-1].id, e_id) == 0) {
            found = 1;
            break;
        } else {
            index --;
        }
    }
    if (found == 0) {
        return NULL;
    }
    else {
        return &global_table.table[index-1];
    }
}

void test_get_element() {
    init();
    char* s1 = "youpi!";
    char* s2 = "nope";
    element e1; 
    element e2;
    e1.id = malloc(sizeof(s1));
    e2.id = malloc(sizeof(s2));
    strcpy(e1.id,s1);
    strcpy(e2.id,s2);
    e1.adress = 1;
    e1.type = 1;
    e1.depth = 1;
    e1.init = 1;
    global_table.index ++;
    e2.adress = 2;
    e2.type = 2;
    e2.depth = 2;
    e2.init = 2;
    global_table.index ++;
    global_table.table[0] = e1;
    global_table.table[1] = e2;
    if (get_element(s1) != NULL) {
        printf("%d\n", get_element(s1) -> depth);
    }
    print_table();
}


// Fonction qui rajoute un element dans la table
void add_table(char *e_id, int e_init, int e_type, int e_depth) {
    // Check if a double definition exists
    if (get_element(e_id) != NULL && get_element(e_id) -> depth == e_depth) {
        printf("ERREUR: double definition !");
    }
    else {
        element e;
        e.id = malloc(sizeof(e_id));
        strcpy(e.id, e_id);
        e.adress = global_table.index;
        e.init = e_init;
        e.type = e_type;
        e.depth = e_depth;
        global_table.table[global_table.index] = e;
        global_table.index ++;
    }  
}

uint16_t get_adress(char* e) {
    uint16_t addr =get_element(e)-> adress;
    return addr;
}

// Fonction qui affecte une valeur à la variable
void affect(char *e_id, int depth) {
    if (get_element(e_id) != NULL) {
        int type = get_element(e_id) -> type;
        int init = get_element(e_id) -> init;
        if (type == 1 && init == 1) {
            printf("La constante a deja ete affectee !\n");
        }
        else {
            get_element(e_id) -> init = 1;
        }
    }
    else {
        printf("Cette variable n'a pas ete definie !\n");
    }
}

// Gestion de la profondeur 
void erase_depth() {
    uint16_t index = global_table.index;
    int act_depth = global_table.table[index].depth;
    while (global_table.table[index].depth == act_depth) {
        global_table.index --;
    }
}

void print_table() {
    printf("Table des symboles \n");
    printf("**********************************************\n");
    printf("| id | adress | init | type | depth |\n");
    int i;
    for (i = 0; i < 101; i++) {
        printf("| %s  |    %d   |  %d   |  %d   |   %d   |\n", global_table.table[i].id, global_table.table[i].adress, global_table.table[i].init, global_table.table[i].type, global_table.table[i].depth);
    }
}

/* int main(int argc, char *argv[]) {
    char* s = "symbole 1";
    add_table(s,1,2,3);
    print_table();
    //test_get_element();
} */

// Fonctions pour la generation des instructions assembleur

void print_index() {
    printf("index = %d\n", global_table.index);
}

void push() {
    element e;
    e.id = "";
    e.adress = sommet_pile;
    e.init = 1;
    e.type = 0;
    e.depth = 0;
    global_table.table[sommet_pile] = e;
    sommet_pile--;
}

void pop() {
    element e;
    e.id = "";
    e.adress = 0;
    e.init = 0;
    e.type = 0;
    e.depth = 0;
    global_table.table[sommet_pile] = e;
    sommet_pile ++;
}
