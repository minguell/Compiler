%{
#include <stdio.h>
int yylex(void);
void yyerror (char const *mensagem);
int get_line_number();
%}


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
%token TK_ID
%token TK_LI_INTEIRO
%token TK_LI_DECIMAL
%token TK_ER

%%

programa: lista ';'
        | %empty
        ;
        
lista: elemento
     | lista ',' elemento
     ;
     
elemento: declaracao_variavel
        | declaracao_funcao
        ;
        
declaracao_variavel: TK_VAR TK_ID TK_ATRIB tipo_num;

declaracao_funcao: cabecalho_funcao bloco_de_comandos;

cabecalho_funcao: TK_ID TK_SETA tipo_num lista_parametros_opcional TK_ATRIB;


lista_parametros_opcional: lista_parametros
                         | %empty
                         ;
                         
lista_parametros: TK_COM parametros
                | parametros
                ;
                
parametros: parametro
          | parametros ',' parametro
          ;

parametro: TK_ID TK_ATRIB tipo_num;


bloco_de_comandos: '[' ']'
                 | '[' sequencia_comandos ']'
                 ;
                 
sequencia_comandos: comando
                  | sequencia_comandos comando
                  ;
                  
comando: matched_statement
       | unmatched_statement
       ;
       
/* Um "matched statement" é um if/else completo ou outro comando que não seja um if incompleto. */
matched_statement: TK_SE '(' expressao ')' matched_statement TK_SENAO matched_statement
                 | outro_comando
                 ;
 
/* Um "unmatched statement" contém um if sem else. */
unmatched_statement: TK_SE '(' expressao ')' comando
                   | TK_SE '(' expressao ')' matched_statement TK_SENAO unmatched_statement
                   ;
                   
/* Todos os outros comandos que não são condicionais. */
outro_comando: bloco_de_comandos
             | declaracao_variavel_comando
             | atribuicao
             | chamada_funcao
             | retorno
             | repeticao
             ;
             
declaracao_variavel_comando: declaracao_variavel
                           | declaracao_variavel TK_COM literal
                           ;

literal: TK_LI_INTEIRO | TK_LI_DECIMAL;

atribuicao: TK_ID TK_ATRIB expressao;

chamada_funcao: TK_ID '(' ')'
              | TK_ID '(' argumentos ')'
              ;
              
argumentos: expressao
          | argumentos ',' expressao
          ;
          
retorno: TK_RETORNA expressao TK_ATRIB tipo_num;


repeticao: TK_ENQUANTO '(' expressao ')' bloco_de_comandos;	

tipo_num: TK_DECIMAL 
          | TK_INTEIRO;

expressao: expr_logica_ou;

expr_logica_ou: expr_logica_ou '|' expr_logica_e
              | expr_logica_e
              ;
              
expr_logica_e: expr_logica_e '&' expr_igualdade
             | expr_igualdade
             ;

expr_igualdade: expr_igualdade TK_OC_EQ expr_relacional
              | expr_igualdade TK_OC_NE expr_relacional
              | expr_relacional
              ;

expr_relacional: expr_relacional '<' expr_aditiva
               | expr_relacional '>' expr_aditiva
               | expr_relacional TK_OC_LE expr_aditiva
               | expr_relacional TK_OC_GE expr_aditiva
               | expr_aditiva
               ;


expr_aditiva: expr_aditiva '+' expr_multiplicativa
            | expr_aditiva '-' expr_multiplicativa
            | expr_multiplicativa
            ;

expr_multiplicativa: expr_multiplicativa '*' expr_unaria
                   | expr_multiplicativa '/' expr_unaria
                   | expr_multiplicativa '%' expr_unaria
                   | expr_unaria
                   ;

expr_unaria: '+' fator
           | '-' fator
           | '!' fator
           | fator
           ;

/* Fator: nível mais alto de precedência (literais, IDs, parênteses) */
fator: TK_ID
     | literal
     | chamada_funcao
     | '(' expressao ')'
     ;
     
%%

 void yyerror (char const *mensagem) {

    printf ("Erro na Linha %i - [%s]\n", get_line_number(), mensagem);

}

