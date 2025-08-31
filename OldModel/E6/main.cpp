//Aluno: Miguel Dutra Fontes Guerra
//Cartão UFRGS: 00342573

# include <stdio.h>
# include <stdlib.h>
# include "ast.hpp"
# include "symbols.hpp"
# include "semantic.hpp"

extern FILE*yyin;
extern int running;
extern int lineNumber;

char* outputFile = NULL;

int yylex();
int yyparse();

int isRunning();
int getLineNumber();
void symbolPrintTable();

void astPrint(AST* ast, int level);

int main(int argc, char** argv)
{
    if(argc < 3)
    {
        fprintf(stderr, "Call filename\n"); exit(1);
    }
    if(0 == (yyin=fopen(argv[1],"r")))
    {
        fprintf(stderr, "nao abriu o arquivo"); exit(2);
    }

    outputFile = argv[2];
    
    yyparse(); // GERAÇÃO DA AST e da TABELA DE SIMBOLOS
    int linhas = getLineNumber(); printf("\nQUANTIDADE DE LINHAS: %d\n\n", linhas);
    printf("\nTABELA DE SÍMBOLOS:\n");symbolPrintTable(); printf("\n");

    if(SemanticErrors > 0)
    {
        fprintf(stderr, "\nErros semanticos existentes: %d\n", SemanticErrors); exit(4);
    }

    printf("PROGRAMA COMPILADO SEM ERROS!\n");
}
