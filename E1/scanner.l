/* Augusto Mattei Grohmnann - 550429
 Miguel Dutra Fontes Guerra - 342573 */

%{
#include "tokens.h"
%}

%option noyywrap
%option yylineno


%%

[ \t\r\f\v\n]+      /* Ignora espaços, tabulações e linhas (contadas pelo yylineno) */          
"//".*              /* Ignora comentários de uma linha */

"tipo"              { return TK_TIPO; }
"var"               { return TK_VAR; }
"senao"             { return TK_SENAO; }
"decimal"           { return TK_DECIMAL; }
"se"                { return TK_SE; }
"inteiro"           { return TK_INTEIRO; }
"retorna"           { return TK_RETORNA; }
"enquanto"          { return TK_ENQUANTO; }
"com"               { return TK_COM; }

[!*/%+-<>[\]()=,;&|] { return yytext[0]; }

"<="                { return TK_OC_LE; }
">="                { return TK_OC_GE; }
"=="                { return TK_OC_EQ; }
"!="                { return TK_OC_NE; }
":="                { return TK_ATRIB; }
"->"                { return TK_SETA; }

[a-z_][a-z0-9_]*    { return TK_ID; }

[0-9]+              { return TK_LI_INTEIRO; }
[0-9]+"."[0-9]+     { return TK_LI_DECIMAL; }

.                   {return TK_ER; }

%%

int main(int argc, char* argv[])
{
    int token;
    while ((token = yylex())) {
        // Imprime o token encontrado (para depuração)
        printf("Token: %d, Texto: '%s', Linha: %d\n", token, yytext, yylineno);
    }
    return 0;
}