%{
    #include "y.tab.h"
%}

%%
    /* structurel */
"main"                  {printf("tMAIN");}
"{"                     {printf("tAO");}
"}"                     {printf("tAF");}
"("                     {printf("tPO");}
")"                     {printf("tPF");}

    /* type des variables */
"const"                 {printf("tCONST");}
"int"                   {printf("tINT");}

    /* variables */
[A-Za-z]+[A-Za-z0-9_]*  {
                            yylval.str=strdup(yytext);  
                            return tID;
                        }
[0-9]+                  {
                            yylval.nb=(int)atof(yytext); 
                            return tNB;
                        }                  

    /* separateurs */
" "                     {printf("tSPACE");}
","                     {printf("tVR");}

    /* fin de l'instruction */
";"                     {printf("tPV");}

    /* operations arithmetiques */
"+"                     {printf("tPLUS");}
"-"                     {printf("tMOINS");}
"*"                     {printf("tMUL");}
"/"                     {printf("tDIV");}
"="                     {printf("tEQ"); return tEQ;}

    /* erreur pour tous les caracteres non reconnus */
.                       {printf("Error !");}

%%
 
int yywrap(void) {return 1;}
    /* int main() {while (yylex() != 0); return 0;} */

