/* Augusto Mattei Grohmnann - 550429
 Miguel Dutra Fontes Guerra - 342573 */
 
%{
#include <stdio.h>
#include <string.h>
#include "asd.h"
#include "tabela.h"
#include "errors.h"

int yylex(void);
void yyerror (char const *mensagem);
int get_line_number();

// Variável global para rastrear a função sendo parseada atualmente.
// Essencial para validar os tipos de retorno.
symbol_t* current_function = NULL;

// Funções auxiliares para criar nós da AST
static asd_tree_t* asd_new_binary_op(const char* label, asd_tree_t* child1, asd_tree_t* child2);
static asd_tree_t* asd_new_unary_op(const char* label, asd_tree_t* child);
void check_types(asd_tree_t* node, asd_tree_t* child1, asd_tree_t* child2);
%}

%code requires {
     #include "asd.h"
     #include "tabela.h"
     extern asd_tree_t *arvore;
     typedef struct {
          int numero_linha;
          int tipo_token;
          char* valor;
     } valor_lexico;
}

%define parse.error verbose

// Tokens
%token TK_TIPO TK_VAR TK_SENAO TK_DECIMAL TK_SE TK_INTEIRO TK_ATRIB TK_RETORNA
%token TK_SETA TK_ENQUANTO TK_COM TK_OC_LE TK_OC_GE TK_OC_EQ TK_OC_NE
%token <valor_lexico> TK_ID TK_LI_INTEIRO TK_LI_DECIMAL
%token TK_ER

// Union
%union {
    valor_lexico valor_lexico;
    asd_tree_t* nodo_arvore;
    int tipo_dado;
}

// Tipos dos não-terminais
%type <nodo_arvore> programa lista elemento declaracao_funcao
%type <nodo_arvore> cabecalho_funcao lista_parametros_opcional lista_parametros parametros parametro
%type <nodo_arvore> bloco_de_comandos sequencia_comandos comando matched_statement unmatched_statement
%type <nodo_arvore> outro_comando atribuicao chamada_funcao retorno repeticao
%type <nodo_arvore> expressao expr_logica_ou expr_logica_e expr_igualdade expr_relacional
%type <nodo_arvore> expr_aditiva expr_multiplicativa expr_unaria fator literal argumentos
%type <tipo_dado> tipo_num
%type <nodo_arvore> declaracao_variavel

%%

programa: lista ';' { arvore = $1; }
        | %empty    { arvore = NULL; }
        ;
        
lista:  elemento           { $$ = $1; }
      | elemento ',' lista { if ($1) { if ($3) asd_add_child($1, $3); $$ = $1; } else $$ = $3; }
      ;

elemento: declaracao_variavel { $$ = $1; }
        | declaracao_funcao   { $$ = $1; }
        ;
        
declaracao_variavel: TK_VAR TK_ID TK_ATRIB tipo_num {
                         add_symbol($2.valor, $2.numero_linha, NATURE_VARIABLE, $4, NULL);
                         free($2.valor);
                         $$ = NULL;
                    }
                   | TK_VAR TK_ID TK_ATRIB tipo_num TK_COM literal {
                         add_symbol($2.valor, $2.numero_linha, NATURE_VARIABLE, $4, NULL);
                         if ($4 != $6->data_type) semantic_error(ERR_WRONG_TYPE, $2.numero_linha, "Tipo do literal de inicialização é incompatível com a variável.");
                         $$ = asd_new(":=");
                         asd_tree_t* id_node = asd_new($2.valor);
                         id_node->data_type = $4;
                         asd_add_child($$, id_node);
                         asd_add_child($$, $6);
                         free($2.valor);
                   };

declaracao_funcao: cabecalho_funcao bloco_de_comandos {
                        $$ = $1;
                        if ($2) asd_add_child($$, $2);
                        pop_scope(); // Fim do escopo da função
                        current_function = NULL; // Limpa a referência para a função atual
                   };

cabecalho_funcao: TK_ID TK_SETA tipo_num lista_parametros_opcional TK_ATRIB {
                        // Ação Semântica: Adiciona a função ao escopo PAI e armazena os parâmetros
                        symbol_t* func_symbol = add_symbol($1.valor, $1.numero_linha, NATURE_FUNCTION, $3, $4);
                        current_function = func_symbol; // Define a função atual para validação de retorno
                        
                        $$ = asd_new($1.valor);
                        $$->data_type = $3;
                        if($4) asd_add_child($$, $4);
                        free($1.valor);
                  }
                  '[' { push_scope(); // Início do escopo da função, após os parâmetros serem adicionados ao escopo
                        // Adiciona os parâmetros ao novo escopo (escopo da função)
                        if (current_function && current_function->params) {
                            param_t* p = current_function->params;
                            while(p) {
                                add_symbol(p->key, current_function->line, NATURE_VARIABLE, p->type, NULL);
                                p = p->next;
                            }
                        }
                      }
                ;


lista_parametros_opcional: lista_parametros { $$ = $1; }
                         | %empty		    { $$ = NULL; }
                         ;

lista_parametros: TK_COM parametros { $$ = $2; }
                | parametros		{ $$ = $1; }
                ;

parametros: parametro                { $$ = $1; }
          | parametro ',' parametros { asd_add_child($1, $3); $$ = $1; }
          ;

parametro: TK_ID TK_ATRIB tipo_num {
               $$ = asd_new($1.valor);
               $$->data_type = $3;
               free($1.valor);
           };


bloco_de_comandos: '[' { push_scope(); } ']'            { pop_scope(); $$ = NULL; }
                 | '[' { push_scope(); } sequencia_comandos ']' { pop_scope(); $$ = $3; }
                 ;

sequencia_comandos: comando                 { $$ = $1; }
                  | comando sequencia_comandos { if ($1) { if ($2) asd_add_child($1, $2); $$ = $1; } else $$ = $2; }
                  ;

comando: matched_statement   { $$ = $1; }
       | unmatched_statement { $$ = $1; }
       ;
       
matched_statement: TK_SE '(' expressao ')' matched_statement TK_SENAO matched_statement {
                        $$ = asd_new("se");
                        asd_add_child($$, $3); 
                        if ($5) asd_add_child($$, $5);
                        if ($7) asd_add_child($$, $7);
                   }
                 | outro_comando { $$ = $1; }
                 ;

unmatched_statement: TK_SE '(' expressao ')' comando {
                        $$ = asd_new("se");
                        asd_add_child($$, $3); 
                        if ($5) asd_add_child($$, $5);
                   }
                   | TK_SE '(' expressao ')' matched_statement TK_SENAO unmatched_statement {
                        $$ = asd_new("se");
                        asd_add_child($$, $3);
                        if ($5) asd_add_child($$, $5);
                        if ($7) asd_add_child($$, $7);
                   }
                   ;

outro_comando: bloco_de_comandos | declaracao_variavel | atribuicao | chamada_funcao | retorno | repeticao { $$ = $1; };

literal: TK_LI_INTEIRO { $$ = asd_new($1.valor); $$->data_type = TYPE_INTEGER; free($1.valor); }
	   | TK_LI_DECIMAL { $$ = asd_new($1.valor); $$->data_type = TYPE_FLOAT; free($1.valor); } 
       ;

atribuicao: TK_ID TK_ATRIB expressao { 
                symbol_t* symbol = find_symbol($1.valor);
                if (!symbol) semantic_error(ERR_UNDECLARED, $1.numero_linha, $1.valor);
                if (symbol->nature != NATURE_VARIABLE) semantic_error(ERR_FUNCTION, $1.numero_linha, $1.valor);
                if (symbol->type != $3->data_type) semantic_error(ERR_WRONG_TYPE, $1.numero_linha, "Tipo da expressão incompatível com a variável.");
                $$ = asd_new(":=");
                asd_tree_t* id_node = asd_new($1.valor);
                id_node->data_type = symbol->type;
                asd_add_child($$, id_node); 
                asd_add_child($$, $3);     
                free($1.valor);
            };

chamada_funcao: TK_ID '(' ')' {
                    symbol_t* symbol = find_symbol($1.valor);
                    if (!symbol) semantic_error(ERR_UNDECLARED, $1.numero_linha, $1.valor);
                    if (symbol->nature != NATURE_FUNCTION) semantic_error(ERR_VARIABLE, $1.numero_linha, $1.valor);
                    if (symbol->params != NULL) semantic_error(ERR_MISSING_ARGS, $1.numero_linha, $1.valor); // Esperava argumentos, não recebeu nenhum
                    
                    char label[256];
                    sprintf(label, "call %s", $1.valor);
                    $$ = asd_new(label);
                    $$->data_type = symbol->type;
                    free($1.valor);
              }
              | TK_ID '(' argumentos ')' {
                    symbol_t* symbol = find_symbol($1.valor);
                    if (!symbol) semantic_error(ERR_UNDECLARED, $1.numero_linha, $1.valor);
                    if (symbol->nature != NATURE_FUNCTION) semantic_error(ERR_VARIABLE, $1.numero_linha, $1.valor);
                    
                    // --- VALIDAÇÃO COMPLETA DE ARGUMENTOS ---
                    param_t* current_param = symbol->params;
                    asd_tree_t* current_arg_node = $3;
                    int arg_count = 0;
                    
                    // Percorre argumentos e parâmetros simultaneamente
                    while (current_arg_node != NULL && current_param != NULL) {
                        asd_tree_t* arg = current_arg_node->children[0];
                        if (arg->data_type != current_param->type) {
                            semantic_error(ERR_WRONG_TYPE_ARGS, $1.numero_linha, $1.valor);
                        }
                        arg_count++;
                        current_param = current_param->next;
                        current_arg_node = (current_arg_node->number_of_children > 1) ? current_arg_node->children[1] : NULL;
                    }

                    // Verifica se sobraram argumentos ou parâmetros
                    if (current_arg_node != NULL) semantic_error(ERR_EXCESS_ARGS, $1.numero_linha, $1.valor);
                    if (current_param != NULL) semantic_error(ERR_MISSING_ARGS, $1.numero_linha, $1.valor);
                    // --- FIM DA VALIDAÇÃO ---

                    char label[256];
                    sprintf(label, "call %s", $1.valor);
                    $$ = asd_new(label);
                    $$->data_type = symbol->type;
                    asd_add_child($$, $3); 
                    free($1.valor);
              }
              ;
              
argumentos: expressao                { $$ = asd_new("arg_list"); asd_add_child($$, $1); }
          | expressao ',' argumentos { asd_add_child($1, $3); $$ = $1; }
          ;

retorno: TK_RETORNA expressao TK_ATRIB tipo_num {
            // --- VALIDAÇÃO DO TIPO DE RETORNO ---
            if (!current_function) {
                semantic_error(ERR_WRONG_TYPE, get_line_number(), "Comando de retorno fora de uma função.");
            }
            if ($2->data_type != current_function->type) {
                char msg[256];
                sprintf(msg, "Tipo de retorno da função '%s' é incompatível.", current_function->key);
                semantic_error(ERR_WRONG_TYPE, get_line_number(), msg);
            }
            if ($4 != $2->data_type) {
                semantic_error(ERR_WRONG_TYPE, get_line_number(), "Tipo especificado no retorno é incompatível com a expressão retornada.");
            }
            $$ = asd_new("retorna");
            asd_add_child($$, $2);
         };

repeticao: TK_ENQUANTO '(' expressao ')' bloco_de_comandos {	
                $$ = asd_new("enquanto");
                asd_add_child($$, $3);
                if ($5) asd_add_child($$, $5);
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
           symbol_t* symbol = find_symbol($1.valor);
           if (!symbol) semantic_error(ERR_UNDECLARED, $1.numero_linha, $1.valor);
           if (symbol->nature != NATURE_VARIABLE) semantic_error(ERR_FUNCTION, $1.numero_linha, $1.valor);
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
void check_types(asd_tree_t* node, asd_tree_t* child1, asd_tree_t* child2) {
    if (child1->data_type == TYPE_UNDEFINED || child2->data_type == TYPE_UNDEFINED) {
        node->data_type = TYPE_UNDEFINED;
        return;
    }
    if (child1->data_type != child2->data_type) {
        semantic_error(ERR_WRONG_TYPE, get_line_number(), "Operação com tipos incompatíveis (int e float).");
    }
    node->data_type = child1->data_type;
}
