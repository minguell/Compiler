//Aluno: Miguel Dutra Fontes Guerra
//Cartão UFRGS: 00342573

#include "symbols.hpp"
#include <string>
#include <map>
#include <vector>

map<string, SYMBOL*> SymbolTable;

string SymbolName[] = {
    "SYMBOL_LIT_INT", "SYMBOL_LIT_CHAR", "SYMBOL_LIT_REAL", "SYMBOL_LIT_STRING",
    "SYMBOL_ID",
    "VAR",
    "VET",
    "FUNC", "FUNC_PAR"
};

string DataType[] = {
    "NONE", "INT", "CHAR", "BYTE", "REAL", "STRING", "OTHER"
};
// TODO: IMPLEMENTAR O VECTOR DOS TIPOS DOS PARAMETROS NA TABELA DE SIMBOLOS
SYMBOL *symbolInsert(int type,char* text, int datatype, bool isFunc, int num_par_func, bool isVec, std::vector<int> type_par_func)
{
    if (SymbolTable.find(string(text)) != SymbolTable.end())
    {
        return SymbolTable.find(string(text))->second;
    }

    SYMBOL *newSymbol = new SYMBOL(type, string(text), datatype, isFunc, num_par_func, isVec, type_par_func);
    SymbolTable[string(text)] = newSymbol;
    return newSymbol;
}

void symbolPrintTable()
{
    // Percorre a tabela e imprime os símbolos
    for (const auto& entry : SymbolTable)
    {
        printf("Symbol[%s,%s,%s,%d]\n",SymbolName[entry.second->type].c_str(),
                                    entry.second->text.c_str(),
                                    DataType[entry.second->datatype].c_str(),
                                    entry.second->num_par_func
                                );
    }
}

int checkSymbolsUndeclared()
{
    int undeclared = 0;

    for (const auto& entry : SymbolTable)
    {
        if (entry.second->type == SYMBOL_ID)
        {
            fprintf(stderr, "Erro Semantico: %s não declarado\n", entry.second->text.c_str());
            undeclared++;
        } 
    }
    return undeclared;
}
