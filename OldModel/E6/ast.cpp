//Aluno: Miguel Dutra Fontes Guerra
//Cartão UFRGS: 00342573

#include "symbols.hpp"
#include "ast.hpp" 

#include <string>
#include <stdio.h>
#include <fstream>
#include <iostream>


string ASTTypeNames[] = {

     // Comandos Print e Return
     
    "AST_PRINT",
    "AST_PRINT_LIST",
    "AST_RETURN",
    "AST_READ",
    
    // Estruturas básicas
    "AST_CMD_BLOCK",
    "AST_LDECL",
    "AST_UNKNOWN",
    "AST_SYMBOL",
    "AST_SYMBOL_FUNC",
    "AST_SYMBOL_VEC",

    // Lista de Parametros para funcoes

    "AST_PAR_INT_SYMBOL",
    "AST_PAR_BYTE_SYMBOL",
    "AST_PAR_REAL_SYMBOL",
    
    // Operadores aritméticos
    "AST_ADD", "AST_SUB", "AST_MUL", "AST_DIV",
    
    // Operadores relacionais
    "AST_EQUAL", "AST_DIF", "AST_LESS", "AST_GRT", "AST_GE", "AST_LE",
    
    // Operadores lógicos
    "AST_AND", "AST_OR", "AST_NOT",
    
    // Listas e comandos
    "AST_CMD_LIST",
    "AST_PARAM_LIST",
    "AST_ASSIGNMENT",
    "AST_VET_ASSIGNMENT",
    
    // Declarações
    "AST_INT_VARDEC", "AST_BYTE_VARDEC", "AST_REAL_VARDEC",
    "AST_INT_FUNDEC","AST_BYTE_FUNDEC","AST_REAL_FUNDEC",
    "AST_INT_VETDEC", "AST_BYTE_VETDEC", "AST_REAL_VETDEC",
    "AST_INT_VETDEC_VAZIO", "AST_BYTE_VETDEC_VAZIO", "AST_REAL_VETDEC_VAZIO",
    
    // Estruturas de controle
    "AST_IF_THEN_ELSE", "AST_IF_THEN",
    "AST_WHILE", "AST_DO_WHILE",
    
    // Expressões
    "AST_EXP_LIST",
    "AST_PAR_LIST",
    "AST_EXPR_VET_ELEM"
};


void astPrint(AST* node, int level)
{
    if(!node)
    {
        return;
    }
    
    for(int i=0; i<level;++i)
        fprintf(stderr, "  ");

    fprintf(stderr, "AST: %s, %s \n",
        ASTTypeNames[node->type].c_str(),
        node->symbol? node->symbol->text.c_str() : "");

    for (auto s: node->children)
        astPrint(s, level+1);
}

// LE UMA AST E MONTA UM CÓDIGO FONTE

void descompile(AST* node, std::ofstream& out, int indent)
{
    if (!node) return;

    std::string indentation(indent, ' ');

    switch (node->type) 
    {
        case AST_PRINT:
            out << indentation << "print " << (node->symbol ? node->symbol->text : "") << "";
            descompile(node->children[0], out, 0);
            out << ";\n";
            break;
        
        case AST_PRINT_LIST:
            descompile(node->children[0], out, 0);
            if (node->children[1]) {
                out << " ";
                descompile(node->children[1], out, 0);
            }
            break;

        case AST_RETURN:
            out << indentation << "return ";
            descompile(node->children[0], out, 0);
            out << ";\n";
            break;

        case AST_READ:
            out << indentation << "read " << (node->symbol ? node->symbol->text : "") << ";\n";
            break;

        case AST_CMD_BLOCK:
            out << indentation << "{\n";
            descompile(node->children[0], out, indent + 4);
            out << indentation << "}\n";
            break;

        case AST_CMD_LIST:
            descompile(node->children[0], out, indent);
            descompile(node->children[1], out, indent);
            break;

        case AST_LDECL:
            descompile(node->children[0], out, indent);
            descompile(node->children[1], out, indent);
            break;

        case AST_INT_VARDEC:
        {   
            out << indentation << "int" << " " << (node->symbol ? node->symbol->text : "");
            if (node->children[0]) {
                out << " = ";
                descompile(node->children[0], out, 0);
            }
            out << ";\n";
            break;
        }

        case AST_BYTE_VARDEC:
        {
            out << indentation << "byte" << " " << (node->symbol ? node->symbol->text : "");
            if (node->children[0]) {
                out << " = ";
                descompile(node->children[0], out, 0);
            }
            out << ";\n";
            break;
        }
        case AST_REAL_VARDEC:
        {
            out << indentation << "real" << " " << (node->symbol ? node->symbol->text : "");
            if (node->children[0]) {
                out << " = ";
                descompile(node->children[0], out, 0);
            }
            out << ";\n";
            break;
        }


        case AST_ASSIGNMENT:
            out << indentation << (node->symbol ? node->symbol->text : "") << " = ";
            descompile(node->children[0], out, 0);
            out << ";\n";
            break;

        case AST_VET_ASSIGNMENT:
            out << indentation << (node->symbol ? node->symbol->text : "") << "[";
            descompile(node->children[0], out, 0); 
            out << "] = ";
            descompile(node->children[1], out, 0);
            out << ";\n";
            break;

        case AST_ADD:
            out << "(";
            descompile(node->children[0], out, 0);
            out << " + ";
            descompile(node->children[1], out, 0);
            out << ")";
            break;

        case AST_SUB:
            out << "(";
            descompile(node->children[0], out, 0);
            out << " - ";
            descompile(node->children[1], out, 0);
            out << ")";
            break;

        case AST_MUL:
            out << "(";
            descompile(node->children[0], out, 0);
            out << " * ";
            descompile(node->children[1], out, 0);
            out << ")";
            break;

        case AST_DIV:
            out << "(";
            descompile(node->children[0], out, 0);
            out << " / ";
            descompile(node->children[1], out, 0);
            out << ")";
            break;

        case AST_EQUAL:
            out << "(";
            descompile(node->children[0], out, 0);
            out << " == ";
            descompile(node->children[1], out, 0);
            out << ")";
            break;

        case AST_DIF:
            out << "(";
            descompile(node->children[0], out, 0);
            out << " != ";
            descompile(node->children[1], out, 0);
            out << ")";
            break;

        case AST_LESS:
            out << "(";
            descompile(node->children[0], out, 0);
            out << " < ";
            descompile(node->children[1], out, 0);
            out << ")";
            break;

        case AST_GRT:
            out << "(";
            descompile(node->children[0], out, 0);
            out << " > ";
            descompile(node->children[1], out, 0);
            out << ")";
            break;

        case AST_GE:
            out << "(";
            descompile(node->children[0], out, 0);
            out << " >= ";
            descompile(node->children[1], out, 0);
            out << ")";
            break;

        case AST_LE:
            out << "(";
            descompile(node->children[0], out, 0);
            out << " <= ";
            descompile(node->children[1], out, 0);
            out << ")";
            break;

        case AST_IF_THEN:
            out << indentation << "if (";
            descompile(node->children[0], out, 0);
            out << ")\n";
            descompile(node->children[1], out, indent);
            break;

        case AST_IF_THEN_ELSE:
            out << indentation << "if (";
            descompile(node->children[0], out, 0);
            out << ")\n";
            descompile(node->children[1], out, indent);
            out << indentation << "else\n";
            descompile(node->children[2], out, indent);
            break;

        case AST_WHILE:
            out << indentation << "while (";
            descompile(node->children[0], out, 0);
            out << ") do\n";
            descompile(node->children[1], out, indent);
            break;

        case AST_DO_WHILE:
            out << indentation << "do\n";
            descompile(node->children[0], out, indent);
            out << indentation << "while (";
            descompile(node->children[1], out, 0);
            out << ");\n";
            break;

        case AST_INT_FUNDEC:
        {
            out << "int" << " " << (node->symbol ? node->symbol->text : "") << "(";
            descompile(node->children[0], out, 0);
            out << ")\n";
            descompile(node->children[1], out, indent);
            break;
        }
        
        case AST_BYTE_FUNDEC:
        {
            out << "byte" << " " << (node->symbol ? node->symbol->text : "") << "(";
            descompile(node->children[0], out, 0);
            out << ")\n";
            descompile(node->children[1], out, indent);
            break;
        }

        case AST_REAL_FUNDEC:
        {
            out << "real" << " " << (node->symbol ? node->symbol->text : "") << "(";
            descompile(node->children[0], out, 0);
            out << ")\n";
            descompile(node->children[1], out, indent);
            break;
        }

        case AST_INT_VETDEC:
            out << indentation << "int " << (node->symbol ? node->symbol->text : "") << "[";
            descompile(node->children[0], out, 0);
            out << "] = ";
            if (node->children[1]) {
                descompile(node->children[1], out, 0);
            }
            out << ";\n";
            break;

        case AST_BYTE_VETDEC:
            out << indentation << "byte " << (node->symbol ? node->symbol->text : "") << "[";
            descompile(node->children[0], out, 0);
            out << "] = ";
            if (node->children[1]) {
                descompile(node->children[1], out, 0);
            }
            out << ";\n";
            break;
        
        case AST_REAL_VETDEC:
            out << indentation << "real " << (node->symbol ? node->symbol->text : "") << "[";
            descompile(node->children[0], out, 0);
            out << "] = ";
            if (node->children[1]) {
                descompile(node->children[1], out, 0);
            }
            out << ";\n";
            break;

            case AST_INT_VETDEC_VAZIO:
            out << indentation << "int " << (node->symbol ? node->symbol->text : "") << "[";
            descompile(node->children[0], out, 0);
            out << "];\n";
            break;

        case AST_BYTE_VETDEC_VAZIO:
            out << indentation << "byte " << (node->symbol ? node->symbol->text : "") << "[";
            descompile(node->children[0], out, 0);
            out << "];\n";
            break;
        
        case AST_REAL_VETDEC_VAZIO:
            out << indentation << "real " << (node->symbol ? node->symbol->text : "") << "[";
            descompile(node->children[0], out, 0);
            out << "];\n";
            break;

        case AST_PARAM_LIST:
            descompile(node->children[0], out, 0);
            if (node->children[1]) {
                out << ", ";
                descompile(node->children[1], out, 0);
            }
            break;

        case AST_SYMBOL:
            out << (node->symbol ? node->symbol->text : "");
            break;

        case AST_SYMBOL_FUNC:
            out << (node->symbol ? node->symbol->text : "") << "(";
            descompile(node->children[0], out, 0);
            out << ")";
            break;

        case AST_SYMBOL_VEC:
            out << (node->symbol ? node->symbol->text : "") << "[";
            descompile(node->children[0], out, 0);
            out << "]";
            break;

        case AST_PAR_INT_SYMBOL:
            out << "int " << (node->symbol ? node->symbol->text : "");
            break;

        case AST_PAR_BYTE_SYMBOL:
            out << "byte " << (node->symbol ? node->symbol->text : "");
            break;

        case AST_PAR_REAL_SYMBOL:
            out << "real " << (node->symbol ? node->symbol->text : "");
            break;

        case AST_PAR_LIST:
            descompile(node->children[0], out, 0);
            if (node->children[1]) {
                out << ", ";
                descompile(node->children[1], out, 0);
            }
            break;

        case AST_EXPR_VET_ELEM:
            out << (node->symbol ? node->symbol->text : "");
            descompile(node->children[0], out, 0);
            if(node->children[1])
            {
                out << ", ";
                descompile(node->children[1], out, 0);
            }
            break;

        case AST_EXP_LIST:
            descompile(node->children[0], out, 0);
            if (node->children[1]) {
                out << ", ";
                descompile(node->children[1], out, 0);
            }
            break;

        case AST_NOT:
            out << "!(";
            descompile(node->children[0], out, 0);
            out << ")";
            break;

        case AST_AND:
            out << "(";
            descompile(node->children[0], out, 0);
            out << " && ";
            descompile(node->children[1], out, 0);
            out << ")";
            break;

        case AST_OR:
            out << "(";
            descompile(node->children[0], out, 0);
            out << " || ";
            descompile(node->children[1], out, 0);
            out << ")";
            break;
        
        case AST_UNKNOWN:
            out << indentation << "// [Unknown node type]\n";
            break;
            
        default:
            out << indentation << "// [Unknown node type]\n";
            break;
    }
}
