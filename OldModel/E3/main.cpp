//Aluno: Miguel Dutra Fontes Guerra
//Cartão UFRGS: 00342573

# include <stdio.h>
# include <stdlib.h>
# include "ast.hpp"
# include "symbols.hpp"

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
        fprintf(stderr, "Call filename\n");
        exit(1);
    }
    if(0 == (yyin=fopen(argv[1],"r")))
    {
        fprintf(stderr, "nao abriu o arquivo");
        exit(1);
    }

    outputFile = argv[2];
    yyparse();

    int linhas = getLineNumber();
    printf("\nQUANTIDADE DE LINHAS: %d\n\n", linhas);

    printf("TABELA DE SÍMBOLOS:\n");
    symbolPrintTable();
    printf("\n");

}
