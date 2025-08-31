//Aluno: Miguel Dutra Fontes Guerra
//Cartão UFRGS: 00342573

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol.h"

#define HASH_SIZE 997

static Symbol* hashTable[HASH_SIZE];

static int hash(const char* text) {
    int address = 1;
    for (int i = 0; text[i] != '\0'; ++i)
        address = (address * text[i]) % HASH_SIZE + 1;
    return address - 1;
}

void initSymbolTable() {
    for (int i = 0; i < HASH_SIZE; i++)
        hashTable[i] = NULL;
}

Symbol* findSymbol(const char* text) {
    int idx = hash(text);
    Symbol* node = hashTable[idx];
    while (node) {
        if (strcmp(node->text, text) == 0)
            return node;
        node = node->next;
    }
    return NULL;
}

Symbol* insertSymbol(const char* text, int type) {
    Symbol* existing = findSymbol(text);
    if (existing) return existing;

    int idx = hash(text);
    Symbol* node = (Symbol*)malloc(sizeof(Symbol));
    node->text = strdup(text);
    node->type = type;
    node->next = hashTable[idx];
    hashTable[idx] = node;
    return node;
}

void printSymbolTable() {
    for (int i = 0; i < HASH_SIZE; i++) {
        for (Symbol* node = hashTable[i]; node; node = node->next) {
            printf("Symbol: %-20s | Type: %d\n", node->text, node->type);
        }
    }
}

void freeSymbolTable() {
    for (int i = 0; i < HASH_SIZE; i++) {
        Symbol* node = hashTable[i];
        while (node) {
            Symbol* next = node->next;
            free(node->text);
            free(node);
            node = next;
        }
        hashTable[i] = NULL;
    }
}

