%{
    #include "y.tab.h"
%}

blancs                  [ \t]+

vID                     [_a-zA-Z][_a-zA-Z0-9]*
chiffre                 [0-9]
vNB                     {chiffre}+
exposant                [eE][+-]?{entier}

reel                    {entier}("."{entier})?{exposant}?

%%
{blancs}                { /* ignore */ }

    /* structurel */
"main"                  {return tMAIN;}
"{"                     {return tAO;}
"}"                     {return tAF;}
"("                     {return tPO;}
")"                     {return tPF;}

    /* type des variables */
"const"                 {return tCONST;}
"int"                   {return tINT;}

    /* variables */
{vID}                   {yylval.str = strdup(yytext);   return tID;}
{vNB}                   {yylval.nb = (int)atof(yytext); return tNB;}                  

    /* separateurs */
","                     {return tVR;}

    /* fin de l'instruction */
";"                     {return tPV;}

    /* operations arithmetiques */
"+"                     {return tPLUS;}
"-"                     {return tMOINS;}
"*"                     {return tMUL;}
"/"                     {return tDIV;}
"="                     {return tEQ;}

    /* erreur pour tous les caracteres non reconnus */
.                       {printf("Error !");}

%%
 
int yywrap(void) {return 1;}
    /* int main() {while (yylex() != 0); return 0;} */

