%{
//Aluno: Miguel Dutra Fontes Guerra
//Cartão UFRGS: 00342573

    #include "ast.hpp"
    #include "parser.tab.hpp"
    #include "funcoes.hpp"
    #include "symbols.hpp"

    using namespace std;
    
    int lineNumber = 1;
    int running = 1;
%}

%option nounput
%option noinput

%x COMMENT

%%

"int"  {return KW_INT;}
"byte" {return KW_BYTE;}
"real" {return KW_REAL;}

"if"   {return KW_IF;}
"else" {return KW_ELSE;}

"do" {return KW_DO;}
"while" {return KW_WHILE;}

"read" {return KW_READ;}
"print" {return KW_PRINT;}

"return" {return KW_RETURN;}

"<=" {return OPERATOR_LE;}
">=" {return OPERATOR_GE;}
"==" {return OPERATOR_EQ;}
"!=" {return OPERATOR_DIF;}

[a-zA-Z_][_a-zA-Z0-9]* {yylval.symbol = symbolInsert(SYMBOL_ID,yytext); return TK_IDENTIFIER;}


[0-9]+ {yylval.symbol = symbolInsert(SYMBOL_LIT_INT,yytext); return LIT_INT;}
'[^']' {yylval.symbol = symbolInsert(SYMBOL_LIT_CHAR,yytext); return LIT_CHAR;}
[0-9]+\/[0-9]+ {yylval.symbol = symbolInsert(SYMBOL_LIT_REAL,yytext); return LIT_REAL;}
\"([^\"\n\\]|\\["\\n])*\"  {yylval.symbol = symbolInsert(SYMBOL_LIT_STRING,yytext); return LIT_STRING;}


[-.,:;+*/=(){}[\]%&<>|~] {return yytext[0];}
[ \t] 
\n {lineNumber++;}


"//".*

"/--" { BEGIN(COMMENT); }
<COMMENT>"--/" { BEGIN(INITIAL); }
<COMMENT>.
<COMMENT>\n {lineNumber++;}


. {return TOKEN_ERROR;}

%%

int yywrap()
{
    running = 0;
    return 1;
}
