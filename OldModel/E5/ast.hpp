//Aluno: Miguel Dutra Fontes Guerra
//Cartão UFRGS: 00342573

#ifndef AST_HEADER
#define AST_HEADER

#include <vector>
#include "symbols.hpp"


using namespace std;

enum ASTTypes {
     // Comandos Print e Return
     
     AST_PRINT,
     AST_PRINT_LIST,
     AST_RETURN,
     AST_READ,

     // Estruturas básicas
     AST_CMD_BLOCK,
     AST_LDECL,
     AST_UNKNOWN,
     AST_SYMBOL,
     AST_SYMBOL_FUNC,
     AST_SYMBOL_VEC,
     
     // Lista de Parametros para funcoes

     AST_PAR_INT_SYMBOL,
     AST_PAR_BYTE_SYMBOL,
     AST_PAR_REAL_SYMBOL,
     
     // Operadores aritméticos
     AST_ADD, AST_SUB, AST_MUL, AST_DIV,
     
     // Operadores relacionais
     AST_EQUAL, AST_DIF, AST_LESS, AST_GRT, AST_GE, AST_LE,
     
     // Operadores lógicos
     AST_AND, AST_OR, AST_NOT,
     
     // Listas e comandos
     AST_CMD_LIST,
     AST_PARAM_LIST,
     AST_ASSIGNMENT,
     AST_VET_ASSIGNMENT,
     
     // Declarações
     AST_INT_VARDEC, AST_BYTE_VARDEC, AST_REAL_VARDEC,
     AST_INT_FUNDEC, AST_BYTE_FUNDEC, AST_REAL_FUNDEC,
     AST_INT_VETDEC, AST_BYTE_VETDEC, AST_REAL_VETDEC,
     AST_INT_VETDEC_VAZIO, AST_BYTE_VETDEC_VAZIO, AST_REAL_VETDEC_VAZIO,

     // Estruturas de controle
     AST_IF_THEN_ELSE, AST_IF_THEN,
     AST_WHILE, AST_DO_WHILE,
     
     // Expressões
     AST_EXP_LIST,
     AST_PAR_LIST,
     AST_EXPR_VET_ELEM
};

struct AST
{
    int type;
    vector<AST*> children;
    SYMBOL* symbol;

    public:

    AST(int t, vector<AST*> v, SYMBOL* s=nullptr): type(t), children(v), symbol(s) {};
};

void astPrint(AST* node, int level);
void descompile(AST* node, std::ofstream& out, int indent=0);

#endif //AST_HEADER
