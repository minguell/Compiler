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

// Funções auxiliares para criar nós da AST
static asd_tree_t* asd_new_binary_op(const char* label, asd_tree_t* child1, asd_tree_t* child2);
static asd_tree_t* asd_new_unary_op(const char* label, asd_tree_t* child);

// Função auxiliar para verificação de tipos em operações binárias
void check_types(asd_tree_t* node, asd_tree_t* child1, asd_tree_t* child2);
void check_function_call_args(symbol_t* func_symbol, asd_tree_t* args_node, int line);
static symbol_t* current_function = NULL;
%}

%code requires {
     #include "asd.h"
     #include "tabela.h"
     extern asd_tree_t *arvore;
     // Estrutura do valor léxico do scanner.l
     typedef struct {
          int numero_linha;
          int token_type;
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
    int tipo_dado; 
}

// Tipos dos não-terminais
%type <nodo_arvore> programa lista elemento declaracao_funcao
%type <nodo_arvore> cabecalho_funcao lista_parametros_opcional lista_parametros parametros parametro
%type <nodo_arvore> bloco_de_comandos sequencia_comandos comando matched_statement unmatched_statement
%type <nodo_arvore> outro_comando atribuicao chamada_funcao retorno repeticao
%type <nodo_arvore> expressao expr_logica_ou expr_logica_e expr_igualdade expr_relacional
%type <nodo_arvore> expr_aditiva expr_multiplicativa expr_unaria fator literal argumentos

// Não-terminais que não geram nós, mas passam informações 
%type <tipo_dado> tipo_num
%type <nodo_arvore> declaracao_variavel 

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

elemento: declaracao_variavel   { $$ = $1; }
        | declaracao_funcao     { $$ = $1; }
        ;
        
declaracao_variavel: TK_VAR TK_ID TK_ATRIB tipo_num {
                         add_symbol($2.valor, $2.numero_linha, NATURE_VARIABLE, $4);
                         free($2.valor);
                         $$ = NULL; // Declaração simples não gera nó na AST
                    }
                   | TK_VAR TK_ID TK_ATRIB tipo_num TK_COM literal {
                         add_symbol($2.valor, $2.numero_linha, NATURE_VARIABLE, $4);
                         
                         if ($4 != $6->data_type) {
                            semantic_error(ERR_WRONG_TYPE, $2.numero_linha, "Tipo do literal de inicialização é incompatível com a variável.");
                         }
                         
                         $$ = asd_new(":=");
                         $$->data_type = $4;
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
                        pop_scope();
                        current_function = NULL;
                   };

cabecalho_funcao: TK_ID TK_SETA tipo_num 
                  {
                      current_function = add_symbol($1.valor, $1.numero_linha, NATURE_FUNCTION, $3);
                      push_scope();
                  }
                  lista_parametros_opcional TK_ATRIB
                  {
                      $$ = asd_new($1.valor);
                      $$->data_type = $3;
                      
                      if($5 != NULL) {
                         asd_add_child($$, $5);
                         if(current_function)
                         {    
                             current_function->params = $5; 
                         }

                      }
                      free($1.valor);
                  }
                ;


lista_parametros_opcional: lista_parametros { $$ = $1; }
                         | %empty		    { $$ = NULL; }
                         ;

lista_parametros: TK_COM parametros { $$ = $2; }
                | parametros		{ $$ = $1; }
                ;

parametros: parametro                { $$ = asd_new("params"); asd_add_child($$, $1); }
          | parametro ',' parametros { asd_add_child($1, $3); $$ = $1; }
          ;

parametro: TK_ID TK_ATRIB tipo_num {
               // Adiciona o parâmetro à tabela de símbolos do escopo atual
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
                        if ($3->data_type != TYPE_INTEGER) {
                            semantic_error(ERR_WRONG_TYPE, get_line_number(), "Expressão de teste do 'se' deve ser do tipo 'inteiro'.");
                        }
                        int then_type;
                        int else_type;
                        if ($5 == NULL) {
                            then_type = TYPE_INTEGER;
                        } else {
                            // Tipo do bloco é o tipo do primeiro comando.
                            then_type = $5->data_type;
                        }
                        if ($7 == NULL) {
                            else_type = TYPE_INTEGER;
                        } else {
                            else_type = $7->data_type;
                        }
                        if (then_type != TYPE_UNDEFINED && 
                            else_type != TYPE_UNDEFINED &&
                            then_type != else_type) {
                            semantic_error(ERR_WRONG_TYPE, get_line_number(), "Tipos dos blocos 'se' e 'senao' são incompatíveis.");
                        }
                        $$ = asd_new("se");
                        $$->data_type = $3->data_type;
                        asd_add_child($$, $3); 
                        if ($5 != NULL) asd_add_child($$, $5);
                        if ($7 != NULL) asd_add_child($$, $7);
                   }
                 | outro_comando { $$ = $1; }
                 ;

unmatched_statement: TK_SE '(' expressao ')' comando {
                        if ($3->data_type != TYPE_INTEGER) {
                            semantic_error(ERR_WRONG_TYPE, get_line_number(), "Expressão de teste do 'se' deve ser do tipo 'inteiro'.");
                        }
                        $$ = asd_new("se");
                        $$->data_type = $3->data_type;
                        asd_add_child($$, $3); 
                        if ($5 != NULL) asd_add_child($$, $5);
                   }
                   | TK_SE '(' expressao ')' matched_statement TK_SENAO unmatched_statement {
                        if ($3->data_type != TYPE_INTEGER) {
                            semantic_error(ERR_WRONG_TYPE, get_line_number(), "Expressão de teste do 'se' deve ser do tipo 'inteiro'.");
                        }
                        $$ = asd_new("se");
                        $$->data_type = $3->data_type;
                        asd_add_child($$, $3);
                        if ($5 != NULL) asd_add_child($$, $5);
                        if ($7 != NULL) asd_add_child($$, $7);
                   }
                   ;

outro_comando: bloco_de_comandos { $$ = $1; }
             | declaracao_variavel { $$ = $1; }
             | atribuicao { $$ = $1; }
             | chamada_funcao { $$ = $1; }
             | retorno { $$ = $1; }
             | repeticao { $$ = $1; }
             ;

literal: TK_LI_INTEIRO { $$ = asd_new($1.valor); $$->data_type = TYPE_INTEGER; add_symbol($1.valor, $1.numero_linha, NATURE_LITERAL, TYPE_INTEGER); free($1.valor); }
	   | TK_LI_DECIMAL { $$ = asd_new($1.valor); $$->data_type = TYPE_FLOAT; add_symbol($1.valor, $1.numero_linha, NATURE_LITERAL, TYPE_FLOAT); free($1.valor); } 
       ;

atribuicao: TK_ID TK_ATRIB expressao { 
                // Verifica declaração e tipos da atribuição
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
                $$->data_type = symbol->type;
                asd_tree_t* id_node = asd_new($1.valor);
                id_node->data_type = symbol->type;
                asd_add_child($$, id_node); 
                asd_add_child($$, $3);     
                free($1.valor);
            };

chamada_funcao: TK_ID '(' ')' {
                    // Verifica a chamada de função sem argumentos
                    symbol_t* symbol = find_symbol($1.valor);
                    if (symbol == NULL) semantic_error(ERR_UNDECLARED, $1.numero_linha, $1.valor);
                    if (symbol->nature != NATURE_FUNCTION) semantic_error(ERR_VARIABLE, $1.numero_linha, $1.valor);
                    
                    // Se a função esperava parâmetros, lança erro.
                    if (symbol->params != NULL && symbol->params->number_of_children > 0) {
                        semantic_error(ERR_MISSING_ARGS, $1.numero_linha, $1.valor);
                    }
                    
                    char label[256];
                    sprintf(label, "call %s", $1.valor);
                    $$ = asd_new(label);
                    $$->data_type = symbol->type;
                    free($1.valor);
                }
              | TK_ID '(' argumentos ')' {
                    symbol_t* symbol = find_symbol($1.valor);
                    if (symbol == NULL) semantic_error(ERR_UNDECLARED, $1.numero_linha, $1.valor);
                    if (symbol->nature != NATURE_FUNCTION) semantic_error(ERR_VARIABLE, $1.numero_linha, $1.valor);
                    
                    if (symbol->params == NULL || symbol->params->number_of_children == 0) {
                        semantic_error(ERR_EXCESS_ARGS, $1.numero_linha, $1.valor);
                    } else {
                        check_function_call_args(symbol, $3, $1.numero_linha);
                    }
                    
                    char label[256];
                    sprintf(label, "call %s", $1.valor);
                    $$ = asd_new(label);
                    $$->data_type = symbol->type;
                    asd_add_child($$, $3); 
                    free($1.valor);
                }
              ;
              
argumentos: expressao                { $$ = asd_new("args"); asd_add_child($$, $1); }
          | expressao ',' argumentos { asd_add_child($1, $3); $$ = $1; }
          ;

retorno: TK_RETORNA expressao TK_ATRIB tipo_num { 
            // Verifica se o tipo do retorno é compatível com o tipo da expressão
            if ($4 != $2->data_type) {
                semantic_error(ERR_WRONG_TYPE, get_line_number(), "Tipo de retorno incompatível com a expressão retornada.");
            }
            if (current_function == NULL) {
                semantic_error(ERR_WRONG_TYPE, get_line_number(), "Comando 'retorna' fora do escopo de uma função.");
            } else if (current_function->type != $4) {
                semantic_error(ERR_WRONG_TYPE, get_line_number(), "Tipo de retorno declarado ('retorna ... := tipo') incompatível com o tipo da função.");
            }
            $$ = asd_new("retorna");
            $$->data_type = $2->data_type;
            asd_add_child($$, $2);
         };

repeticao: TK_ENQUANTO '(' expressao ')' bloco_de_comandos {	
                if ($3->data_type != TYPE_INTEGER) {
                    semantic_error(ERR_WRONG_TYPE, get_line_number(), "Expressão de teste do 'enquanto' deve ser do tipo 'inteiro'.");
                }
                $$ = asd_new("enquanto");
                $$->data_type = $3->data_type;
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
           //  Busca o identificador e anota seu tipo no nó
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


void check_function_call_args(symbol_t* func_symbol, asd_tree_t* args_node, int line) {
    asd_tree_t* param_list = func_symbol->params;    
    int num_params = param_list->number_of_children;
    int num_args = args_node->number_of_children;

    // Verifica contagem de argumentos
    if (num_args < num_params) {
        semantic_error(ERR_MISSING_ARGS, line, func_symbol->key);
    }
    if (num_args > num_params) {
        semantic_error(ERR_EXCESS_ARGS, line, func_symbol->key);
    }

    // Verifica os tipos 
    for (int i = 0; i < num_params; i++) {
        asd_tree_t* current_param = param_list->children[i];
        asd_tree_t* current_arg = args_node->children[i];

        if (current_param->data_type != current_arg->data_type) {
            // Reporta erro especificando o argumento
            char error_msg[256];
            sprintf(error_msg, "Argumento %d na chamada da função '%s' está com tipo errado.", i+1, func_symbol->key);
            semantic_error(ERR_WRONG_TYPE_ARGS, line, error_msg);
        }
    }
}

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
        node->data_type = TYPE_UNDEFINED;
        return;
    }
    // float e int não podem ser misturados
    if (child1->data_type != child2->data_type) {
        semantic_error(ERR_WRONG_TYPE, get_line_number(), "Operação com tipos incompatíveis (int e float).");
    }
    node->data_type = child1->data_type;
}
