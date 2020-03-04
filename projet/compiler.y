%{
    #include <stdio.h>
    int yylex();
    void yyerror(char *str);
%}
%token tMAIN tINT tEQ tID tPO tPF tAO tAF tPV tVR

%% 
%start File;
File:
    Main;
Main: 
    tMAIN tPO tPF tAO Body tAF;
Body: 
    Definition {printf("definition");}
    | Affectation;
Affectation:
    /* vide */;
Definition:
    tINT tID DefinitionN tPV;
DefinitionN:
    /* vide */
    | tVR tID DefinitionN;

%%
    /* Supprimer cette partie dans le fichier .l si presente ici*/
void yyerror(char *str) {};
int main() {
    yyparse(); 
    return 0;
}
