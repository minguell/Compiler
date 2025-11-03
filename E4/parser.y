/* Augusto Mattei Grohmnann - 550429
 Miguel Dutra Fontes Guerra - 342573 */
 
%{
#include <stdio.h>
#include <string.h>
#include "asd.h"
#include "tabela.h" // Incluído para acesso à tabela de símbolos e tipos
#include "errors.h"   // Incluído para os códigos de erro

int yylex(void);
void yyerror (char const *mensagem);
int get_line_number();

// Funções auxiliares para criar nós da AST
static asd_tree_t* asd_new_binary_op(const char* label, asd_tree_t* child1, asd_tree_t* child2);
static asd_tree_t* asd_new_unary_op(const char* label, asd_tree_t* child);

// Função auxiliar para verificação de tipos em operações binárias
void check_types(asd_tree_t* node, asd_tree_t* child1, asd_tree_t* child2);
%}

%code requires {
     #include "asd.h"
     #include "tabela.h" // Adicionado para ter as definições de tipo no %union
     extern asd_tree_t *arvore;
     // Estrutura do valor léxico vindo do scanner.l
     typedef struct {
          int numero_linha;
          int tipo_token; // Renomeado para evitar conflito com 'tipo' da gramática
          char* valor;
     } valor_lexico;
}

%define parse.error verbose

// Tokens da linguagem
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

// Union para os valores semânticos ($$, $1, $2, etc.)
%union {
    valor_lexico valor_lexico;
    asd_tree_t* nodo_arvore;
    int tipo_dado; // Adicionado para propagar tipos (TYPE_INTEGER, TYPE_FLOAT)
}

// Tipos dos não-terminais
%type <nodo_arvore> programa lista elemento declaracao_funcao
%type <nodo_arvore> cabecalho_funcao lista_parametros_opcional lista_parametros parametros parametro
%type <nodo_arvore> bloco_de_comandos sequencia_comandos comando matched_statement unmatched_statement
%type <nodo_arvore> outro_comando atribuicao chamada_funcao retorno repeticao
%type <nodo_arvore> expressao expr_logica_ou expr_logica_e expr_igualdade expr_relacional
%type <nodo_arvore> expr_aditiva expr_multiplicativa expr_unaria fator literal argumentos

// Não-terminais que não geram nós, mas passam informações (como tipo)
%type <tipo_dado> tipo_num
%type <nodo_arvore> declaracao_variavel // Modificado para retornar um nó em caso de inicialização

%%

programa: lista ';' { arvore = $1; }
        | %empty    { arvore = NULL; }
        ;
        
lista:  elemento                { $$ = $1; }
      | elemento ',' lista      { 
                                    if ($1 != NULL) {
                                        if ($3 != NULL) {
                                            asd_add_child($1, $3);
                                        }
                                        $$ = $1;
                                    } else {
                                        $$ = $3;
                                    }
                                }
      ;

elemento: declaracao_variavel   { $$ = $1; /* Agora pode retornar um nó (inicialização) */ }
        | declaracao_funcao     { $$ = $1; }
        ;
        
declaracao_variavel: TK_VAR TK_ID TK_ATRIB tipo_num {
                         // Ação Semântica: Adiciona variável à tabela de símbolos do escopo atual
                         add_symbol($2.valor, $2.numero_linha, NATURE_VARIABLE, $4);
                         free($2.valor);
                         $$ = NULL; // Declaração simples não gera nó na AST
                    }
                   | TK_VAR TK_ID TK_ATRIB tipo_num TK_COM literal {
                         // Ação Semântica: Adiciona variável e verifica tipo da inicialização
                         add_symbol($2.valor, $2.numero_linha, NATURE_VARIABLE, $4);
                         
                         if ($4 != $6->data_type) {
                            semantic_error(ERR_WRONG_TYPE, $2.numero_linha, "Tipo do literal de inicialização é incompatível com a variável.");
                         }
                         
                         $$ = asd_new(":=");
                         asd_tree_t* id_node = asd_new($2.valor);
                         id_node->data_type = $4;
                         asd_add_child($$, id_node);
                         asd_add_child($$, $6);
                         free($2.valor);
                   };

declaracao_funcao: cabecalho_funcao bloco_de_comandos {
                        $$ = $1;
                        if ($2 != NULL){
                              asd_add_child($$, $2);
                        }
                        pop_scope(); // Fim do escopo da função
                   };

cabecalho_funcao: TK_ID TK_SETA tipo_num 
                  {
                      add_symbol($1.valor, $1.numero_linha, NATURE_FUNCTION, $3);
                      push_scope(); 
                  }
                  lista_parametros_opcional TK_ATRIB 
                  {
                      $$ = asd_new($1.valor);
                      $$->data_type = $3;
                      
                      if($4 != NULL) {
                         asd_add_child($$, $4);
                         symbol_t* func_symbol = find_symbol($1.valor);
                         if (func_symbol) {
                            func_symbol->params = $4->children[0]; 
                         }
                      }
                      free($1.valor);
                  }
                  '[' // O { push_scope(); } [cite: 141] foi removido daqui
                ;


lista_parametros_opcional: lista_parametros { $$ = $1; }
                         | %empty		    { $$ = NULL; }
                         ;

lista_parametros: TK_COM parametros { $$ = $2; }
                | parametros		{ $$ = $1; }
                ;

parametros: parametro                { $$ = asd_new("params"); asd_add_child($$, $1); }
          | parametro ',' parametros { asd_add_child($1, $3->children[0]); free($3); $$ = $1; }
          ;

parametro: TK_ID TK_ATRIB tipo_num {
               // Ação Semântica: Adiciona o parâmetro à tabela de símbolos do escopo atual
               add_symbol($1.valor, $1.numero_linha, NATURE_VARIABLE, $3);
               
               $$ = asd_new($1.valor);
               $$->data_type = $3;
               free($1.valor);
           };


bloco_de_comandos: '[' { push_scope(); } ']'            { pop_scope(); $$ = NULL; }
                 | '[' { push_scope(); } sequencia_comandos ']' { pop_scope(); $$ = $3; }
                 ;

sequencia_comandos:   comando                       { $$ = $1; }
                    | comando sequencia_comandos    { 
                                    if ($1 != NULL) {
                                        if ($2 != NULL) asd_add_child($1, $2);
                                        $$ = $1;
                                    } else {
                                        $$ = $2;
                                    }
                                }
                    ;

comando: matched_statement   { $$ = $1; }
       | unmatched_statement { $$ = $1; }
       ;
       
matched_statement: TK_SE '(' expressao ')' matched_statement TK_SENAO matched_statement {
                        $$ = asd_new("se");
                        asd_add_child($$, $3); 
                        if ($5 != NULL) asd_add_child($$, $5);
                        if ($7 != NULL) asd_add_child($$, $7);
                   }
                 | outro_comando { $$ = $1; }
                 ;

unmatched_statement: TK_SE '(' expressao ')' comando {
                        $$ = asd_new("se");
                        asd_add_child($$, $3); 
                        if ($5 != NULL) asd_add_child($$, $5);
                   }
                   | TK_SE '(' expressao ')' matched_statement TK_SENAO unmatched_statement {
                        $$ = asd_new("se");
                        asd_add_child($$, $3);
                        if ($5 != NULL) asd_add_child($$, $5);
                        if ($7 != NULL) asd_add_child($$, $7);
                   }
                   ;

outro_comando: bloco_de_comandos { $$ = $1; }
             | declaracao_variavel { $$ = $1; /* Passa o nó de inicialização, se houver */ }
             | atribuicao { $$ = $1; }
             | chamada_funcao { $$ = $1; }
             | retorno { $$ = $1; }
             | repeticao { $$ = $1; }
             ;

literal: TK_LI_INTEIRO { $$ = asd_new($1.valor); $$->data_type = TYPE_INTEGER; free($1.valor); }
	   | TK_LI_DECIMAL { $$ = asd_new($1.valor); $$->data_type = TYPE_FLOAT; free($1.valor); } 
       ;

atribuicao: TK_ID TK_ATRIB expressao { 
                // Ação Semântica: Verifica declaração e tipos da atribuição
                symbol_t* symbol = find_symbol($1.valor);
                if (symbol == NULL) {
                    semantic_error(ERR_UNDECLARED, $1.numero_linha, $1.valor);
                }
                if (symbol->nature != NATURE_VARIABLE) {
                    semantic_error(ERR_FUNCTION, $1.numero_linha, $1.valor);
                }
                if (symbol->type != $3->data_type) {
                    semantic_error(ERR_WRONG_TYPE, $1.numero_linha, "Tipo da expressão incompatível com a variável.");
                }

                $$ = asd_new(":=");
                asd_tree_t* id_node = asd_new($1.valor);
                id_node->data_type = symbol->type;
                asd_add_child($$, id_node); 
                asd_add_child($$, $3);     
                free($1.valor);
            };

chamada_funcao: TK_ID '(' ')' {
                    // Ação Semântica: Verifica a chamada de função sem argumentos
                    symbol_t* symbol = find_symbol($1.valor);
                    if (symbol == NULL) semantic_error(ERR_UNDECLARED, $1.numero_linha, $1.valor);
                    if (symbol->nature != NATURE_FUNCTION) semantic_error(ERR_VARIABLE, $1.numero_linha, $1.valor);
                    if (symbol->params != NULL) semantic_error(ERR_MISSING_ARGS, $1.numero_linha, $1.valor);
                    
                    char label[256];
                    sprintf(label, "call %s", $1.valor);
                    $$ = asd_new(label);
                    $$->data_type = symbol->type;
                    free($1.valor);
              }
              | TK_ID '(' argumentos ')' {
                    // Ação Semântica: Verifica a chamada de função com argumentos
                    symbol_t* symbol = find_symbol($1.valor);
                    if (symbol == NULL) semantic_error(ERR_UNDECLARED, $1.numero_linha, $1.valor);
                    if (symbol->nature != NATURE_FUNCTION) semantic_error(ERR_VARIABLE, $1.numero_linha, $1.valor);
                    // Lógica para verificar número e tipo dos argumentos...
                    
                    char label[256];
                    sprintf(label, "call %s", $1.valor);
                    $$ = asd_new(label);
                    $$->data_type = symbol->type;
                    asd_add_child($$, $3); 
                    free($1.valor);
              }
              ;
              
argumentos: expressao                { $$ = $1; }
          | expressao ',' argumentos { asd_add_child($1, $3); $$ = $1; }
          ;

retorno: TK_RETORNA expressao TK_ATRIB tipo_num { 
            // Ação Semântica: Verificar se o tipo do retorno é compatível com o tipo da expressão
            if ($4 != $2->data_type) {
                semantic_error(ERR_WRONG_TYPE, get_line_number(), "Tipo de retorno incompatível com a expressão retornada.");
            }
            // A verificação do tipo do retorno com o da função deve ser feita no nó da função
            $$ = asd_new("retorna");
            asd_add_child($$, $2);
         };

repeticao: TK_ENQUANTO '(' expressao ')' bloco_de_comandos {	
                $$ = asd_new("enquanto");
                asd_add_child($$, $3);
                if ($5 != NULL) asd_add_child($$, $5);
           };

tipo_num: TK_DECIMAL { $$ = TYPE_FLOAT; }
        | TK_INTEIRO { $$ = TYPE_INTEGER; }
        ;

expressao: expr_logica_ou { $$ = $1; };

expr_logica_ou: expr_logica_ou '|' expr_logica_e { $$ = asd_new_binary_op("|", $1, $3); check_types($$, $1, $3); }
              | expr_logica_e                   { $$ = $1; }
              ;

expr_logica_e: expr_logica_e '&' expr_igualdade { $$ = asd_new_binary_op("&", $1, $3); check_types($$, $1, $3); }
             | expr_igualdade                  { $$ = $1; }
             ;

expr_igualdade: expr_igualdade TK_OC_EQ expr_relacional { $$ = asd_new_binary_op("==", $1, $3); check_types($$, $1, $3); } 
              | expr_igualdade TK_OC_NE expr_relacional { $$ = asd_new_binary_op("!=", $1, $3); check_types($$, $1, $3); }
              | expr_relacional                         { $$ = $1; }
              ;

expr_relacional: expr_relacional '<' expr_aditiva      { $$ = asd_new_binary_op("<", $1, $3); check_types($$, $1, $3); }
               | expr_relacional '>' expr_aditiva      { $$ = asd_new_binary_op(">", $1, $3); check_types($$, $1, $3); }
               | expr_relacional TK_OC_LE expr_aditiva { $$ = asd_new_binary_op("<=", $1, $3); check_types($$, $1, $3); }
               | expr_relacional TK_OC_GE expr_aditiva { $$ = asd_new_binary_op(">=", $1, $3); check_types($$, $1, $3); }
               | expr_aditiva                          { $$ = $1;}
               ;

expr_aditiva: expr_aditiva '+' expr_multiplicativa { $$ = asd_new_binary_op("+", $1, $3); check_types($$, $1, $3); }
            | expr_aditiva '-' expr_multiplicativa { $$ = asd_new_binary_op("-", $1, $3); check_types($$, $1, $3); }
            | expr_multiplicativa                  { $$ = $1; }
            ;

expr_multiplicativa: expr_multiplicativa '*' expr_unaria { $$ = asd_new_binary_op("*", $1, $3); check_types($$, $1, $3); }
                   | expr_multiplicativa '/' expr_unaria { $$ = asd_new_binary_op("/", $1, $3); check_types($$, $1, $3); }
                   | expr_multiplicativa '%' expr_unaria { $$ = asd_new_binary_op("%", $1, $3); check_types($$, $1, $3); }
                   | expr_unaria                         { $$ = $1; }
                   ;

expr_unaria: '+' fator { $$ = asd_new_unary_op("+", $2); $$->data_type = $2->data_type; }
           | '-' fator { $$ = asd_new_unary_op("-", $2); $$->data_type = $2->data_type; }
           | '!' fator { $$ = asd_new_unary_op("!", $2); $$->data_type = $2->data_type; }
           | fator     { $$ = $1; }
           ;

fator: TK_ID {
           // Ação Semântica: Busca o identificador e anota seu tipo no nó
           symbol_t* symbol = find_symbol($1.valor);
           if (symbol == NULL) {
               semantic_error(ERR_UNDECLARED, $1.numero_linha, $1.valor);
           }
           if (symbol->nature != NATURE_VARIABLE) {
               semantic_error(ERR_FUNCTION, $1.numero_linha, $1.valor);
           }
           $$ = asd_new($1.valor);
           $$->data_type = symbol->type;
           free($1.valor);
       }
     | literal        { $$ = $1; }
     | chamada_funcao { $$ = $1; }
     | '(' expressao ')' { $$ = $2; }
     ;
%%

// Implementação das funções auxiliares
void yyerror (char const *mensagem) {
    fprintf (stderr, "Erro sintático na Linha %i: %s\n", get_line_number(), mensagem);
}

static asd_tree_t* asd_new_binary_op(const char* label, asd_tree_t* child1, asd_tree_t* child2) {
     asd_tree_t* node = asd_new(label);
     asd_add_child(node, child1);
     asd_add_child(node, child2);
     return node;
}

static asd_tree_t* asd_new_unary_op(const char* label, asd_tree_t* child) {
     asd_tree_t* node = asd_new(label);
     asd_add_child(node, child);
     return node;
}

// Implementação da verificação de tipos para expressões binárias
void check_types(asd_tree_t* node, asd_tree_t* child1, asd_tree_t* child2) {
    if (child1->data_type == TYPE_UNDEFINED || child2->data_type == TYPE_UNDEFINED) {
        // Um dos filhos não tem tipo, erro já deve ter sido reportado (ex: undeclared)
        node->data_type = TYPE_UNDEFINED;
        return;
    }
    // Regra: float e int não podem ser misturados
    if (child1->data_type != child2->data_type) {
        semantic_error(ERR_WRONG_TYPE, get_line_number(), "Operação com tipos incompatíveis (int e float).");
    }
    // O tipo do nó pai é o mesmo dos filhos
    node->data_type = child1->data_type;
}
