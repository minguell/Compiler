/* Augusto Mattei Grohmnann - 550429
 Miguel Dutra Fontes Guerra - 342573 */

#ifndef _TABELA_H_
#define _TABELA_H_

#include "asd.h"
#include "parser.tab.h"

#define TYPE_UNDEFINED 0
#define TYPE_INTEGER   1
#define TYPE_FLOAT     2

// Constantes para a natureza dos símbolos
#define NATURE_UNDEFINED   0
#define NATURE_VARIABLE    1
#define NATURE_FUNCTION    2
#define NATURE_LITERAL     3

typedef struct symbol {
    char* key;
    int line;
    int nature;
    int type;
    int size; 
    int address;
    asd_tree_t* params; // Ponteiro para o nó com a lista de parâmetros
    struct symbol* next;
} symbol_t;

typedef struct scope {
    symbol_t* symbols;
    struct scope* next;
} scope_t;

void push_scope();
void pop_scope();
void free_all_scopes();

// Funções da tabela de símbolos
symbol_t* add_symbol(const char* key, int line, int nature, int type); 
symbol_t* find_symbol(const char* key);
symbol_t* find_symbol_in_current_scope(const char* key);

// Função para tratamento de erros semânticos
void semantic_error(int error_code, int line, const char* description);

#endif // _TABELA_H_
