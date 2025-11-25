/* Augusto Mattei Grohmnann - 550429
 Miguel Dutra Fontes Guerra - 342573 */
 
#include "iloc.h" // Inclua o novo cabeçalho
#ifndef _ASD_H_
#define _ASD_H_

typedef struct asd_tree {
  char *label;
  int data_type;
  int number_of_children;
  struct asd_tree **children;
  
  // --- NOVOS CAMPOS PARA E5 ---
  ILOC_List *code;   
  char *temp_result; 
                    
} asd_tree_t;


asd_tree_t *asd_new(const char *label);

void asd_free(asd_tree_t *tree);

void asd_add_child(asd_tree_t *tree, asd_tree_t *child);

void asd_print(asd_tree_t *tree);

void asd_print_graphviz (asd_tree_t *tree);
#endif 

