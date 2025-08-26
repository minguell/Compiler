%{
// Miguel Dutra Fontes Guerra - 342573
#include "stdio.h"
#include "tokens.h"

int running = 1;
int lineNumber = 1;
%}

%x COMMENT

%%

"byte"           { return KW_BYTE; }
"int"            { return KW_INT; }
"real"           { return KW_REAL; }
"if"             { return KW_IF; }
"else"           { return KW_ELSE; }
"do"             { return KW_DO; }
"while"          { return KW_WHILE; }
"read"           { return KW_READ; }
"print"          { return KW_PRINT; }
"return"         { return KW_RETURN; }

[,;:()\[\]{}=+\-*/%<>&|~] { return yytext[0]; }

"<="            { return OPERATOR_LE; }
">="            { return OPERATOR_GE; }
"=="            { return OPERATOR_EQ; }
"!="            { return OPERATOR_DIF; }

[a-zA-Z_][a-zA-Z_0-9]*  { return TK_IDENTIFIER; }

[0-9]+                 { return LIT_INT; }

"'"(\\.|[^'\n])"'"  { return LIT_CHAR; }

[0-9]+"/"[0-9]+        { return LIT_REAL; }

\"([^"\\]|\\.)*\"  { return LIT_STRING; }

[ \t\r\f\v]+         /* Ignora espaços e tabulações */

\n                     { lineNumber++; }

"//".*                /* Ignora comentários de uma linha */

"/--"                 { BEGIN(COMMENT); }

<COMMENT>"--/"        { BEGIN(INITIAL); }
<COMMENT>\n           { lineNumber++; }
<COMMENT>.            /* Ignora conteúdo do comentário */

.  { printf("Erro lexico na linha %d: caractere invalido '%s'\n", lineNumber, yytext); return TOKEN_ERROR; }

%%

#include "main.cpp"

extern int yylex(void);

int yywrap() {
    running = 0;
    return 1;
}

void initMe(void) {}

int getLineNumber(void) {
    return lineNumber;
}

int isRunning(void){
    return running;
}
