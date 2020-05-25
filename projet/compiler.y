%{
    #include <stdio.h>
    #include "symboltable.h"
    int yylex();
    void yyerror(char *str);
    int depth = 0;
%}
%token tMAIN tINT tEQ tPO tPF tAO tAF tPV tVR tPLUS tMOINS tMUL tDIV tCONST tPRINTF
%union{
    int nb;
    char* str;
}
%left tPLUS tMOINS
%left tMUL tDIV
%right tEQ
%token <nb> tNB tXX
%token <str> tID
%type <nb> Expr
%type <nb> Printf

%% 
%start File;

File:
    Main;
Main: 
    tMAIN tPO {init();} tPF tAO Body tAF;         
Body: 
    /*vide*/
    | Definition Body                       {printf("Definition\n");}
    | Affectation Body                      {printf("Affectation\n");}
    | Definition Printf Body
Printf:
    tPRINTF tPO tNB tPF                     {$$=$3; printf("%d",$$);};
Affectation:
    tID tEQ Expr tPV                        {affect($1, depth); printf("COP @%d @%d\n", get_adress($1), sommet_pile); pop();};
Expr:
    tNB                                     {printf("AFC @%d %d\n", sommet_pile, $1); push();}
    | tID                                   {printf("COP @%d @%d\n", sommet_pile, get_adress($1)); push();}
    | Expr tPLUS Expr                       {printf("ADD @%d @%d @%d \n", sommet_pile, sommet_pile, sommet_pile - 1); pop(); pop(); push();}
    | Expr tMOINS Expr                      {printf("SOU @%d @%d @%d \n", sommet_pile, sommet_pile, sommet_pile -1); pop(); pop(); pop();}
    | Expr tMUL Expr                        {printf("MUL @%d @%d @%d \n", sommet_pile, sommet_pile, sommet_pile - 1); pop(); pop(); push();}
    | Expr tDIV Expr                        {printf("DIV @%d @%d @%d \n", sommet_pile, sommet_pile, sommet_pile - 1); pop(); pop(); push();}
    | tPO Expr tPF                          {printf("Affect\n");};
Definition:
    tINT tID DefinitionN tPV                {add_table($2, 0, 0, depth);}
    | tCONST tID DefinitionN tPV            {add_table($2, 0, 1, depth);};     
DefinitionN:
    /* vide */
    | tVR tINT tID DefinitionN              {add_table($3, 0, 0, depth);}
    | tVR tCONST tID DefinitionN            {add_table($3, 0, 1, depth);};
BeginDepth:
    tAO                                     {depth ++;};
EndDepth:
    tAF                                     {erase_depth(); depth --;};

%%
    /* Supprimer cette partie dans le fichier .l si presente ici*/
void yyerror(char *str) {
    fprintf(stderr,"%s\n",str);
};
int main() {
    sommet_pile = 100;
    yyparse(); 
    //print_table();
    return 0;
}
