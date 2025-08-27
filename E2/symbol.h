//Aluno: Miguel Dutra Fontes Guerra
//Cartão UFRGS: 00342573

#ifndef SYMBOL_H
#define SYMBOL_H

#define SYMBOL_LIT_INT     1
#define SYMBOL_LIT_CHAR    2
#define SYMBOL_LIT_REAL    3
#define SYMBOL_LIT_STRING  4
#define SYMBOL_VARIABLE    5
#define SYMBOL_VECTOR      6
#define SYMBOL_FUNCTION    7
#define SYMBOL_IDENTIFIER  8  

typedef struct Symbol {
    char* text;
    int type;
    struct Symbol* next;
} Symbol;

void initSymbolTable();
Symbol* insertSymbol(const char* text, int type);
Symbol* findSymbol(const char* text);
void printSymbolTable();
void freeSymbolTable();

#endif 

