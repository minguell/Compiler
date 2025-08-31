//Aluno: Miguel Dutra Fontes Guerra
//Cartão UFRGS: 00342573

#include "semantic.hpp"
#include "symbols.hpp"
#include "funcoes.hpp"

int SemanticErrors = 0;

string ArithmeticsOperators[] = {
    "ADD", "SUB", "MUL", "DIV"
};

string LogicalOperators[] = {
    "AND", "OR", "NOT"
};

string RelationalOperators[] = {
    "EQUAL", "DIF", "LE", "LESS", "GRT", "GEQ"
};



int getNumParFunc(AST *node) {
    if (!node) return 0;
    if (node->type == AST_PAR_LIST || node->type == AST_EXP_LIST) {
        return getNumParFunc(node->children[0]) + getNumParFunc(node->children[1]);
    }
    if (node->type == AST_PAR_INT_SYMBOL || node->type == AST_PAR_BYTE_SYMBOL ||
        node->type == AST_PAR_REAL_SYMBOL || node->type == AST_SYMBOL) {
        return 1;
    }
    return 0;
}



void fillParamTypes(AST *parList, std::vector<int> &types)
{
    if (!parList) return;

    switch (parList->type)
    {
        case AST_PAR_INT_SYMBOL:
            types.push_back(INT);
            break;
        case AST_PAR_BYTE_SYMBOL:
            types.push_back(BYTE);
            break;
        case AST_PAR_REAL_SYMBOL:
            types.push_back(REAL);
            break;
        case AST_PAR_LIST:
            fillParamTypes(parList->children[0], types);
            fillParamTypes(parList->children[1], types);
            break;
    }
}



bool checkExpressionsInt(AST *node) 
{

    if(node->type == AST_SYMBOL || node->type == AST_SYMBOL_FUNC || node->type == AST_SYMBOL_VEC)
    {
        if(node->symbol->datatype == INT || node->symbol->datatype == CHAR)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        for (auto s : node->children)
        {
            if (!s)
                continue; // ou return false, dependendo da semântica do AST
            if (s->type == AST_SYMBOL || s->type == AST_SYMBOL_VEC || s->type == AST_SYMBOL_FUNC) 
            {
                if (s->symbol->datatype != INT && s->symbol->datatype != CHAR) {
                    return false;
                }
            } 
            else 
            {
                if (!checkExpressionsInt(s)) {
                    return false;
                }
            }
        }
    }
    return true;
}



bool checkExpressionsReal(AST *node) // vai retornar um true ou false, true significa que a expressão é um real
{
    for(auto s: node->children)
    {
        if(!s)
            return true;

        // se não for um simbolo, passa adiante
        if(!(s->type == AST_SYMBOL || s->type == AST_SYMBOL_VEC || s->type == AST_SYMBOL_VEC))
        {
            return true && checkExpressionsReal(s);
        }
        // se for um simbolo confere se é real ou não
        else if(s->symbol->datatype == REAL)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    return true;
}



bool checkExpressionsReturn(AST *node, int funType)
{

    if(node->type == AST_RETURN)
    {
        if(node->children[0]->symbol->datatype == funType)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        for (auto s : node->children)
        {
            if (!s)
                continue; // ou return false, dependendo da semântica do AST

            if (s->type == AST_RETURN) {
                if (s->children[0]->symbol->datatype != funType) {
                    return false;
                }
            } else {
                // Recursivamente verifica se todos os nós internos também são INT
                if (!checkExpressionsReturn(s,funType)) {
                    return false;
                }
            }
        }
    }
    return true;
}



void checkAndSetDeclarations(AST *node)
{
    if(!node)
    {
        return;
    }

    switch (node->type)
    {

        case AST_INT_VARDEC:
            if(node->symbol == nullptr)
            {
                fprintf(stderr, "Semantic ERROR: Símbolo não declarado\n");
                SemanticErrors++;
            }
            if(node->symbol->type != SYMBOL_ID)
            {
                fprintf(stderr,"Semantic ERROR: variavel %s já declarada\n", node->symbol->text.c_str());
                SemanticErrors++;
            }
            node->symbol->type = VAR;
            node->symbol->datatype = INT;
            break;

        case AST_BYTE_VARDEC:
            if(node->symbol == nullptr)
            {
                fprintf(stderr, "Semantic ERROR: Símbolo não declarado\n");
                SemanticErrors++;
            }
            if(node->symbol->type != SYMBOL_ID)
            {
                fprintf(stderr,"Semantic ERROR: variavel %s já declarada\n", node->symbol->text.c_str());
                SemanticErrors++;
            }
            node->symbol->type = VAR;
            node->symbol->datatype = BYTE; 
            break;

        case AST_REAL_VARDEC:
            if(node->symbol == nullptr)
            {
                fprintf(stderr, "Semantic ERROR: Símbolo não declarado\n");
                SemanticErrors++;
            }
            if(node->symbol->type != SYMBOL_ID)
            {
                fprintf(stderr,"Semantic ERROR: variavel %s já declarada\n", node->symbol->text.c_str());
                SemanticErrors++;
            }
            node->symbol->type = VAR;
            node->symbol->datatype = REAL;
            
            break;

        case AST_INT_VETDEC:
            if(node->symbol == nullptr)
            {
                fprintf(stderr, "Semantic ERROR: Símbolo não declarado\n");
                SemanticErrors++;
            }
            if(node->symbol->type != SYMBOL_ID)
            {
                fprintf(stderr,"Semantic ERROR: vetor %s já declarada\n", node->symbol->text.c_str());
                SemanticErrors++;
            }
            node->symbol->type = VET;
            node->symbol->datatype = INT;
            node->symbol->isVec = true;
            break;

        case AST_BYTE_VETDEC:
            if(node->symbol == nullptr)
            {
                fprintf(stderr, "Semantic ERROR: Símbolo não declarado\n");
                SemanticErrors++;
            }
            if(node->symbol->type != SYMBOL_ID)
            {
                fprintf(stderr,"Semantic ERROR: vetor %s já declarada\n", node->symbol->text.c_str());
                SemanticErrors++;
            }
            node->symbol->type = VET;
            node->symbol->datatype = BYTE;
            node->symbol->isVec = true;
            break;

        case AST_REAL_VETDEC:
            if(node->symbol == nullptr)
            {
                fprintf(stderr, "Semantic ERROR: Símbolo não declarado\n");
                SemanticErrors++;
            }
            if(node->symbol->type != SYMBOL_ID)
            {
                fprintf(stderr,"Semantic ERROR: vetor %s já declarada\n", node->symbol->text.c_str());
                SemanticErrors++;
            }
            node->symbol->type = VET;
            node->symbol->datatype = REAL;
            node->symbol->isVec = true;
            break;
        
        case AST_INT_VETDEC_VAZIO:
            if(node->symbol == nullptr)
            {
                fprintf(stderr, "Semantic ERROR: Símbolo não declarado\n");
                SemanticErrors++;
            }
            if(node->symbol->type != SYMBOL_ID)
            {
                fprintf(stderr,"Semantic ERROR: vector %s already declared\n", node->symbol->text.c_str());
                SemanticErrors++;
            }
            node->symbol->type = VET;
            node->symbol->datatype = INT;
            node->symbol->isVec = true;
            break;
        
        case AST_BYTE_VETDEC_VAZIO:
            if(node->symbol == nullptr)
            {
                fprintf(stderr, "Semantic ERROR: Símbolo não declarado\n");
                SemanticErrors++;
            }
            if(node->symbol->type != SYMBOL_ID)
            {
                fprintf(stderr,"Semantic ERROR: vetor %s já declarada\n", node->symbol->text.c_str());
                SemanticErrors++;
            }
            node->symbol->type = VET;
            node->symbol->datatype = BYTE;
            node->symbol->isVec = true;
            break;

        case AST_REAL_VETDEC_VAZIO:
            if(node->symbol == nullptr)
            {
                fprintf(stderr, "Semantic ERROR: Símbolo não declarado\n");
                SemanticErrors++;
            }
            if(node->symbol->type != SYMBOL_ID)
            {
                fprintf(stderr,"Semantic ERROR: vetor %s já declarada\n", node->symbol->text.c_str());
                SemanticErrors++;
            }
            node->symbol->type = VET;
            node->symbol->datatype = REAL;
            node->symbol->isVec = true;
            break;

        case AST_INT_FUNDEC: {
            if(node->symbol == nullptr)
            {
                fprintf(stderr, "Semantic ERROR: Símbolo não declarado\n");
                SemanticErrors++;
            }
            if(node->symbol->type != SYMBOL_ID)
            {
                fprintf(stderr,"Semantic ERROR: funcao %s já declarada\n", node->symbol->text.c_str());
                SemanticErrors++;
            }
            node->symbol->type = FUNC;
            node->symbol->datatype = INT;
            node->symbol->num_par_func = getNumParFunc(node->children[0]);
            node->symbol->isFunc = true;

            std::vector<int> types;
            fillParamTypes(node->children[0], types); // node->children[0] = AST_PAR_LIST
            node->symbol->type_par_func = types;
            break;
        }
        case AST_BYTE_FUNDEC: {
            if(node->symbol == nullptr)
            {
                fprintf(stderr, "Semantic ERROR: Símbolo não declarado\n");
                SemanticErrors++;
            }
            if(node->symbol->type != SYMBOL_ID)
            {
                fprintf(stderr,"Semantic ERROR: funcao %s já declarada\n", node->symbol->text.c_str());
                SemanticErrors++;
            }
            node->symbol->type = FUNC;
            node->symbol->datatype = BYTE;
            node->symbol->num_par_func = getNumParFunc(node);
            node->symbol->isFunc = true;

            std::vector<int> types;
            fillParamTypes(node->children[0], types); // node->children[0] = AST_PAR_LIST
            node->symbol->type_par_func = types;
            break;
        }
        case AST_REAL_FUNDEC: {
            if(node->symbol == nullptr)
            {
                fprintf(stderr, "Semantic ERROR: Símbolo não declarado\n");
                SemanticErrors++;
            }
            if(node->symbol->type != SYMBOL_ID)
            {
                fprintf(stderr,"Semantic ERROR: funcao %s já declarada\n", node->symbol->text.c_str());
                SemanticErrors++;
            }
            node->symbol->type = FUNC;
            node->symbol->datatype = REAL;
            node->symbol->num_par_func = getNumParFunc(node);
            node->symbol->isFunc = true;

            std::vector<int> types;
            fillParamTypes(node->children[0], types); // node->children[0] = AST_PAR_LIST
            node->symbol->type_par_func = types;
            break;
        }

        case AST_PAR_INT_SYMBOL:
            node->symbol->type = FUNC_PAR;
            node->symbol->datatype = INT;
            break;
        
        case AST_PAR_BYTE_SYMBOL:
            node->symbol->type = FUNC_PAR;
            node->symbol->datatype = BYTE;
            break;
        
        case AST_PAR_REAL_SYMBOL:
            node->symbol->type = FUNC_PAR;
            node->symbol->datatype = REAL;
            break;

        default:
            break;
    }
    for (auto s: node->children)
        checkAndSetDeclarations(s);
}



void checkUndeclared()
{
    SemanticErrors += checkSymbolsUndeclared();
}



// Funções auxiliares corrigidas
bool isReal(AST *node) {
    if (!node) return false;
    
    // Se for um literal real
    if (node->type == AST_SYMBOL && node->symbol->type == SYMBOL_LIT_REAL) return true;
    
    // Se for um símbolo com tipo real
    return node->symbol && node->symbol->datatype == REAL;
}

bool isInteger(AST *node) {
    if (!node) return false;
    
    // Se for um literal inteiro
    if (node->type == AST_SYMBOL && node->symbol->type == SYMBOL_LIT_INT) return true;
    
    // Se for um símbolo com tipo inteiro
    return node->symbol && (node->symbol->datatype == INT || 
                           node->symbol->datatype == BYTE);
}

bool isChar(AST *node) {
    if (!node) return false;
    
    // Se for um literal char
    if (node->type == AST_SYMBOL && node->symbol->type == SYMBOL_LIT_CHAR) return true;
    
    // Se for um símbolo com tipo char
    return node->symbol && node->symbol->datatype == CHAR;
}

// Função para obter o tipo efetivo de um nó
int getEffectiveType(AST *node) {
    if (!node) return -1;
    
    // Literais
    if (node->type == AST_SYMBOL && node->symbol) {
        if (node->symbol->type == SYMBOL_LIT_INT) return INT;
        if (node->symbol->type == SYMBOL_LIT_REAL) return REAL;
        if (node->symbol->type == SYMBOL_LIT_CHAR) return CHAR;
        
        // Símbolos normais (variáveis, funções, vetores)
        return node->symbol->datatype;
    }
    
    // Expressões aritméticas - retornam o tipo baseado nos operandos
    if (node->type == AST_ADD || node->type == AST_SUB || 
        node->type == AST_MUL || node->type == AST_DIV) {
        AST *left = node->children[0];
        AST *right = node->children[1];
        
        int leftType = getEffectiveType(left);
        int rightType = getEffectiveType(right);
        
        // Se qualquer operando é real, resultado é real
        if (leftType == REAL || rightType == REAL) return REAL;
        // Senão, resultado é inteiro (promove char para int em aritmética)
        return INT;
    }
    
    // Expressões relacionais sempre retornam INT (0 ou 1)
    if (node->type == AST_EQUAL || node->type == AST_DIF || 
        node->type == AST_GE || node->type == AST_GRT ||
        node->type == AST_LE || node->type == AST_LESS) {
        return INT;
    }
    
    // Expressões lógicas sempre retornam INT (0 ou 1)
    if (node->type == AST_AND || node->type == AST_OR || node->type == AST_NOT) {
        return INT;
    }
    
    return -1;
}

bool isValidArithmeticOperand(AST *node) {
    if (!node) return false;
    
    int effectiveType = getEffectiveType(node);
    return effectiveType == INT || effectiveType == REAL || effectiveType == CHAR ||
           effectiveType == BYTE;
}

bool isValidLogicalOperand(AST *node) {
    if (!node) return false;
    
    int effectiveType = getEffectiveType(node);
    // Operações lógicas aceitam qualquer tipo numérico
    return effectiveType == INT || effectiveType == BYTE || effectiveType == CHAR ||
           effectiveType == REAL;
}

bool isValidRelationalOperand(AST *node) {
    if (!node) return false;
    
    int effectiveType = getEffectiveType(node);
    // Operações relacionais aceitam qualquer tipo numérico
    return effectiveType == INT || effectiveType == BYTE || effectiveType == CHAR ||
           effectiveType == REAL;
}

void testArithmeticsCases(AST *node, int operators) {
    AST *left = node->children[0];
    AST *right = node->children[1];
    
    if (!left || !right) {
        fprintf(stderr, "Semantic ERROR: Operandos inválidos para %s\n", 
                ArithmeticsOperators[operators].c_str());
        ++SemanticErrors;
        return;
    }
    
    // Verifica se ambos operandos são válidos para aritmética
    if (!isValidArithmeticOperand(left)) {
        fprintf(stderr, "Semantic ERROR: Operando esquerdo inválido para operação aritmética %s\n", 
                ArithmeticsOperators[operators].c_str());
        ++SemanticErrors;
    }
    
    if (!isValidArithmeticOperand(right)) {
        fprintf(stderr, "Semantic ERROR: Operando direito inválido para operação aritmética %s\n", 
                ArithmeticsOperators[operators].c_str());
        ++SemanticErrors;
    }
    
    int leftType = getEffectiveType(left);
    int rightType = getEffectiveType(right);
    
    // Verifica mistura de tipos (REAL com outros tipos não é permitido)
    if ((leftType == REAL && (rightType == INT || rightType == CHAR || rightType == BYTE)) ||
        (rightType == REAL && (leftType == INT || leftType == CHAR || leftType == BYTE))) {
        fprintf(stderr, "Semantic ERROR: Não pode misturar REAL com INT/CHAR/BYTE em operações aritméticas (%s)\n",
                ArithmeticsOperators[operators].c_str());
        ++SemanticErrors;
    }
}

void testLogicalCases(AST *node, int operators) {
    AST *left = node->children[0];
    AST *right = node->children[1];
    
    // Para operador NOT, só há operando direito (filho[0])
    if (node->type == AST_NOT) {
        if (!left) {
            fprintf(stderr, "Semantic ERROR: Operando inválido para NOT\n");
            ++SemanticErrors;
            return;
        }
        
        if (!isValidLogicalOperand(left)) {
            fprintf(stderr, "Semantic ERROR: Operando inválido para operação lógica NOT\n");
            ++SemanticErrors;
        }
        return;
    }
    
    if (!left || !right) {
        fprintf(stderr, "Semantic ERROR: Operandos inválidos para %s\n", 
                LogicalOperators[operators].c_str());
        ++SemanticErrors;
        return;
    }
    
    int leftType = getEffectiveType(left);
    int rightType = getEffectiveType(right);
    
    // Verifica se ambos operandos são válidos
    if (!isValidLogicalOperand(left)) {
        fprintf(stderr, "Semantic ERROR: Operando esquerdo inválido para operação lógica %s\n", 
                LogicalOperators[operators].c_str());
        ++SemanticErrors;
    }
    
    if (!isValidLogicalOperand(right)) {
        fprintf(stderr, "Semantic ERROR: Operando direito inválido para operação lógica %s\n", 
                LogicalOperators[operators].c_str());
        ++SemanticErrors;
    }
    
    // Verifica mistura de tipos (REAL com outros tipos não é permitido)
    if ((leftType == REAL && (rightType == INT || rightType == CHAR || rightType == BYTE)) ||
        (rightType == REAL && (leftType == INT || leftType == CHAR || leftType == BYTE))) {
        fprintf(stderr, "Semantic ERROR: Não pode misturar REAL com INT/CHAR/BYTE em operações lógicas (%s)\n",
                LogicalOperators[operators].c_str());
        ++SemanticErrors;
    }
}

void testRelationalCases(AST *node, int operators) {
    AST *left = node->children[0];
    AST *right = node->children[1];
    
    if (!left || !right) {
        fprintf(stderr, "Semantic ERROR: Operandos inválidos para %s\n", 
                RelationalOperators[operators].c_str());
        ++SemanticErrors;
        return;
    }
    
    int leftType = getEffectiveType(left);
    int rightType = getEffectiveType(right);
    
    // Verifica se os operandos são válidos para comparação
    if (!isValidRelationalOperand(left)) {
        fprintf(stderr, "Semantic ERROR: Operando esquerdo inválido para operação relacional (%s)\n",
                RelationalOperators[operators].c_str());
        ++SemanticErrors;
    }
    
    if (!isValidRelationalOperand(right)) {
        fprintf(stderr, "Semantic ERROR: Operando direito inválido para operação relacional (%s)\n",
                RelationalOperators[operators].c_str());
        ++SemanticErrors;
    }
    
    // Verifica mistura de tipos incompatíveis (REAL com outros tipos)
    if ((leftType == REAL && (rightType == INT || rightType == CHAR || rightType == BYTE)) ||
        (rightType == REAL && (leftType == INT || leftType == CHAR || leftType == BYTE))) {
        fprintf(stderr, "Semantic ERROR: Não pode misturar REAL com INT/CHAR/BYTE em operações relacionais (%s)\n",
                RelationalOperators[operators].c_str());
        ++SemanticErrors;
    }
}



void checkOperands(AST *node)
{
    if(!node)
    {
        return;
    }
    switch (node->type) 
    {
        // OPERADORES ARITMÉTICOS

        case AST_ADD:

            testArithmeticsCases(node, ADD);
            break;

        case AST_SUB:
            
            testArithmeticsCases(node, SUB);
            break;

        case AST_MUL:

            testArithmeticsCases(node, MUL);
            break;
        
        case AST_DIV:

            testArithmeticsCases(node, DIV);
            break;

        // OPERADORES LÓGICOS

        case AST_AND:

            testLogicalCases(node, AND);
            break;

        case AST_OR:
            testLogicalCases(node, OR);
            break;
        
        case AST_NOT:
            testLogicalCases(node, NOT);
            break;

        // OPERADORES RELACIONAIS

        case AST_EQUAL:
            testRelationalCases(node, EQUAL);
            break;
            
        case AST_DIF:
            testRelationalCases(node, DIF);
            break;

        case AST_GE:
            testRelationalCases(node, GEQ);
            break;

        case AST_GRT:
            testRelationalCases(node, GRT);
            break;
        
        case AST_LE:
            testRelationalCases(node, LE);
            break;

        case AST_LESS:
            testRelationalCases(node, LESS);
            break;
    }
    for (auto s: node->children)
        checkOperands(s);
}



void checkAssignments(AST *node)
{
    if(!node) return;

    if(node->type == AST_ASSIGNMENT)
    {
        int att_datatype = node->symbol->datatype;

        switch(att_datatype)
        {
            case REAL:
                if(checkExpressionsReal(node) == false)
                {
                    fprintf(stderr, "Semantic ERROR: ATRIBUIÇÃO DE TIPOS INCOMPATIVEIS em %s\n", node->symbol->text.c_str());
                    SemanticErrors++;
                }
                break;

            case INT:
            case CHAR:
            case BYTE:
                if(checkExpressionsReal(node) == true)
                {
                    fprintf(stderr, "Semantic ERROR: ATRIBUIÇÃO DE TIPOS INCOMPATIVEIS em %s\n", node->symbol->text.c_str());
                    SemanticErrors++;
                }
                break;
        }
    }
    for (auto s: node->children)
        checkAssignments(s);
}



void checkVariables(AST *node)
{
    if (!node) return;

    if(node->type == AST_SYMBOL)
    {
        if(node->symbol->isFunc == true || node->symbol->isVec == true)
        {
            fprintf(stderr, "Semantic ERROR: identificador %s não é uma variável\n", node->symbol->text.c_str());
            SemanticErrors++;
        }
    }

    for (auto s : node->children)
        checkVariables(s);
}


int countInitValues(AST *node) {
    if (!node) return 0;
    if (node->type == AST_EXPR_VET_ELEM) {
        int count = 0;
        for (auto child : node->children)
            count += countInitValues(child);
        return count;
    }
    return 1;
}



int invertString(string str)
{
    string invertida;
    
    // Passo 1: Inverter a string manualmente
    for (int i = str.size() - 1; i >= 0; --i) {
        invertida += str[i];
    }
    // Passo 2: Converter para inteiro
    int numero_invertido = stoi(invertida);
    return numero_invertido;
}



void checkVectors(AST *node)
{
    if (!node) return;

    switch (node->type)
    {
        case AST_INT_VETDEC:
        case AST_BYTE_VETDEC:
        case AST_REAL_VETDEC:

        if(countInitValues(node->children[1]) > invertString(node->children[0]->symbol->text.c_str()))
        {
            fprintf(stderr, "Semantic ERROR: Há mais elementos em %s do que declarado no indice\n", node->symbol->text.c_str());
            SemanticErrors++;
        }
        case AST_SYMBOL_VEC:

        case AST_INT_VETDEC_VAZIO:
        case AST_BYTE_VETDEC_VAZIO:
        case AST_REAL_VETDEC_VAZIO:
        if (node->symbol->isVec == false)
        {
            fprintf(stderr, "Semantic ERROR: identificador %s não é um vetor e está sendo indexado\n", node->symbol->text.c_str());
            SemanticErrors++;
        }
        else
        {
            if (!checkExpressionsInt(node->children[0]))
            {
                fprintf(stderr, "Semantic ERROR: index de %s não é inteiro\n", node->symbol->text.c_str());
                SemanticErrors++;
            }
        }
            break;
        default:
            break;
    }

    for (auto s : node->children)
        checkVectors(s);
}



void checkReturn(AST *node)
{
    if (!node) return;

    switch (node->type)
    {
        case AST_INT_FUNDEC:
            if (!checkExpressionsReturn(node, INT))
            {
                fprintf(stderr, "Semantic ERROR: Tipo retornado em %s não é compativel com o tipo da função\n", node->symbol->text.c_str());
                SemanticErrors++;
            }
            break;
        case AST_BYTE_FUNDEC:
            if (!checkExpressionsReturn(node, BYTE))
            {
                fprintf(stderr, "Semantic ERROR: Tipo retornado em %s não é compativel com o tipo da função\n", node->symbol->text.c_str());
                SemanticErrors++;
            }
            break;

        case AST_REAL_FUNDEC:

            if (!checkExpressionsReturn(node, REAL))
            {
                fprintf(stderr, "Semantic ERROR: Tipo retornado em %s não é compativel com o tipo da função\n", node->symbol->text.c_str());
                SemanticErrors++;
            }
            break;
        default:
            break;
    }
    for (auto s : node->children)
        checkReturn(s);
}



void checkNumParFunc(AST *node)
{
    if (!node) return;

    switch (node->type)
    {
        case AST_SYMBOL_FUNC:

            if (node->symbol->isFunc == false)
            {
                fprintf(stderr, "Semantic ERROR: identificador %s não é uma função\n", node->symbol->text.c_str());
                SemanticErrors++;
            }
            else
            {
                if (node->symbol->num_par_func != getNumParFunc(node->children[0]))
                {
                    fprintf(stderr, "Semantic ERROR: Quantidade de parametros em %s incompatível\n", node->symbol->text.c_str());
                    SemanticErrors++;
                }
            }
            break;
        default:
            break;
    }
    for (auto s : node->children)
        checkNumParFunc(s);
}



bool isRealAux(AST* node)
{
    if (!node) return false;

    switch (node->type)
    {
        case AST_SYMBOL:
            if (node->symbol && node->symbol->datatype == REAL)
                return true;
            return false;

        // Expressões compostas
        case AST_ADD:
        case AST_SUB:
        case AST_MUL:
        case AST_DIV:
        case AST_LESS:
        case AST_GRT:
        case AST_GE:
        case AST_LE:
        case AST_EQUAL:
        case AST_DIF:
            return isRealAux(node->children[0]) || isRealAux(node->children[1]);

        default:
            // Por padrão, não consideramos real
            return false;
    }
}



void checkTypeParFunc(AST *node) // CHECA SE OS PARAMETROS TEM O MESMO TIPO DOS ARGUMENTOS
{
    if (!node) return;

    if (node->type == AST_SYMBOL_FUNC)
    {
        SYMBOL *funcSymbol = node->symbol; // função chamada
        std::vector<int> expectedTypes = funcSymbol->type_par_func;

        std::vector<AST*> args;
        AST *expList = node->children[0]; // AST_EXP_LIST

        while (expList)
        {
            if (expList->type == AST_EXP_LIST)
            {
                args.push_back(expList->children[0]); // argumento atual
                expList = expList->children[1];      
            }
            else
            {
                args.push_back(expList);
                break;
            }
        }
        for (size_t i = 0; i < args.size(); ++i)
        {
            AST *arg = args[i];
            bool isReal = isRealAux(arg);

            switch (expectedTypes[i])
            {
                case REAL:
                    if (!isReal)
                    {
                        fprintf(stderr,
                                "Semantic ERROR: tipo incompatível no argumento %lu da chamada de '%s': esperado REAL\n",
                                i + 1, funcSymbol->text.c_str());
                        SemanticErrors++;
                    }
                    break;
                case INT:
                case BYTE:
                case CHAR:
                    if (isReal)
                    {
                        fprintf(stderr,
                                "Semantic ERROR: tipo incompatível no argumento %lu da chamada de '%s': não pode ser REAL\n",
                                i + 1, funcSymbol->text.c_str());
                        SemanticErrors++;
                    }
                    break;
            }
        }
    }
    for (auto s : node->children)
        checkTypeParFunc(s);
}
