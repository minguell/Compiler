//Aluno: Miguel Dutra Fontes Guerra
//Cartão UFRGS: 00342573


#include <stdio.h>
#include <stdlib.h>

extern int yyparse(void);
extern void initMe(void);
extern int isRunning(void);
extern FILE* yyin;

int main(int argc, char** argv) {
    if (argc < 2) {
        fprintf(stderr, "Uso: %s nome_arquivo\n", argv[0]);
        exit(1);
    }

    yyin = fopen(argv[1], "r");
    if (!yyin) {
        fprintf(stderr, "Erro ao abrir arquivo %s\n", argv[1]);
        exit(2);
    }

    initMe();

    if (yyparse() == 0) {
        fprintf(stdout, "Compilado com sucesso\n");
        exit(0);
    } else {
        fprintf(stderr, "Erro na compilação\n");
        exit(3);
    }

    return 0;
}
