//Aluno: Miguel Dutra Fontes Guerra
//Cartão UFRGS: 00342573

#include "symbols.hpp"
#include <string>
#include <map>
#include <vector>
#include <algorithm>

map<string, SYMBOL*> SymbolTable;



string SymbolName[] = {
    "SYMBOL_LIT_INT", "SYMBOL_LIT_CHAR", "SYMBOL_LIT_REAL", "SYMBOL_LIT_STRING",
    "SYMBOL_ID", "SYMBOL_LABEL",
    "VAR",
    "VET",
    "FUNC", "FUNC_PAR"
};



string DataType[] = {
    "NONE", "INT", "CHAR", "BYTE", "REAL", "STRING", "OTHER"
};



SYMBOL *symbolInsert(int type,char* text, int datatype, bool isFunc, int num_par_func, bool isVec,int vecIndex, std::vector<int> type_par_func, std::vector<string> name_par_func)
{
    if (SymbolTable.find(string(text)) != SymbolTable.end())
    {
        return SymbolTable.find(string(text))->second;
    }

    SYMBOL *newSymbol = new SYMBOL(type, string(text), datatype, isFunc, num_par_func, isVec,vecIndex, type_par_func, name_par_func);
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
            fprintf(stderr, "\nErro Semantico: %s não declarado\n", entry.second->text.c_str());
            undeclared++;
        } 
    }
    return undeclared;
}



SYMBOL* makeTemp(void)
{
    static int serialNumber = 0;
    static char buffer[256] = "";
    sprintf(buffer, "______Temp_____var_%d", serialNumber++);
    return symbolInsert(SYMBOL_ID, buffer, SYMBOL_ID, false, 0, false,0, {},{});
}

// COISA DA ETAPA 4
// TODO: TEM ALGUMA COISA DE ERRADO NA ATRIBUIÇÃO DOS TIPOS NA TABELA DE SIMBOLOS
// ESTÁ ATRIBUINDO INT

SYMBOL* makeLabel(void)
{
    static int serialNumber = 0;
    static char buffer[256] = "";
    sprintf(buffer, "______Label_____var_%d", serialNumber++);
    return symbolInsert(SYMBOL_ID, buffer, SYMBOL_LABEL, false, 0, false,0, {},{});
}


// =========================================================================================================


std::string sanitize_literal_name(const std::string& text, const std::string& prefix)
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


// CRIAÇÃO DOS DADOS GLOBAIS (ASSEMBLY)

void setInitialValue(SYMBOL* sym, int value)
{
    sym->initialIntValue = value;
}

void setInitialValue(SYMBOL* sym, float value) 
{
    sym->initialFloatValue = value;
}

void setInitialValue(SYMBOL* sym, char value) 
{
    sym->initialIntValue = value;
}



void printAsm(FILE *fout) 
{   
    fprintf(fout,".section .data\n");
    fprintf(fout,"# DATA SECTION\n");
    
    for (const auto& entry : SymbolTable)
    {   
        // INICIALIZAÇÃO DE FUNÇÕES E SEUS PARÂMETROS
        if (entry.second->isFunc)
        {
            std::string funcName = entry.second->text;
            fprintf(fout, ".globl _%s\n", funcName.c_str());
            
            // Se for a função principal (main)
            if (funcName == "main") {
                fprintf(fout, "_%s:\t.long\t0\n", funcName.c_str());
            }
            // Outras funções
            else {
                fprintf(fout, "_%s:\t.long\t0\t# Função retorna inteiro\n", funcName.c_str());
            }
        }

        // INICIALIZAÇÃO DE PARÂMETROS DE FUNÇÃO
        if (entry.second->type == FUNC_PAR)
        {
            std::string paramName = entry.second->text;
            fprintf(fout, ".globl _%s\n", paramName.c_str());
            
            // Parâmetros inteiros (incluindo byte)

            if (entry.second->datatype == INT || entry.second->datatype == BYTE) {
                fprintf(fout, "_%s:\t.long\t0\t# Parâmetro da função\n", paramName.c_str());
            }
            // Parâmetros float
            else if (entry.second->datatype == REAL) {
                fprintf(fout, "_%s:\t.float\t0.0\t# Parâmetro float da função\n", paramName.c_str());
            }
        }

        // INICIALIZAÇÃO DE VETORES
        
        if (entry.second->isVec)
        {
            std::string name = entry.second->text;
            int size = entry.second->vecIndex;

            fprintf(fout, ".globl _%s\n", name.c_str());

            if (entry.second->datatype == INT)
            {
                fprintf(fout, "_%s:\t.long", name.c_str());

                bool hasInitValues = !entry.second->vecIntValues.empty();

                for (int i = 0; i < size; i++)
                {
                    int value = (hasInitValues && i < (int)entry.second->vecIntValues.size())
                    ? entry.second->vecIntValues[i] : 0;

                    fprintf(fout, " %d", value);
                    if (i < size - 1)
                        fprintf(fout, ",");
                }
                fprintf(fout, "\n");
            }

            // REAL
            else if (entry.second->datatype == REAL)
            {
                fprintf(fout, "_%s:\t.float", name.c_str());

                bool hasInitValues = !entry.second->vecFloatValues.empty();

                for (int i = 0; i < size; i++)
                {
                    float value = (hasInitValues && i < (int)entry.second->vecFloatValues.size()) 
                        ? entry.second->vecFloatValues[i] : 0.0f;

                    fprintf(fout, " %f", value);
                    if (i < size - 1)
                        fprintf(fout, ",");
                }
                fprintf(fout, "\n");
            }
        }

        // INICIALIZAÇÃO DO RESTO
        else 
        {
            // INICIALIZAÇÃO DE VARIAVEIS

            if(entry.second->type == VAR && (entry.second->datatype == INT || entry.second->datatype == BYTE))
            {
                fprintf(fout, ".globl _%s\n", entry.second->text.c_str());

                if(entry.second->initialCharValue != "\0")
                {
                    fprintf(fout, "_%s:\t.long\t%s\n", entry.second->text.c_str(),entry.second->initialCharValue.c_str());
                }
                else
                {
                    fprintf(fout, "_%s:\t.long\t%d\n", entry.second->text.c_str(),entry.second->initialIntValue);
                }
            }

            if(entry.second->type == VAR && entry.second->datatype == REAL)
            {
                fprintf(fout, ".globl _%s\n", entry.second->text.c_str());
                fprintf(fout, "_%s:\t.float\t%f\n", entry.second->text.c_str(),entry.second->initialFloatValue);
                /*size_t slash_pos = value.find('/');
                    float numerator = std::stof(value.substr(0, slash_pos));
                    float denominator = std::stof(value.substr(slash_pos + 1));
                    float float_value = numerator / denominator;
                    */
            }

            
            // INICIALIZAÇÃO DE TEMPS
            if(entry.second->type == SYMBOL_ID)
            {
                fprintf(fout, ".globl _%s\n", entry.second->text.c_str());
                fprintf(fout, "_%s:\t.long\t0\n", entry.second->text.c_str());
            }


            // INICIALIZAÇÃO DE LITERAIS

            // Literais inteiros
            if(entry.second->type == SYMBOL_LIT_INT)
            {
                
                std::string value = entry.second->text;
                // Inverte os dígitos
                std::reverse(value.begin(), value.end());
                // Remove zeros à esquerda do valor invertido
                value.erase(0, value.find_first_not_of('0'));
                if (value.empty()) value = "0"; // Caso o valor original fosse "0"
                
                fprintf(fout, ".globl __%s\n", entry.second->text.c_str());
                fprintf(fout, "__%s:\t.long\t%s\n", entry.second->text.c_str(), value.c_str());
            }
            
            // Literais caracteres
            if(entry.second->type == SYMBOL_LIT_CHAR)
            {   
                std::string symbolName = sanitize_literal_name(entry.second->text, "char_");
                std::string char_value = entry.second->text;

                // remove aspas simples
                if (char_value.length() >= 3 && char_value.front() == '\'' && char_value.back() == '\'')
                    char_value = char_value.substr(1, char_value.length() - 2);

                fprintf(fout, ".globl __%s\n", symbolName.c_str());
                fprintf(fout, "__%s:\t.byte\t%s\n", symbolName.c_str(), entry.second->text.c_str());
            }

            // Literais caracteres
            if(entry.second->type == SYMBOL_LIT_STRING)
            {   
                std::string symbolName = sanitize_literal_name(entry.second->text, "char_");
                std::string char_value = entry.second->text;
                // remove aspas simples
                if (char_value.length() >= 3 && char_value.front() == '\'' && char_value.back() == '\'')
                    char_value = char_value.substr(1, char_value.length() - 2);

                fprintf(fout, ".globl __%s\n", symbolName.c_str());
                fprintf(fout, "__%s:\t.string\t%s\n", symbolName.c_str(), entry.second->text.c_str());
            }

            // Literais reais
            if(entry.second->type == SYMBOL_LIT_REAL)
            {   
                std::string value = entry.second->text;
                
                std::string label_name = value;
                std::replace(label_name.begin(), label_name.end(), '/', ' '); // Troca '/' por espaço temporariamente
                size_t pos;
                while ((pos = label_name.find(' ')) != std::string::npos)
                    label_name.replace(pos, 1, "barra");

                if (value.find('/') != std::string::npos)
                {
                    size_t slash_pos = value.find('/');
                    float numerator = std::stof(value.substr(0, slash_pos));
                    float denominator = std::stof(value.substr(slash_pos + 1));
                    float float_value = numerator / denominator;
                    
                    char buffer[32];
                    snprintf(buffer, sizeof(buffer), "%.6f", float_value);
                    std::string float_str = buffer;
                    float_str.erase(float_str.find_last_not_of('0') + 1, std::string::npos);
                    if (float_str.back() == '.') 
                        float_str.push_back('0');
                    
                    fprintf(fout, ".globl __%s\n", label_name.c_str());
                    fprintf(fout, "__%s:\t.float\t%s\n", label_name.c_str(), float_str.c_str());
                }
                else {
                    fprintf(fout, ".globl __%s\n", label_name.c_str());
                    fprintf(fout, "__%s:\t.float\t%s\n", label_name.c_str(), value.c_str());
                }
            }
        }
        
    }
}
