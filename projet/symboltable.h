/** Structure elements table */
/* id       - nom du symbole */
/* adresse  - emplacement dans la memoire */
/* init     - verification s'il a ete initialise */
/* type     - constante ou pas */
/* depth    - profondeur des variables */
#include <stdint.h>

typedef struct s_element element;
typedef struct s_table table;

extern table global_table;
int sommet_pile;

element* get_element(char *id);
uint16_t get_adress(char* element);
void add_table(char *e_id, int e_init, int e_type, int e_depth);
void print_table();
void print_index();
void init();
void affect(char *e_id, int depth);

void pop();
void push();
