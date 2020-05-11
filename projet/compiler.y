%{
    #include <stdio.h>
    #include "symboltable.h"
    int yylex();
    void yyerror(char *str);
    int depth = 0;
    int sommet_pile = 100;
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
    | Definition Body                              {printf("Definition\n");}
    | Affectation Body                          {printf("Affectation\n");}
    | Definition Affectation Body           {printf("Definition et affectation\n");}
    | Definition Printf Body
Printf:
    tPRINTF tPO tNB tPF                     {$$=$3; printf("%d",$$);};
Affectation:
    tID tEQ Expr tPV                        {affect($1, depth);};
Expr:
    tNB                                     {$$=$1;}
    | tID                                   {printf("%s",$1);}
    | Expr tPLUS Expr                       {$$=$1+$3; printf("%d",$$);}
    | Expr tMOINS Expr                      {$$=$1-$3; printf("%d",$$);}
    | Expr tMUL Expr                        {$$=$1*$3; printf("%d",$$);}
    | Expr tDIV Expr                        {$$=$1/$3; printf("%d",$$);}
    | tPO Expr tPF                          {$$=$2;};
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
    yyparse(); 
    print_table();
    return 0;
}
