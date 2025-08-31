//Aluno: Miguel Dutra Fontes Guerra
//Cartão UFRGS: 00342573

#include <vector>
#include "tac.hpp"
#include "ast.hpp"

#define MAX_SONS 4


string TACTypenames[] = {
    "TAC_UNKNOWN",
    "TAC_SYMBOL",
    "TAC_ADD", "TAC_SUB", "TAC_MUL", "TAC_DIV",
    "TAC_NOT", "TAC_AND", "TAC_OR", 
    "TAC_GRT", "TAC_GE", "TAC_LESS", "TAC_LE", "TAC_EQUAL", "TAC_DIF",
    
    "TAC_COPY",
    "TAC_VET_STORE",
    "TAC_VET_LOAD",
    


    "TAC_JFALSE", "TAC_LABEL", "TAC_JUMP",
    "TAC_BEGINFUN", "TAC_ENDFUN", "TAC_CALL", "TAC_ARG",
    "TAC_RET","TAC_PRINT","TAC_READ" 
};


// FUNÇÕES DE PRINT DA TAC

void tacPrintSingle(TAC* tac)
{
    if (!tac) return;

    const char* typeName = "TAC_INVALID";
    if (tac->type >= 0 && tac->type < (int)(sizeof(TACTypenames)/sizeof(string))) {
        typeName = TACTypenames[tac->type].c_str();
    }

    if(!(tac->type == TAC_SYMBOL))
    {
        fprintf(stderr, "TAC(%s,%s,%s,%s)\n",
            typeName,
            (tac->res) ? tac->res->text.c_str() : "",
            (tac->op1) ? tac->op1->text.c_str() : "",
            (tac->op2) ? tac->op2->text.c_str() : ""
        );
    }
}



void tacPrintBackwards(TAC* tac)
{
    fprintf(stderr, "\nTAC:\n\n");
    for(;tac;tac = tac->prev)
        tacPrintSingle(tac);
}

// ============================================================================================================================

// FUNÇÕES AUXILIARES DE CONSTRUÇÃO DAS TACS
TAC* makeFunc(AST* node, TAC* code1)
{
    // Cria TAC de início da função
            TAC* beginFunc = new TAC(TAC_BEGINFUN, node->symbol, nullptr, nullptr);
            
            // Cria TAC de fim da função
            TAC* endFunc = new TAC(TAC_ENDFUN, node->symbol, nullptr, nullptr);
            
            // Junta: início + código do corpo da função + fim
            // Assumindo que o corpo da função está em code[1] (após os parâmetros)
            return tacJoin(beginFunc, tacJoin(code1, endFunc));
}



TAC* makeCall(SYMBOL* function, TAC* args)
{
    // Criar TAC para chamada de função
    SYMBOL* temp = makeTemp();
    TAC* call = new TAC(TAC_CALL, temp, function, nullptr);
    
    if (args) {
        return tacJoin(args, call);
    }
    return call;
}



// 2. ARGUMENTOS DE FUNÇÃO
TAC* makeArg(TAC* codeExpr)
{
    if (!codeExpr) return nullptr;
    
    TAC* arg = new TAC(TAC_ARG, codeExpr->res, nullptr, nullptr);
    return tacJoin(codeExpr, arg);
}



TAC* makeBinOp(int tacType, TAC* code0, TAC* code1)
{
    if (!code0 || !code1)
    {
        fprintf(stderr, "Erro: operandos ausentes em operação binária %s\n", TACTypenames[tacType].c_str());
        exit(1);
    }
    SYMBOL* temp = makeTemp();
    TAC* op = new TAC(tacType, temp, code0->res, code1->res);
    return tacJoin(tacJoin(code0, code1), op);
}

TAC* makeIfThen(TAC* code0, TAC* code1)
{
    TAC* jumptac = nullptr;
    TAC* labeltac = nullptr;
    SYMBOL* newlabel = nullptr;

    newlabel = makeLabel(); // FAZER ESTA FUNCAO

    jumptac = new TAC(TAC_JFALSE,newlabel, code0->res, nullptr);
    jumptac->prev = code0;

    labeltac = new TAC(TAC_LABEL,newlabel, nullptr, nullptr);
    labeltac->prev = code1;
    
    return tacJoin(jumptac,labeltac);
}



TAC* makeIfThenElse(TAC* codeCond, TAC* codeThen, TAC* codeElse)
{
    SYMBOL* labelElse = makeLabel();
    SYMBOL* labelEnd = makeLabel();

    TAC* tacJFalse = new TAC(TAC_JFALSE, labelElse, codeCond->res, nullptr);
    TAC* tacJumpEnd = new TAC(TAC_JUMP, labelEnd, nullptr, nullptr);
    TAC* tacLabelElse = new TAC(TAC_LABEL, labelElse, nullptr, nullptr);
    TAC* tacLabelEnd = new TAC(TAC_LABEL, labelEnd, nullptr, nullptr);

    return tacJoin(
        codeCond,
        tacJoin(
            tacJFalse,
            tacJoin(
                codeThen,
                tacJoin(
                    tacJumpEnd,
                    tacJoin(
                        tacLabelElse,
                        tacJoin(
                            codeElse,
                            tacLabelEnd
                        )
                    )
                )
            )
        )
    );
}


TAC* makeWhile(TAC* codeCond, TAC* codeBody)
{
    SYMBOL* labelStart = makeLabel();
    SYMBOL* labelEnd = makeLabel();

    TAC* tacLabelStart = new TAC(TAC_LABEL, labelStart, nullptr, nullptr);
    TAC* tacJFalse = new TAC(TAC_JFALSE, labelEnd, codeCond->res, nullptr);
    TAC* tacJumpBack = new TAC(TAC_JUMP, labelStart, nullptr, nullptr);
    TAC* tacLabelEnd = new TAC(TAC_LABEL, labelEnd, nullptr, nullptr);

    return tacJoin(
        tacLabelStart,
        tacJoin(
            codeCond,
            tacJoin(
                tacJFalse,
                tacJoin(
                    codeBody,
                    tacJoin(
                        tacJumpBack,
                        tacLabelEnd
                    )
                )
            )
        )
    );
}



TAC* makeDoWhile(TAC* codeBody, TAC* codeCond)
{
    SYMBOL* labelStart = makeLabel();
    SYMBOL* labelEnd = makeLabel();

    TAC* tacLabelStart = new TAC(TAC_LABEL, labelStart, nullptr, nullptr);
    TAC* tacJFalse = new TAC(TAC_JFALSE, labelEnd, codeCond->res, nullptr);
    TAC* tacJumpBack = new TAC(TAC_JUMP, labelStart, nullptr, nullptr);
    TAC* tacLabelEnd = new TAC(TAC_LABEL, labelEnd, nullptr, nullptr);

    return tacJoin(
        tacLabelStart,
        tacJoin(
            codeBody,
            tacJoin(
                codeCond,
                tacJoin(
                    tacJFalse,
                    tacJoin(
                        tacJumpBack,
                        tacLabelEnd
                    )
                )
            )
        )
    );
}



TAC* makePrint(TAC* codeExpr)
{   
    return tacJoin(codeExpr, new TAC(TAC_PRINT, codeExpr->res, nullptr, nullptr));
}


TAC* makePrintList(TAC* codeExpr, TAC* nextPrintList) {
    TAC* printTac = new TAC(TAC_PRINT, codeExpr->res, nullptr, nullptr);    
    return tacJoin(codeExpr, tacJoin(printTac, nextPrintList));
}



TAC* makeRead(SYMBOL* target)
{
    // Debug: verifica se target é válido
    if (!target) {
        fprintf(stderr, "ERRO: makeRead chamado com target nullptr\n");
        return nullptr;
    }
    return new TAC(TAC_READ, target, nullptr, nullptr);
}

TAC* makeReturn(TAC* codeExpr)
{
    return tacJoin(codeExpr, new TAC(TAC_RET, codeExpr ? codeExpr->res : nullptr, nullptr, nullptr));
}



TAC* makeVetAssignment(SYMBOL* vetor, TAC* codeIndex, TAC* codeValue)
{
    // você pode criar um tipo de TAC próprio, ex: TAC_VECSTORE
    return tacJoin(
        tacJoin(codeIndex, codeValue),
        new TAC(TAC_VET_STORE, vetor, codeIndex->res, codeValue->res)  // customizado
    );
}



TAC* makeVetAccess(SYMBOL* vetor, TAC* codeIndex) {
    SYMBOL* temp = makeTemp();
    return tacJoin(
        codeIndex,
        new TAC(TAC_VET_LOAD, temp, vetor, codeIndex->res)
    );
}



TAC* tacJoin(TAC* l1, TAC* l2)
{
    TAC* t;
    if(!l1) return l2;
    if(!l2) return l1;
    for(t=l2; t->prev; t= t->prev)
        ;
    t->prev = l1;
    return l2;
}

// ============================================================================================================================


TAC* generateCode(AST* node)
{
    if (!node) return nullptr;

    TAC* result = nullptr;
    TAC* code[MAX_SONS] = {nullptr};

    int i = 0;
    for (auto s : node->children)
        code[i++] = generateCode(s);

    switch (node->type)
    {

        // BEGINFUN E ENDFUN
        case AST_INT_FUNDEC:
        case AST_BYTE_FUNDEC:
        case AST_REAL_FUNDEC:
            result = makeFunc(node,code[1]);
            break;

        // SIMBOLOS (NÃO SERÃO PRINTADOS)
        case AST_SYMBOL:
            result = new TAC(TAC_SYMBOL, node->symbol, nullptr, nullptr);
            break;

        case AST_SYMBOL_VEC:
            // Para acessos como vet[2] (dentro de atribuições ou operações)
            result = makeVetAccess(node->symbol, code[0]);  // code[0] contém o índice
            break;
        


        // OPERAÇÕES ARITMÉTICAS
        case AST_ADD:
            result = makeBinOp(TAC_ADD, code[0], code[1]);
            break;
        case AST_SUB:
            result = makeBinOp(TAC_SUB, code[0], code[1]);
            break;
        case AST_MUL:
            result = makeBinOp(TAC_MUL, code[0], code[1]);
            break;
        case AST_DIV:
            result = makeBinOp(TAC_DIV, code[0], code[1]);
            break;

        // OPERAÇÕES LÓGICAS
        case AST_AND:
            result = makeBinOp(TAC_AND, code[0], code[1]);
            break;
        case AST_OR:
            result = makeBinOp(TAC_OR, code[0], code[1]);
            break;
        case AST_NOT:
            if (!code[0]) {
                fprintf(stderr, "Erro: operando ausente em operação NOT\n");
                exit(1);
            }
            result = tacJoin(code[0], new TAC(TAC_NOT, makeTemp(), code[0]->res, nullptr));
            break;

        // OPERAÇÕES RELACIONAIS
        case AST_EQUAL:
            result = makeBinOp(TAC_EQUAL, code[0], code[1]);
            break;

        case AST_DIF:
            result = makeBinOp(TAC_DIF, code[0], code[1]);
            break;

        case AST_GRT:
            result = makeBinOp(TAC_GRT, code[0], code[1]);
            break;
        case AST_GE:
            result = makeBinOp(TAC_GE, code[0], code[1]);
            break;
        case AST_LE:
            result = makeBinOp(TAC_LE, code[0], code[1]);
            break;
        case AST_LESS:
            result = makeBinOp(TAC_LESS, code[0], code[1]);
            break;

        case AST_ASSIGNMENT:
            result = tacJoin(code[0], new TAC(TAC_COPY, node->symbol, code[0]?code[0]->res:0, nullptr)); // TODO: QUANDO É VETOR TEM QUE GUARDAR O INDICE
            break;
        
        case AST_VET_ASSIGNMENT:
            result = makeVetAssignment(node->symbol, code[0], code[1]);
            break;
        
        case AST_SYMBOL_FUNC: // CHAMADA DE FUNÇÃO
        {
            // Os argumentos estão em code[0] como uma lista encadeada AST_EXP_LIST
            TAC* argsCode = code[0]; // code[0] já contém o código dos argumentos processados
            result = makeCall(node->symbol, argsCode);
        }
        break;

        case AST_EXP_LIST: // LISTA DE EXPRESSÕES (argumentos)
        {
            // Para AST_EXP_LIST: primeiro filho é a expressão, segundo é a próxima lista
            TAC* exprCode = code[0];  // Código da expressão atual
            TAC* nextListCode = code[1]; // Código da próxima lista (se houver)
            
            // Se há uma expressão, cria TAC_ARG para ela
            if (exprCode) {
                TAC* argTac = makeArg(exprCode);
                result = tacJoin(argTac, nextListCode);
            } else {
                result = nextListCode;
            }
        }
        break;


        case AST_IF_THEN:
            result = makeIfThen(code[0], code[1]);
            break;

        case AST_IF_THEN_ELSE:
            result = makeIfThenElse(code[0], code[1], code[2]);
            break;

        case AST_WHILE:
          result = makeWhile(code[0], code[1]);
          break;

        case AST_DO_WHILE:
            result = makeDoWhile(code[0], code[1]);
            break;

      //  case AST_PRINT:
     //       result = makePrint(code[0]);
     //       break;

        case AST_PRINT_LIST: 
        {
            // code[0] = TAC do argumento atual (ex: 'a')
            // code[1] = TAC do resto da lista (ex: 'b, c')
            TAC* currentArg = code[0]; 
            TAC* remainingArgs = code[1]; // Já contém as TACs dos próximos prints
            
            // Se há mais argumentos, processa recursivamente
            if (remainingArgs) {
                result = makePrintList(currentArg, remainingArgs);
            } 
            // Caso base: último argumento
            else {
                result = makePrint(currentArg);
            }
            break;
        }

        
        case AST_READ:
            result = makeRead(node->symbol);
            break;

        case AST_RETURN:
            result = makeReturn(code[0]);
            break;

        // DEFAULT: junta qualquer código restante
        default:
            result = nullptr;
            for (int i = 0; i < MAX_SONS; ++i) {
                if (code[i]) {
                    result = tacJoin(result, code[i]);
                }
            }
            break;
    }

    return result;
}
