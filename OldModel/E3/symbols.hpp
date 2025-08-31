//Aluno: Miguel Dutra Fontes Guerra
//Cartão UFRGS: 00342573

#ifndef SYMBOL_HPP
#define SYMBOL_HPP

#include <string>

using namespace std;

enum SymbolType{
    SYMBOL_LIT_INT, SYMBOL_LIT_CHAR, SYMBOL_LIT_REAL, SYMBOL_LIT_STRING, SYMBOL_ID
};

struct SYMBOL
{
    int type;
    string text;

    public:
    SYMBOL(int t, string s): type(t), text(s) {};
};

SYMBOL* symbolInsert(int type,char* text);
void symbolPrintTable();

#endif // SYMBOL_HPP
