/* Augusto Mattei Grohmnann - 550429
 Miguel Dutra Fontes Guerra - 342573 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabela.h"
#include "errors.h"

scope_t *scope_stack = NULL;

// --- Funções da Pilha de Escopos ---

void push_scope() {
    scope_t* new_scope = (scope_t*) malloc(sizeof(scope_t));
    if (!new_scope) {
        fprintf(stderr, "Erro fatal: Falha ao alocar memória para novo escopo.\n");
        exit(1);
    }
    new_scope->symbols = NULL;
    new_scope->next = scope_stack;
    scope_stack = new_scope;
}

void pop_scope() {
    if (scope_stack == NULL) return;

    scope_t* top = scope_stack;
    scope_stack = top->next;

    symbol_t* current_symbol = top->symbols;
    while (current_symbol != NULL) {
        symbol_t* next_symbol = current_symbol->next;
        free(current_symbol->key);
        free(current_symbol);
        current_symbol = next_symbol;
    }
    free(top);
}

void free_all_scopes() {
    while (scope_stack != NULL) {
        pop_scope();
    }
}

// --- Funções da Tabela de Símbolos ---

symbol_t* add_symbol(const char* key, int line, int nature, int type) {
    if (scope_stack == NULL) {
        fprintf(stderr, "Erro fatal: Tentando adicionar símbolo sem escopo.\n");
        exit(1);
    }

    if (nature == NATURE_VARIABLE || nature == NATURE_FUNCTION) {
        if (find_symbol_in_current_scope(key) != NULL) {
            semantic_error(ERR_DECLARED, line, key);
        }
    }
    
    symbol_t* new_symbol = (symbol_t*) malloc(sizeof(symbol_t));
    if (!new_symbol) {
        fprintf(stderr, "Erro fatal: Falha ao alocar memória para novo símbolo.\n");
        exit(1);
    }

    new_symbol->key = strdup(key);
    new_symbol->line = line;
    new_symbol->nature = nature;
    new_symbol->type = type;
    new_symbol->size = (type == TYPE_INTEGER) ? 4 : (type == TYPE_FLOAT) ? 8 : 0;
    new_symbol->params = NULL; 
    
    new_symbol->next = scope_stack->symbols;
    scope_stack->symbols = new_symbol;

    return new_symbol; // Retorna o símbolo criado
}

symbol_t* find_symbol(const char* key) {
    scope_t* current_scope = scope_stack;
    while (current_scope != NULL) {
        symbol_t* current_symbol = current_scope->symbols;
        while (current_symbol != NULL) {
            if (strcmp(current_symbol->key, key) == 0) {
                return current_symbol;
            }
            current_symbol = current_symbol->next;
        }
        current_scope = current_scope->next;
    }
    return NULL; 
}

symbol_t* find_symbol_in_current_scope(const char* key) {
    if (scope_stack == NULL) return NULL;

    symbol_t* current_symbol = scope_stack->symbols;
    while (current_symbol != NULL) {
        if (strcmp(current_symbol->key, key) == 0) {
            return current_symbol;
        }
        current_symbol = current_symbol->next;
    }
    return NULL; 
}

// --- Função de Erro ---

void semantic_error(int error_code, int line, const char* description) {
    fprintf(stderr, "Erro semântico na linha %d: ", line);
    switch(error_code) {
        case ERR_UNDECLARED:
            fprintf(stderr, "Identificador '%s' não declarado.\n", description);
            break;
        case ERR_DECLARED:
            fprintf(stderr, "Identificador '%s' já declarado neste escopo.\n", description);
            break;
        case ERR_VARIABLE:
            fprintf(stderr, "Identificador '%s' é uma variável e não pode ser usado como função.\n", description);
            break;
        case ERR_FUNCTION:
            fprintf(stderr, "Identificador '%s' é uma função e não pode ser usado como variável.\n", description);
            break;
        case ERR_WRONG_TYPE:
            fprintf(stderr, "Tipos incompatíveis na expressão. %s\n", description);
            break;
        case ERR_MISSING_ARGS:
             fprintf(stderr, "Faltam argumentos na chamada da função '%s'.\n", description);
            break;
        case ERR_EXCESS_ARGS:
             fprintf(stderr, "Argumentos em excesso na chamada da função '%s'.\n", description);
            break;
        case ERR_WRONG_TYPE_ARGS:
            fprintf(stderr, "Tipo incorreto para argumento na chamada da função '%s'.\n", description);
            break;
        default:
            fprintf(stderr, "Erro semântico desconhecido (%d) com '%s'.\n", error_code, description);
            break;
    }
    exit(error_code);
}
