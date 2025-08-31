//Aluno: Miguel Dutra Fontes Guerra
//Cartão UFRGS: 00342573

#include "symbols.hpp"
#include <string>
#include <map>

map<string, SYMBOL*> SymbolTable;

string SymbolName[] = {
    "SYMBOL_LIT_INT", "SYMBOL_LIT_CHAR", "SYMBOL_LIT_REAL",
     "SYMBOL_LIT_STRING", "SYMBOL_ID"
};

SYMBOL *symbolInsert(int type,char* text)
{
    if (SymbolTable.find(string(text)) != SymbolTable.end())
    {
        return SymbolTable.find(string(text))->second;
    }

    SYMBOL *newSymbol = new SYMBOL(type, string(text));
    SymbolTable[string(text)] = newSymbol;
    return newSymbol;
}

void symbolPrintTable()
{
    // Percorre a tabela e imprime os símbolos
    for (const auto& entry : SymbolTable)
    {
        printf("Symbol[%s,%s]\n",SymbolName[entry.second->type].c_str(), entry.second->text.c_str());
    }
}
