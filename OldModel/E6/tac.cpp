//Aluno: Miguel Dutra Fontes Guerra
//Cartão UFRGS: 00342573

#include <vector>
#include <algorithm>
#include "symbols.hpp"
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

// FUNÇÃO DE REVERSÃO DA TAC

TAC* tacReverse(TAC* tac) {
    TAC* t = tac;
    for (t = tac; t->prev; t = t->prev)
        t->prev->next = t;
    return t;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------

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
            result = tacJoin(code[0], new TAC(TAC_COPY, node->symbol, code[0]?code[0]->res:0, nullptr)); 
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

        case AST_PRINT_LIST: 
        {
            TAC* currentArg = code[0]; 
            TAC* remainingArgs = code[1];
            
            if (remainingArgs) {
                result = makePrintList(currentArg, remainingArgs); // Se há mais argumentos, processa recursivamente
            } 
            else {
                result = makePrint(currentArg); // Caso base: último argumento
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

// =====================================================================================

// GERAÇÃO DE CÓDIGO ASM


string resolveSymbol(SYMBOL* symbol) // FUNÇÃO QUE TRATA OS SIMBOLOS, FORMATANDO
{

    switch(symbol->type)
    {
        case SYMBOL_LIT_STRING:
        case SYMBOL_LIT_CHAR:
            if (symbol->text.at(0) == '_')
                return symbol->text;    
            return "_" + symbol->text.substr(1, symbol->text.size()-2);
            break;

        case SYMBOL_LIT_REAL:
        {
            // SUBSTITUI O "/" por "barra"
            std::string label_name = symbol->text;
            std::replace(label_name.begin(), label_name.end(), '/', ' '); // Troca '/' por espaço temporariamente
            size_t pos;
            while ((pos = label_name.find(' ')) != std::string::npos)
                label_name.replace(pos, 1, "barra");

            if (label_name.at(0) == '_')
            {
                return label_name;
            }
            return "_" + label_name;
            break;
        }

        case SYMBOL_LIT_INT:
        {        
            if (symbol->text.at(0) == '_')
            {
                return symbol->text;
            }
            return "_" + symbol->text;
            break;
        }
        default:
            return symbol->text;
    }   
}


std::string sanitize_literal(const std::string& text, const std::string& prefix)
{
    std::string result = prefix;

    for (char c : text) {
        if (isalnum(c)) {
            result += c;
        } else if (c == '\n') {
            result += "nl";  // newline
        } else if (c == ' ') {
            result += "_";
        } else if (c == '\'') {
            // skip quotes in char
        } else if (c == '"') {
            // skip quotes in string
        } else {
            result += "_";  // fallback for special characters
        }
    }
    return result;
}



// TODO: ADICIONAR PRINTS DE FUNÇÃO

void resolvePrint(FILE* fout,SYMBOL* res, string varName, TAC* currentTac)
{   
    // CASO DE RETORNO DE FUNÇÕES
    if (res->type == SYMBOL_ID && currentTac->prev && currentTac->prev->type == TAC_CALL && currentTac->prev->res == res) 
    {    
        // Resultado de chamada de função detectado
        string funcName = currentTac->prev->op1->text;
        
        fprintf(fout, "# PRINT RETORNO DE FUNCAO %s\n", funcName.c_str());
        
        // O resultado já está no registrador eax (para inteiros) ou xmm0 (para floats)
        if (currentTac->prev->op1->datatype == REAL) 
        {
            // Para float, convertemos para double e imprimimos
            fprintf(fout, "\tcvtps2pd\t%%xmm0, %%xmm0\n");
            fprintf(fout, "\tleaq\tprintfloatstr(%%rip), %%rdi\n");
            fprintf(fout, "\tmovl\t$1, %%eax\n");
        } else {
            // Para inteiros (incluindo char), movemos de eax para esi
            fprintf(fout, "\tmovl\t%%eax, %%esi\n");
            fprintf(fout, "\tleaq\tprintintstr(%%rip), %%rdi\n");
            fprintf(fout, "\tmovl\t$0, %%eax\n");
        }
        fprintf(fout, "\tcall\tprintf@PLT\n");
    }


    // CASO DOS VETORES
    if (res->type == SYMBOL_ID && currentTac->prev && currentTac->prev->type == TAC_VET_LOAD && currentTac->prev->res == res) 
    {    
        // Acesso a vetor detectado!
        string vetName = currentTac->prev->op1->text;
        SYMBOL* indexSym = currentTac->prev->op2;
        string indexName = resolveSymbol(indexSym);

        fprintf(fout, "# PRINT VETOR %s[%s]\n", vetName.c_str(), indexName.c_str());
        
        // Gera código de acesso
        if (indexSym->type == SYMBOL_LIT_INT) {
            int offset;
            if (!indexName.empty() && indexName[0] == '_')
            {
                offset = atoi(indexName.substr(1).c_str()) * 4; // Pega do segundo caractere em diante
            } 
            else
            {
                offset = atoi(indexName.c_str()) * 4;
            }
            fprintf(fout, "\tmovl\t_%s+%d(%%rip), %%esi\n", vetName.c_str(), offset);
        } else {
            fprintf(fout, "\tmovl\t_%s(%%rip), %%eax\n", indexName.c_str());
            fprintf(fout, "\tleaq\t_%s(%%rip), %%rdi\n", vetName.c_str());
            fprintf(fout, "\tmovl\t(%%rdi,%%rax,4), %%esi\n");
        }
        
        // Gera código de print
        fprintf(fout, "\tleaq\tprintintstr(%%rip), %%rdi\n");
        fprintf(fout, "\tmovl\t$0, %%eax\n");
        fprintf(fout, "\tcall\tprintf@PLT\n");
    }
    
    // DEMAIS CASOS
    else 
    {
        switch (res->type) 
        {  
            case VAR:
            {
                if(res->datatype == REAL)
                {
                    fprintf(fout,
                        "\tmovss\t_%s(%%rip), %%xmm0\n"
                        "\tcvtps2pd\t%%xmm0, %%xmm0\n"
                        "\tleaq\tprintfloatstr(%%rip), %%rax\n"
                        "\tmovq\t%%rax, %%rdi\n"
                        "\tmovl\t$1, %%eax\n"
                        "\tcall\tprintf@PLT\n"
                        "\tmovl\t$1, %%eax;\n",
                        varName.c_str()
                    );
                }
                else // TRATA CHAR COMO SE FOSSE INT
                {
                    fprintf(fout,
                        "\tmovl\t_%s(%%rip), %%esi\n"
                        "\tleaq\tprintintstr(%%rip), %%rax\n"
                        "\tmovq\t%%rax, %%rdi\n"
                        "\tmovl\t$0, %%eax\n"
                        "\tcall\tprintf@PLT\n"
                        "\tmovl\t$0, %%eax;\n",
                        varName.c_str()
                    );
                }

                break;
            }
            case SYMBOL_LIT_INT:
            {
                fprintf(fout,
                    "\tmovl\t__%s(%%rip), %%esi\n"
                    "\tleaq\tprintintstr(%%rip), %%rax\n"
                    "\tmovq\t%%rax, %%rdi\n"
                    "\tmovl\t$0, %%eax\n"
                    "\tcall\tprintf@PLT\n"
                    "\tmovl\t$0, %%eax;\n",
                    varName.c_str()
                );
                break;
            }
            case SYMBOL_LIT_REAL:
            {
                // float

                std::string varName = res->text;
                std::replace(varName.begin(), varName.end(), '/', ' '); // Troca '/' por espaço temporariamente
                size_t pos;
                while ((pos = varName.find(' ')) != std::string::npos)
                    varName.replace(pos, 1, "barra");


                fprintf(fout,
                    "\tmovss\t__%s(%%rip), %%xmm0\n"
                    "\tcvtps2pd\t%%xmm0, %%xmm0\n"
                    "\tleaq\tprintfloatstr(%%rip), %%rax\n"
                    "\tmovq\t%%rax, %%rdi\n"
                    "\tmovl\t$1, %%eax\n"  // float em xmm0
                    "\tcall\tprintf@PLT\n",
                    varName.c_str()
                );
                break;
            }
            case SYMBOL_LIT_CHAR:
            {
                // char (imprime como caractere)

                varName = sanitize_literal(res->text, "char_");
                fprintf(fout,
                    "\tmovl\t__%s(%%rip), %%esi\n"
                    "\tleaq\tprintcharstr(%%rip), %%rax\n"
                    "\tmovq\t%%rax, %%rdi\n"
                    "\tmovl\t$0, %%eax\n"
                    "\tcall\tprintf@PLT\n",
                    varName.c_str()
                );
                break;
            }
            case SYMBOL_LIT_STRING:
            {
                // string (ponteiro)
                varName = sanitize_literal(res->text, "char_");
                fprintf(fout,
                    "\tleaq\t__%s(%%rip), %%rsi\n"
                    "\tleaq\tprintstringstr(%%rip), %%rax\n"
                    "\tmovq\t%%rax, %%rdi\n"
                    "\tmovl\t$0, %%eax\n"
                    "\tcall\tprintf@PLT\n",
                    varName.c_str()
                );
                break;
            }
            default:
                fprintf(stderr, "Erro: tipo desconhecido para print.\n");
                break;
        }
    }      
}

// CRIAÇÃO DO CÓDIGO (ASSEMBLY)
void generateAsm(TAC* first) 
{
    std::vector<SYMBOL*> argStack;  // Stack temporário para TAC_ARG
    //int insideAuxFunc = 0;

    FILE *fout;
    fout = fopen("out.s", "w");

    // INIT
    fprintf(fout, "# FIXED INIT\n"
                  ".text\n"
                  ".section .rodata\n"
                  "printintstr: .string \"%%d\\n\"\n"
                  "printfloatstr: .string \"%%f\\n\"\n"
                  "printcharstr: .string \"%%c\\n\"\n"
                  "printstringstr: .string \"%%s\\n\"\n"
                  ".text\n");

    // Restante do código (hashtable, TACs, etc.)
    
    
    TAC* tac;

    for(tac = first; tac; tac = tac->next)
    {   
        switch(tac->type) 
        {   
            case TAC_UNKNOWN:
            {
                // Tratamento para código desconhecido
                break;
            }    
            case TAC_SYMBOL:
            {
                // Tratamento para símbolos (variáveis, constantes)
                break;
            }
            /* Operações aritméticas */
            case TAC_ADD:
            {
                // Gera código para adição
                
                string res = resolveSymbol(tac->res);
                string left = resolveSymbol(tac->op1);
                string right = resolveSymbol(tac->op2);
                
                if(tac->op1->datatype == REAL && tac->op2->datatype == REAL)
                {
                    fprintf(fout, "\tmovss\t_%s(%%rip), %%xmm0\n", left.c_str());
                    fprintf(fout, "\taddss\t_%s(%%rip), %%xmm0\n", right.c_str());
                    fprintf(fout, "\tmovss\t%%xmm0, _%s(%%rip)\n", res.c_str());
                }
                else
                {
                    fprintf(fout, "# TAC_ADD\n");
                    fprintf(fout, "\tmovl\t_%s(%%rip), %%edx\n", left.c_str());  // RIP-relative
                    fprintf(fout, "\tmovl\t_%s(%%rip), %%eax\n", right.c_str()); // RIP-relative
                    fprintf(fout, "\taddl\t%%edx, %%eax\n");
                    fprintf(fout, "\tmovl\t%%eax, _%s(%%rip)\n", res.c_str());   // RIP-relative
                }
                break;
            }
            case TAC_SUB:
            {
                // Gera código para subtração
                string res = resolveSymbol(tac->res);
                string left = resolveSymbol(tac->op1);
                string right = resolveSymbol(tac->op2);

                fprintf(fout, "# TAC_SUB\n");

                if(tac->op1->datatype == REAL && tac->op2->datatype == REAL)
                {
                    fprintf(fout, "\tmovss\t_%s(%%rip), %%xmm0\n", left.c_str());
                    fprintf(fout, "\tsubss\t_%s(%%rip), %%xmm0\n", right.c_str());
                    fprintf(fout, "\tmovss\t%%xmm0, _%s(%%rip)\n", res.c_str());
                }
                else
                {
                    fprintf(fout, "\tmovl\t_%s(%%rip),\t%%eax\n", left.c_str());   // eax = left
                    fprintf(fout, "\tsubl\t_%s(%%rip),\t%%eax\n", right.c_str());  // eax -= right
                    fprintf(fout, "\tmovl\t%%eax,\t_%s(%%rip)\n", res.c_str());    // res = eax
                break;
                }
            }
            case TAC_MUL:
            {
                // Gera código para multiplicação
                string res = resolveSymbol(tac->res);
                string left = resolveSymbol(tac->op1);
                string right = resolveSymbol(tac->op2);

                fprintf(fout, "# TAC_MUL\n");
                if(tac->op1->datatype == REAL && tac->op2->datatype == REAL)
                {
                    fprintf(fout, "\tmovss\t_%s(%%rip), %%xmm0\n", left.c_str());
                    fprintf(fout, "\tmulss\t_%s(%%rip), %%xmm0\n", right.c_str());
                    fprintf(fout, "\tmovss\t%%xmm0, _%s(%%rip)\n", res.c_str());
                }
                else
                {
                    fprintf(fout, "\tmovl\t_%s(%%rip),\t%%eax\n", left.c_str());   // eax = left
                    fprintf(fout, "\timull\t_%s(%%rip),\t%%eax\n", right.c_str()); // eax *= right
                    fprintf(fout, "\tmovl\t%%eax,\t_%s(%%rip)\n", res.c_str());    // res = eax
                }
                break;
            }
            case TAC_DIV:
            {
                // Gera código para divisão
                string res = resolveSymbol(tac->res);
                string left = resolveSymbol(tac->op1);
                string right = resolveSymbol(tac->op2);

                fprintf(fout, "# TAC_DIV\n");
                if(tac->op1->datatype == REAL && tac->op2->datatype == REAL)
                {
                    fprintf(fout, "\tmovss\t_%s(%%rip), %%xmm0\n", left.c_str());
                    fprintf(fout, "\tdivss\t_%s(%%rip), %%xmm0\n", right.c_str());
                    fprintf(fout, "\tmovss\t%%xmm0, _%s(%%rip)\n", res.c_str());
                }
                else
                {
                    fprintf(fout, "\tmovl\t_%s(%%rip),\t%%eax\n", left.c_str());    // eax = left (dividendo)
                    fprintf(fout, "\tcltd\n");                               // estende sinal de eax para edx
                    fprintf(fout, "\tidivl\t_%s(%%rip)\n", right.c_str());          // eax = eax / right
                    fprintf(fout, "\tmovl\t%%eax,\t_%s(%%rip)\n", res.c_str());     // res = eax (quociente)
                }
                break;
            }

            /* Operações lógicas */   // ASSINALAR 0 ou 1 nos testes
            case TAC_NOT:
            {
                // Gera código para NOT lógico
                string res = resolveSymbol(tac->res);
                string left = resolveSymbol(tac->op1);  // apenas um operando
                
                fprintf(fout, "# TAC_NOT\n");
                fprintf(fout, "\tmovl\t_%s(%%rip),\t%%eax\n", left.c_str());
                fprintf(fout, "\tcmpl\t$0,\t%%eax\n");
                fprintf(fout, "\tsete\t%%al\n");  // se for igual a 0 → true (1)
                fprintf(fout, "\tmovzbl\t%%al,\t%%eax\n");
                fprintf(fout, "\tmovl\t%%eax,\t_%s(%%rip)\n", res.c_str());
                break;
            }
            case TAC_AND:
            {
                string res = resolveSymbol(tac->res);
                string left = resolveSymbol(tac->op1);
                string right = resolveSymbol(tac->op2);
                
                fprintf(fout, "# TAC_AND\n");
                fprintf(fout, "\tmovl\t_%s,\t%%eax\n", left.c_str());
                fprintf(fout, "\tcmpl\t$0,\t%%eax\n");
                fprintf(fout, "\tsete\t%%al\n");               // al = (left == 0)
                fprintf(fout, "\tmovzbl\t%%al,\t%%ecx\n");     // ecx = (left == 0)

                fprintf(fout, "\tmovl\t_%s,\t%%eax\n", right.c_str());
                fprintf(fout, "\tcmpl\t$0,\t%%eax\n");
                fprintf(fout, "\tsete\t%%al\n");               // al = (right == 0)
                fprintf(fout, "\tmovzbl\t%%al,\t%%eax\n");     // eax = (right == 0)

                fprintf(fout, "\torl\t%%ecx,\t%%eax\n");       // eax = (left == 0) || (right == 0)
                fprintf(fout, "\txorl\t$1,\t%%eax\n");         // eax = !eax → ambos ≠ 0
                fprintf(fout, "\tmovl\t%%eax,\t_%s\n", res.c_str());
                break;
            }
            case TAC_OR:
            {
                string res = resolveSymbol(tac->res);
                string left = resolveSymbol(tac->op1);
                string right = resolveSymbol(tac->op2);
                
                fprintf(fout, "# TAC_OR\n");
                fprintf(fout, "\tmovl\t_%s,\t%%eax\n", left.c_str());
                fprintf(fout, "\tcmpl\t$0,\t%%eax\n");
                fprintf(fout, "\tsetne\t%%al\n");              // al = (left != 0)
                fprintf(fout, "\tmovzbl\t%%al,\t%%ecx\n");     // ecx = (left != 0)

                fprintf(fout, "\tmovl\t_%s,\t%%eax\n", right.c_str());
                fprintf(fout, "\tcmpl\t$0,\t%%eax\n");
                fprintf(fout, "\tsetne\t%%al\n");              // al = (right != 0)
                fprintf(fout, "\tmovzbl\t%%al,\t%%eax\n");     // eax = (right != 0)

                fprintf(fout, "\torl\t%%ecx,\t%%eax\n");       // eax = (left != 0) || (right != 0)
                fprintf(fout, "\tmovl\t%%eax,\t_%s\n", res.c_str());
                break;
            }

            /* Operações relacionais */
            case TAC_GRT:
            {
                // Gera código para maior (>)
                string res = resolveSymbol(tac->res);
                string left = resolveSymbol(tac->op1);
                string right = resolveSymbol(tac->op2);
                
                fprintf(fout, "# TAC_GRT\n");
                fprintf(fout, "\tmovl\t_%s,\t%%eax\n", left.c_str());
                fprintf(fout, "\tcmpl\t_%s,\t%%eax\n", right.c_str());
                fprintf(fout, "\tsetg\t%%al\n");
                fprintf(fout, "\tmovzbl\t%%al,\t%%eax\n");
                fprintf(fout, "\tmovl\t%%eax,\t_%s\n", res.c_str());
                break;
            }
            case TAC_GE:
            {
                // Gera código para maior ou igual (>=)
                string res = resolveSymbol(tac->res);
                string left = resolveSymbol(tac->op1);
                string right = resolveSymbol(tac->op2);

                fprintf(fout, "# TAC_GE\n");
                fprintf(fout, "\tmovl\t_%s,\t%%eax\n", left.c_str());
                fprintf(fout, "\tcmpl\t_%s,\t%%eax\n", right.c_str());
                fprintf(fout, "\tsetge\t%%al\n");
                fprintf(fout, "\tmovzbl\t%%al,\t%%eax\n");
                fprintf(fout, "\tmovl\t%%eax,\t_%s\n", res.c_str());
                break;
            }
            case TAC_LESS:
            {
                // Gera código para menor que (<)
                string res = resolveSymbol(tac->res);
                string left = resolveSymbol(tac->op1);
                string right = resolveSymbol(tac->op2);
                
                fprintf(fout, "# TAC_LESS\n");
                fprintf(fout, "\tmovl\t_%s,\t%%eax\n", left.c_str());
                fprintf(fout, "\tcmpl\t_%s,\t%%eax\n", right.c_str());
                fprintf(fout, "\tsetl\t%%al\n");
                fprintf(fout, "\tmovzbl\t%%al,\t%%eax\n");
                fprintf(fout, "\tmovl\t%%eax,\t_%s\n", res.c_str());
                break;
            }
            case TAC_LE:
            {
                // Gera código para menor ou igual (<=)
                string res = resolveSymbol(tac->res);
                string left = resolveSymbol(tac->op1);
                string right = resolveSymbol(tac->op2);
                
                fprintf(fout, "# TAC_LE\n");
                fprintf(fout, "\tmovl\t_%s,\t%%eax\n", left.c_str());
                fprintf(fout, "\tcmpl\t_%s,\t%%eax\n", right.c_str());
                fprintf(fout, "\tsetle\t%%al\n");
                fprintf(fout, "\tmovzbl\t%%al,\t%%eax\n");
                fprintf(fout, "\tmovl\t%%eax,\t_%s\n", res.c_str());
                break;
            }
            case TAC_EQUAL:
            {
                // Gera código para igualdade (==)
                string res = resolveSymbol(tac->res);
                string left = resolveSymbol(tac->op1);
                string right = resolveSymbol(tac->op2);
                
                fprintf(fout, "# TAC_EQUAL\n");
                fprintf(fout, "\tmovl\t_%s,\t%%eax\n", left.c_str());
                fprintf(fout, "\tcmpl\t_%s,\t%%eax\n", right.c_str());
                fprintf(fout, "\tsete\t%%al\n");
                fprintf(fout, "\tmovzbl\t%%al,\t%%eax\n");
                fprintf(fout, "\tmovl\t%%eax,\t_%s\n", res.c_str());
                break;
            }
            case TAC_DIF:
            {
                // Gera código para diferença (!=)
                string res = resolveSymbol(tac->res);
                string left = resolveSymbol(tac->op1);
                string right = resolveSymbol(tac->op2);

                fprintf(fout, "# TAC_DIF\n");
                fprintf(fout, "\tmovl\t_%s,\t%%eax\n", left.c_str());
                fprintf(fout, "\tcmpl\t_%s,\t%%eax\n", right.c_str());
                fprintf(fout, "\tsetne\t%%al\n");
                fprintf(fout, "\tmovzbl\t%%al,\t%%eax\n");
                fprintf(fout, "\tmovl\t%%eax,\t_%s\n", res.c_str());
                break;
            }

            /* Manipulação de variáveis */


            case TAC_COPY:
            {
                string dest = resolveSymbol(tac->res);
                string src = resolveSymbol(tac->op1); 
                


                // TRATAMENTO DE NOME PARA LITERAIS
                if(tac->op1->type == SYMBOL_LIT_CHAR)
                {
                    src = sanitize_literal(src, "_char");
                }

                // ATRIBUIÇÕES DE LITERAIS (FUNCIONANDO)
                if(tac->res->datatype == REAL && tac->op1->datatype == REAL)
                {
                    fprintf(fout, "# TAC COPY %s = %s\n", dest.c_str(), src.c_str());
                    fprintf(fout, "\tmovss\t_%s(%%rip), %%xmm0\n", src.c_str());
                    fprintf(fout, "\tmovss\t%%xmm0, _%s(%%rip)\n", dest.c_str());
                }
                else
                {
                    fprintf(fout, "# TAC COPY %s = %s\n", dest.c_str(), src.c_str());
                    fprintf(fout, "\tmovl\t_%s(%%rip), %%eax\n", src.c_str());
                    fprintf(fout, "\tmovl\t%%eax, _%s(%%rip)\n", dest.c_str());
                }
                break;


            }
        
            case TAC_VET_STORE:
            {
                string dest = resolveSymbol(tac->res);
                string value = resolveSymbol(tac->op2);

                fprintf(fout, "# TAC_VET_STORE %s[", dest.c_str());
                
                // Tratamento especial para o índice
                if(tac->op1->type == SYMBOL_LIT_INT) {
                    // Para literais, use o valor direto

                    int index_val = stoi(tac->op1->text);
                    fprintf(fout, "%d] = %s\n", index_val, value.c_str());
                    int offset = index_val * 4;
                    fprintf(fout, "\tmovl\t_%s(%%rip), %%eax\n", value.c_str());
                    fprintf(fout, "\tmovl\t%%eax, _%s+%d(%%rip)\n", dest.c_str(), offset);
                } 
                else {
                    // Para variáveis, use o código atual
                    string index = resolveSymbol(tac->op1);
                    fprintf(fout, "%s] = %s\n", index.c_str(), value.c_str());
                    fprintf(fout, "\tmovl\t_%s(%%rip), %%eax\n", index.c_str());
                    fprintf(fout, "\tcltq\n");
                    fprintf(fout, "\tmovl\t_%s(%%rip), %%edx\n", value.c_str());
                    fprintf(fout, "\tleaq\t_%s(%%rip), %%rcx\n", dest.c_str());
                    fprintf(fout, "\tmovl\t%%edx, (%%rcx,%%rax,4)\n");
                }
                break;
            }
            
            case TAC_VET_LOAD:
            {
                // Gera código para carregar de vetor
                string dest = resolveSymbol(tac->res);
                string src = resolveSymbol(tac->op1);
                string index = resolveSymbol(tac->op2);
                
                fprintf(fout, "# TAC_VET_LOAD\n");
                fprintf(fout, "\tmovl\t_%s(%%rip), %%eax\n", index.c_str());             // carrega índice em EAX
                fprintf(fout, "\tleaq\t_%s(%%rip), %%rdi\n", src.c_str());              // carrega endereço base do vetor em RDI
                fprintf(fout, "\tmovl\t(%%rdi,%%rax,4), %%edx\n");                       // edx = vetor[eax]
                fprintf(fout, "\tmovl\t%%edx, _%s(%%rip)\n", dest.c_str());              // dest = edx
                break;
            }

            /* Controle de fluxo */

            // TODO: VERIFICAR
            case TAC_JFALSE:
            {
                // Gera código para jump-if-false (pula se a condição for falsa/0)
                string cond = resolveSymbol(tac->op1);
                string label = resolveSymbol(tac->res);
                
                fprintf(fout, "# TAC_JFALSE (if !%s goto %s)\n", cond.c_str(), label.c_str());
                fprintf(fout, "\tmovl\t_%s(%%rip), %%eax\n", cond.c_str());  // Carrega a condição
                fprintf(fout, "\tcmpl\t$0, %%eax\n");                       // Compara com 0
                fprintf(fout, "\tje\t%s\n", label.c_str());                 // Pula se igual a 0 (false)
                break;
            }


            // TODO: VERIFICAR
            case TAC_LABEL:
            {
                // Gera código para rótulo (label)
                string label = resolveSymbol(tac->res);
                
                fprintf(fout, "# TAC_LABEL %s\n", label.c_str());
                fprintf(fout, "%s:\n", label.c_str());  // Define o label
                break;
            }
            
            // TODO: VERIFICAR
            case TAC_JUMP:
            {
                // Gera código para jump incondicional
                string label = resolveSymbol(tac->res);
                
                fprintf(fout, "# TAC_JUMP (goto %s)\n", label.c_str());
                fprintf(fout, "\tjmp\t%s\n", label.c_str());  // Salto incondicional
                break;
            }

            /* Funções */
            case TAC_BEGINFUN:
            {

                string funcName = tac->res ? tac->res->text : "";

               // if(funcName != "main") insideAuxFunc =true;

                fprintf(fout, "\t# BEGIN_FUN\n");
                fprintf(fout, "\t.globl\t%s\n", funcName.c_str());
                fprintf(fout, "\t.type\t%s, @function\n", funcName.c_str());
                fprintf(fout, "%s:\n", funcName.c_str());
                fprintf(fout, "\tpushq\t%%rbp\n");
                fprintf(fout, "\tmovq\t%%rsp, %%rbp\n");
                //TODO: CRIAR CASO PARA ADICIONAR OS ARGUMENTOS NOS PARAMETROS DA FUNCÃO
                
                if (tac->res && tac->res->isFunc && !tac->res->name_par_func.empty()) 
                {
                    const char* intRegs[] = {"%edi", "%esi", "%edx", "%ecx", "%r8d", "%r9d"};
                    size_t numParams = tac->res->name_par_func.size();

                    for (size_t i = 0; i < numParams && i < 6; ++i) {
                        std::string paramName = tac->res->name_par_func[i];
                        fprintf(fout, "\tmovl\t%s, _%s(%%rip)\n", intRegs[i], paramName.c_str());
                    }

                    if (numParams > 6) {
                        fprintf(stderr, "AVISO: Mais de 6 parâmetros não suportado nos registradores\n");
                        // Aqui você pode empilhar argumentos adicionais, se quiser
                    }
                }

                break;
            }

            case TAC_ENDFUN:
            {
                // Gera epílogo de função

                fprintf(fout, "\t# TAC_ENDFUN\n"
	                        "\tpopq	%%rbp\n"
	                        "\tret\n"
                        );

               // insideAuxFunc = false; // DESATIVA
                break;
            }

            // TODO: VERIFICAR
            case TAC_CALL:
            {
                string funcName = resolveSymbol(tac->op1);
                fprintf(fout, "# TAC_CALL %s\n", funcName.c_str());

                // System V ABI - argumentos inteiros: %edi, %esi, %edx, %ecx, %r8d, %r9d
                const char* intRegs[] = {"%edi", "%esi", "%edx", "%ecx", "%r8d", "%r9d"};
                int argCount = 0;

                // Processa cada argumento da pilha
                for (auto sym : argStack) {
                    if (argCount >= 6) {
                        fprintf(stderr, "Erro: Número de argumentos excede o suportado\n");
                        exit(1);
                    }
                    string argName = resolveSymbol(sym);
                    // Sempre passa como inteiro (adequado para seu caso)
                    fprintf(fout, "\tmovl\t_%s(%%rip), %s\n", argName.c_str(), intRegs[argCount]);
                    argCount++;
                }
                // Chama função
                fprintf(fout, "\tcall\t%s\n", funcName.c_str());
                // Armazena resultado se necessário
                if (tac->res) 
                {
                    string retVar = resolveSymbol(tac->res);
                    fprintf(fout, "\tmovl\t%%eax, _%s(%%rip)\n", retVar.c_str());
                }

                argStack.clear();
                break;
            }



            // TODO: VERIFICAR
            case TAC_ARG:
            {
                // Empilha argumentos para a próxima chamada
                fprintf(fout, "# TAC_ARG\n");
                if (tac->res)
                    argStack.push_back(tac->res);
                break;
            }

            /* Operações especiais */

            // TODO: VERIFICAR
            case TAC_RET:
            {
                fprintf(fout, "# TAC_RET\n");
                
                // Encontrar o TAC_BEGINFUN correspondente
                TAC* func_start = tac;
                while(func_start && func_start->type != TAC_BEGINFUN) {
                    func_start = func_start->prev;
                }
                
                if (tac->res) {
                    string ret = resolveSymbol(tac->res);
                    
                    // Verificar o tipo de retorno da função
                    if (func_start && func_start->res && func_start->res->datatype == REAL) {
                        fprintf(fout, "\tmovss\t_%s(%%rip), %%xmm0\n", ret.c_str());
                    } else {
                        fprintf(fout, "\tmovl\t_%s(%%rip), %%eax\n", ret.c_str());
                    }
                }
                
                fprintf(fout, "\tpopq\t%%rbp\n");
                fprintf(fout, "\tret\n");
                break;
            }

            // TODO: VERIFICAR
            case TAC_PRINT:
            {
                // Gera código para impressão
                fprintf(fout, "# TAC PRINT\n");
                string varName = tac->res ? tac->res->text.c_str() : "unknown";
                resolvePrint(fout, tac->res, varName,tac);

                break;
                   
            }

            // TODO: VERIFICAR
            case TAC_READ:
            {
                // Gera código para leitura de entrada
                break;
            }

            default:
                // Tratamento para casos não previstos
                fprintf(stderr, "Erro: TAC desconhecido (tipo %d)\n", tac->type);
                break;
        }
    }

    printAsm(fout); // ADIÇÃO DOS DADOS (TABELA DE SIMBOLOS)
    fclose(fout);
}
