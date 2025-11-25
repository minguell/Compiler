/* Augusto Mattei Grohmnann - 550429
 Miguel Dutra Fontes Guerra - 342573 */
 

/*
Função principal para realização da análise sintática.
*/
#include <stdio.h>
#include "asd.h"
#include "tabela.h"
extern int yyparse(void);
extern int yylex_destroy(void);
asd_tree_t *arvore = NULL;
int main (int argc, char **argv)
{
  push_scope();
  int ret = yyparse();
  if (arvore && arvore->code) {
         print_program(arvore->code);
    }
  asd_free(arvore);
  yylex_destroy();
  free_all_scopes();
  return ret;
}


