/** Structure elements table */
/* id       - nom du symbole */
/* adresse  - emplacement dans la memoire */
/* init     - verification s'il a ete initialise */
/* type     - constante ou pas */
/* depth    - profondeur des variables */

typedef struct s_element element;
typedef struct s_table table;

extern table global_table;

element* get_element(char *id);
void add_table(char *e_id, int e_init, int e_type, int e_depth);
void print_table();
void init();
void affect(char *e_id, int depth);