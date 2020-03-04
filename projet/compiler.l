%{
    #include "y.tab.h"
%}

%%
    /* structurel */
"main()"                {printf("tMAIN");}
"{"                     {printf("tAO");}
"}"                     {printf("tAF");}
"("                     {printf("tPO");}
")"                     {printf("tPF");}

    /* type des variables */
"const"                 {printf("tCONST");}
"int"                   {printf("tINT");}
[A-Za-z]+[A-Za-z0-9_]   {printf("tID");}

    /* separateurs */
" "                     {printf("tSPACE");}
"   "                   {printf("tTAB");}
","                     {printf("tVR");}

    /* fin de l'instruction */
";"                     {printf("tPV");}

    /* operations arithmetiques */
"+"                     {printf("tPLUS");}
"-"                     {printf("tMINUS");}
"*"                     {printf("tMULTIPLY");}
"/"                     {printf("tDIVIDE");}
"="                     {printf("tEQUALS");}

    /* erreur pour tous les caracteres non reconnus */
.                       {printf("Error !");}

%%
 
int yywrap(void) {return 1;}
    /* int main() {while (yylex() != 0); return 0;} */

