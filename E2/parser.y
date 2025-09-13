%{
#include <stdio.h>
int yylex(void);
void yyerror (char const *mensagem);
int get_line_number();
%}


%define parse.error verboso
%token TK_TIPO
%token TK_VAR
%token TK_SENAO
%token TK_DECIMAL
%token TK_SE
%token TK_INTEIRO
%token TK_ATRIB
%token TK_RETORNA
%token TK_SETA
%token TK_ENQUANTO
%token TK_COM
%token TK_OC_LE
%token TK_OC_GE
%token TK_OC_EQ
%token TK_OC_NE
%token TK_ID
%token TK_LI_INTEIRO
%token TK_LI_DECIMAL
%token TK_ER

%%

programa: lista ';';
programa: %empty;
lista: elemento;
lista: lista ',' elemento;
elemento: declaracao_variavel;
elemento: declaracao_funcao;
declaracao_variavel: TK_VAR TK_ID TK_ATRIB tipo_num;
declaracao_funcao: cabeçalho_funcao bloco_de_comandos
cabeçalho_funcao: TK_ID TK_SETA tipo_num lista_parametros TK_ATRIB;
cabeçalho_funcao: TK_ID TK_SETA tipo_num TK_ATRIB;
tipo_num: TK_DECIMAL | TK_INTEIRO;
lista_parametros: TK_COM parametros;
lista_parametros: parametros;
parametros: parametro | parametros ',' parametro;
parametro: TK_ID TK_ATRIB tipo_num;
comando_simples: bloco_de_comandos | declaracao_variavel_comando | atribuicao | chamada_funcao | retorno | condicional | repeticao;
bloco_de_comandos: '{' sequencia_comandos '}'
bloco_de_comandos: '{' '}'
sequencia_comandos: comando_simples
sequencia_comandos: sequencia_comandos comando_simples 
declaracao_variavel_comando: declaracao_variavel;
declaracao_variavel_comando: declaracao_variavel TK_COM literal;
literal: TK_LI_INTEIRO | TK_LI_DECIMAL;
atribuicao: TK_ID TK_ATRIB expressao;
chamada_funcao: TK_ID '(' argumentos ')';
chamada_funcao: TK_ID '(' ')';
argumentos: expressao;
argumentos: argumentos ',' expressao;
retorno: TK_RETORNA expressao TK_ATRIB tipo_num;
condicional: TK_SE '(' expressao ')' bloco_de_comandos
condicional: TK_SE '(' expressao ')' bloco_de_comandos TK_SENAO bloco_de_comandos
repeticao: TK_ENQUANTO '(' expressao ')' bloco_de_comandos
operando: TK_ID | literal | chamada_funcao | expressao;
expressao: operando | operador_unario operando | operando operador_binario operando;
operador_composto: TK_OC_LE | TK_OC_GE | TK_OC_EQ | TK_OC_NE;
operador_unario: '+' | '-' | '*' | '/' | '%' | operador_composto;

%%

 void yyerror (char const *mensagem) {

    printf ("Erro na Linha %i - [%s]\n", get_line_number(), mensagem);

}

