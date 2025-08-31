//Aluno: Miguel Dutra Fontes Guerra
//Cartão UFRGS: 00342573

#ifndef SEMANTIC_HEADER
#define SEMANTIC_HEADER

#include "symbols.hpp"
#include "ast.hpp"

extern int SemanticErrors;

enum ArithmeticsOperators{
    ADD, SUB, MUL, DIV
};

enum LogicalOperators{
    AND, OR, NOT
};

enum RelationalOperators{
    EQUAL, DIF, LE, LESS, GRT, GEQ
};

int getNumParFunc(AST *node);

void fillParamTypes(AST *parList, std::vector<int> &types);
bool checkExpressionsInt(AST *node);
bool checkExpressionsReal(AST *node);


bool isReal(AST *node);
bool isInteger(AST *node);
bool isValidArithmeticNode(AST *node, bool expectReal);
void testArithmeticsCases(AST *node, int operators); // funcoes auxiliares
void testLogicalCases(AST *node, int operators);     
void testRelationalCases(AST *node, int operators);

void checkAndSetDeclarations(AST *node);
void checkUndeclared();
void checkOperands(AST *node);
void checkAssignments(AST *node);
void checkVariables(AST *node);

int invertString(string str);
void checkVectors(AST *node);

// FUNÇÕES PARA CHECAR RETURN
int checkExpressionsType(AST *node);
bool checkExpressionsReturn(AST *node, int funcType);
void checkReturn(AST *node);


void checkNumParFunc(AST *node);
bool isRealAux(AST *node);
void checkTypeParFunc(AST *node);

#endif //SEMANTIC_HEADER
