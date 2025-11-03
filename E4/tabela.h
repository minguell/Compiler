#ifndef _TABELA_H_
#define _TABELA_H_

#include "asd.h"
#include "parser.tab.h"

// Constantes para os tipos de dados
#define TYPE_UNDEFINED 0
#define TYPE_INTEGER   1
#define TYPE_FLOAT     2
#define TYPE_BOOL      3 

// Constantes para a natureza dos símbolos
#define NATURE_UNDEFINED   0
#define NATURE_VARIABLE    1
#define NATURE_FUNCTION    2
#define NATURE_LITERAL     3

// Estrutura para um único símbolo na tabela
typedef struct symbol {
    char* key;
    int line;
    int nature;
    int type;
    int size; // Para variáveis, tamanho em bytes (int=4, float=8)
    // Para funções, podemos adicionar uma lista de parâmetros aqui
    struct symbol* next;
} symbol_t;

// Estrutura para um escopo (uma tabela de símbolos)
typedef struct scope {
    symbol_t* symbols;
    struct scope* next;
} scope_t;

// Funções da pilha de escopos
void push_scope();
void pop_scope();
void free_all_scopes();

// Funções da tabela de símbolos
void add_symbol(const char* key, int line, int nature, int type);
symbol_t* find_symbol(const char* key);
symbol_t* find_symbol_in_current_scope(const char* key);

// Função para tratamento de erros semânticos
void semantic_error(int error_code, int line, const char* description);

#endif // _TABELA_H_
