#include <symboltable.h>

/** Structure elements table */
/* id       - nom du symbole */
/* adresse  - emplacement dans la memoire */
/* init     - verification s'il a ete initialise */
/* type     - constante ou pas */
/* depth    - profondeur des variables */

typedef struct {
    char *id;
    int adress; 
    int init;       // 0 - non initialise, 1 - intitialise
    int type;       // 0 - non constant, 1 - constante
    int depth;
}