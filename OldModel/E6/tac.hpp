//Aluno: Miguel Dutra Fontes Guerra
//Cartão UFRGS: 00342573

#ifndef TAC_HEADER
#define TAC_HEADER

#include <vector>
#include "symbols.hpp"
#include "ast.hpp"

using namespace std;

enum TACTypes {
    TAC_UNKNOWN,
    TAC_SYMBOL,
    TAC_ADD, TAC_SUB, TAC_MUL, TAC_DIV, // EXP. ARITMETICAS
    TAC_NOT, TAC_AND, TAC_OR, // EXP. LOGICAS
    TAC_GRT, TAC_GE, TAC_LESS, TAC_LE, TAC_EQUAL, TAC_DIF, // EXP. RELACIONAIS

    TAC_COPY, // ASSINALAMENTO DE VARIAVEIS
    TAC_VET_STORE,
    TAC_VET_LOAD,

    TAC_JFALSE, TAC_LABEL, TAC_JUMP, // ESTRUTURAS DE CONTROLE
    TAC_BEGINFUN, TAC_ENDFUN, TAC_CALL, TAC_ARG, // FUNÇÕES
    TAC_RET, TAC_PRINT, TAC_READ // FUNÇÕES ESPECIAIS
};

struct TAC
{
    int type;
    SYMBOL* res;
    SYMBOL* op1;
    SYMBOL* op2;
    TAC* prev;
    TAC* next;
    public:
        TAC(int t, SYMBOL* r, SYMBOL* o1, SYMBOL* o2):
            type(t), res(r), op1(o1), op2(o2) {prev=next=0;};
};

void tacPrintSingle(TAC* tac);
void tacPrintBackwards(TAC* tac);

TAC* tacReverse(TAC* tac);

TAC* tacJoin(TAC* l1, TAC* l2);

TAC* generateCode(AST* node);

void generateAsm(TAC* first);
#endif
