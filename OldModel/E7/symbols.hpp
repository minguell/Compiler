//Aluno: Miguel Dutra Fontes Guerra
//Cartão UFRGS: 00342573

#ifndef SYMBOL_HPP
#define SYMBOL_HPP

#include <string>
#include <vector>
#include <stdexcept>


using namespace std;

enum SymbolType{
    SYMBOL_LIT_INT, SYMBOL_LIT_CHAR, SYMBOL_LIT_REAL, SYMBOL_LIT_STRING, // LITERAIS
    SYMBOL_ID, SYMBOL_LABEL,
    VAR,
    VET,    FUNC, FUNC_PAR
};

enum DataType{
    NONE, INT, CHAR, BYTE, REAL, STRING, OTHER
};

struct SYMBOL
{   
    int type;
    string text;
    int datatype;
    bool isFunc;
    int num_par_func;
    bool isVec;
    int vecIndex;
    std::vector<int> type_par_func;
    std::vector<std::string> name_par_func; // NOVO: nomes dos parâmetros da função

    int initialIntValue;    // Para valores inteiros
    float initialFloatValue; // Para valores reais
    string initialCharValue; // Para CHAR

    std::vector<int> vecIntValues;    // Para vetores de INT/BYTE
    std::vector<float> vecFloatValues; // Para vetores de REAL
    

    public:
    SYMBOL(int t, string s, int d, bool isFunc, int n, bool iv,int vi, std::vector<int> type_par_func, std::vector<std::string> name_par_func):
    type(t),
    text(s),
    datatype(d),
    isFunc(isFunc), 
    num_par_func(n), 
    isVec(iv),
    vecIndex(vi), 
    type_par_func(type_par_func),
    name_par_func(name_par_func),
    initialIntValue(0),      // Inicializa com 0
    initialFloatValue(0.0f),  // Inicializa com 0.0
    initialCharValue("\0")
    {};
};

SYMBOL* symbolInsert(int type,char* text, int datatype, bool isFunc, int num_par_func, bool isVec,int vecIndex, std::vector<int> type_par_func, std::vector<string> name_par_func);
void symbolPrintTable();
int checkSymbolsUndeclared();
SYMBOL* makeTemp();
SYMBOL* makeLabel();
void setInitialValue(SYMBOL* sym, int value);
void setInitialValue(SYMBOL* sym, float value);
void setInitialValue(SYMBOL* sym, char value);

void printAsm(FILE *fout);
#endif // SYMBOL_HPP
