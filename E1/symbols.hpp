//Aluno: Miguel Dutra Fontes Guerra
//Cartão UFRGS: 00342573

#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

struct SYMBOL {
    int type;
    string text;
    public:
        SYMBOL(int t, string s): type(t), text(s) {};
};

SYMBOL *symbolInsert(int type, char *text);
void printSymbolsTable();
