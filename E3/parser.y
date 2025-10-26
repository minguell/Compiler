%{
#include <stdio.h>
#include <string.h>

int yylex(void);
void yyerror (char const *mensagem);
int get_line_number();


asd_tree_t* asd_new_bin_op(char* op, asd_tree_t* child1, asd_tree_t* child2) {
    asd_tree_t* node = asd_new(op);
    asd_add_child(node, child1);
    asd_add_child(node, child2);
    return node;
}

asd_tree_t* asd_new_un_op(char* op, asd_tree_t* child) {
    asd_tree_t* node = asd_new(op);
    asd_add_child(node, child);
    return node;
}
%}

%code requires {
    #include "asd.h"
    extern asd_tree_t *arvore; 
    typedef struct {
        int numero_linha;
        int tipo;
        char* valor;
    } valor_lexico;
}

%define parse.error verbose
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
%token <valor_lexico> TK_ID
%token <valor_lexico> TK_LI_INTEIRO
%token <valor_lexico> TK_LI_DECIMAL
%token TK_ER

%union {
        valor_lexico valor_lexico;
        asd_tree_t* nodo_arvore;
}


%type <nodo_arvore> programa lista elemento declaracao_funcao
%type <nodo_arvore> cabecalho_funcao 
%type <nodo_arvore> bloco_de_comandos sequencia_comandos comando matched_statement unmatched_statement
%type <nodo_arvore> outro_comando declaracao_variavel_comando atribuicao chamada_funcao retorno repeticao
%type <nodo_arvore> expressao expr_logica_ou expr_logica_e expr_igualdade expr_relacional
%type <nodo_arvore> expr_aditiva expr_multiplicativa expr_unaria fator literal argumentos
%type <nodo_arvore> argumentos_opcional 

%type <valor_lexico> declaracao_variavel 

%%

programa: lista ';'	{ arvore = $1;}
        | %empty	{ arvore = NULL; }
        ;
        
lista: elemento		{ $$ = $1; }
     | elemento ',' lista	{ if ($1 != NULL) {
                                  asd_add_child($1, $3); 
                                  $$ = $1;
                              } else {
                                  $$ = $3;
                              }
                            }
     ;
     
elemento: declaracao_variavel	{ $$ = NULL; free($1.valor); }
        | declaracao_funcao	{ $$ = $1; }
        ;


declaracao_variavel: TK_VAR TK_ID TK_ATRIB tipo_num {
                        $$ = $2; 
                    };

declaracao_funcao: cabecalho_funcao bloco_de_comandos {
                        $$ = $1;
                        if ($2 != NULL){
                              asd_add_child($$, $2); 
                         }
                   };


cabecalho_funcao: TK_ID TK_SETA tipo_num lista_parametros_opcional TK_ATRIB {
                        $$ = asd_new($1.valor); 
                        free($1.valor);
                  };


lista_parametros_opcional: lista_parametros
                         | %empty
                         ;
                         
lista_parametros: TK_COM parametros
                | parametros
                ;
                
parametros: parametro
          | parametro ',' parametros
          ;

parametro: TK_ID TK_ATRIB tipo_num		{
                free($1.valor); 
           };


bloco_de_comandos: '{' '}' 			{ $$ = NULL; }
                 | '{' sequencia_comandos '}'	{ $$ = $2; }
                 ;
                 
sequencia_comandos: comando			{ $$ = $1; }
                  | comando sequencia_comandos	{ 
                        if ($1 != NULL) {
                            asd_add_child($1, $2); 
                            $$ = $1;
                        } else {
                            $$ = $2;
                        }
                    }
                  
comando: matched_statement			{ $$ = $1; }
       | unmatched_statement			{ $$ = $1; }
       ;
       
matched_statement: TK_SE '(' expressao ')' matched_statement TK_SENAO matched_statement		{
                        $$ = asd_new("se"); 
                        asd_add_child($$, $3); 
                        asd_add_child($$, $5); 
                        asd_add_child($$, $7); 
                   }
                 | outro_comando		{ $$ = $1; }
                 ;
 
unmatched_statement: TK_SE '(' expressao ')' comando		{
                        $$ = asd_new("se"); 
                        asd_add_child($$, $3); 
                        asd_add_child($$, $5); 
                   }
                   | TK_SE '(' expressao ')' matched_statement TK_SENAO unmatched_statement	{
                        $$ = asd_new("se");
                        asd_add_child($$, $3);
                        asd_add_child($$, $5);
                        asd_add_child($$, $7);
                   }
                   ;
                   
outro_comando: bloco_de_comandos		{ $$ = $1; }
             | declaracao_variavel_comando	{ $$ = $1; }
             | atribuicao ';'			{ $$ = $1; } 
             | chamada_funcao ';'		{ $$ = $1; } 
             | retorno				{ $$ = $1; }
             | repeticao			{ $$ = $1; }
             ;


declaracao_variavel_comando: declaracao_variavel ';' { 
                                $$ = NULL; 
                                free($1.valor); 
                           }
                           | declaracao_variavel TK_COM literal ';' { 
                                $$ = asd_new("com"); 
                                asd_tree_t* id_node = asd_new($1.valor); 
                                asd_add_child($$, id_node);
                                asd_add_child($$, $3);
                                free($1.valor); 
                           }
                           ;

literal: TK_LI_INTEIRO 		{ $$ = asd_new($1.valor); free($1.valor);}
	| TK_LI_DECIMAL			{ $$ = asd_new($1.valor); free($1.valor);} 
;

atribuicao: TK_ID TK_ATRIB expressao { 
                $$ = asd_new(":="); 
                asd_tree_t* id_node = asd_new($1.valor);
                asd_add_child($$, id_node); 
                asd_add_child($$, $3);     
                free($1.valor);
            };


chamada_funcao: TK_ID '(' argumentos_opcional ')' {
                    char label[256];
                    sprintf(label, "call %s", $1.valor);
                    $$ = asd_new(label); 
                    if ($3 != NULL) {
                        asd_add_child($$, $3); 
                    }
                    free($1.valor);
              }
              ;
              
argumentos_opcional: argumentos     { $$ = $1; }
                   | %empty         { $$ = NULL; }
                   ;

argumentos: expressao				{ $$ = $1; }
          | expressao ',' argumentos		{ asd_add_child($1, $3); $$ = $1; }
          ;
          

retorno: TK_RETORNA expressao TK_ATRIB tipo_num ';' { 
            $$ = asd_new("retorna"); 
            asd_add_child($$, $2);
         };


repeticao: TK_ENQUANTO '(' expressao ')' bloco_de_comandos {	
                $$ = asd_new("enquanto"); 
                asd_add_child($$, $3); 
                asd_add_child($$, $5); 
           };	

tipo_num: TK_DECIMAL
          | TK_INTEIRO
          ;

expressao: expr_logica_ou		{ $$ = $1; };

expr_logica_ou: expr_logica_ou '|' expr_logica_e	{ $$ = asd_new_bin_op("|", $1, $3); }
              | expr_logica_e				{ $$ = $1; }
              ;
              
expr_logica_e: expr_logica_e '&' expr_igualdade		{ $$ = asd_new_bin_op("&", $1, $3); }
             | expr_igualdade				{ $$ = $1; }
             ;

expr_igualdade: expr_igualdade TK_OC_EQ expr_relacional		{ $$ = asd_new_bin_op("==", $1, $3); }
              | expr_igualdade TK_OC_NE expr_relacional		{ $$ = asd_new_bin_op("!=", $1, $3); }
              | expr_relacional					{ $$ = $1; }
              ;

expr_relacional: expr_relacional '<' expr_aditiva		{ $$ = asd_new_bin_op("<", $1, $3); }
               | expr_relacional '>' expr_aditiva		{ $$ = asd_new_bin_op(">", $1, $3); }
               | expr_relacional TK_OC_LE expr_aditiva		{ $$ = asd_new_bin_op("<=", $1, $3); }
               | expr_relacional TK_OC_GE expr_aditiva		{ $$ = asd_new_bin_op(">=", $1, $3); }
               | expr_aditiva		{ $$ = $1; }
               ;


expr_aditiva: expr_aditiva '+' expr_multiplicativa		{ $$ = asd_new_bin_op("+", $1, $3); }
            | expr_aditiva '-' expr_multiplicativa		{ $$ = asd_new_bin_op("-", $1, $3); }
            | expr_multiplicativa	{ $$ = $1; }
            ;

expr_multiplicativa: expr_multiplicativa '*' expr_unaria	{ $$ = asd_new_bin_op("*", $1, $3); }
                   | expr_multiplicativa '/' expr_unaria	{ $$ = asd_new_bin_op("/", $1, $3); }
                   | expr_multiplicativa '%' expr_unaria	{ $$ = asd_new_bin_op("%", $1, $3); }
                   | expr_unaria	{ $$ = $1; }
                   ;

expr_unaria: '+' fator		{ $$ = asd_new_un_op("+", $2); }
           | '-' fator		{ $$ = asd_new_un_op("-", $2); }
           | '!' fator		{ $$ = asd_new_un_op("!", $2); }
           | fator		{ $$ = $1; }
           ;

fator: TK_ID                  { $$ = asd_new($1.valor); free($1.valor); }
     | literal			{ $$ = $1; }
     | chamada_funcao		{ $$ = $1; }
     | '(' expressao ')'	{ $$ = $2; }
     ;
     
%%

 void yyerror (char const *mensagem) {

    printf ("Erro na Linha %i - [%s]\n", get_line_number(), mensagem);

}

