/* Augusto Mattei Grohmnann - 550429
 Miguel Dutra Fontes Guerra - 342573 */
// iloc.h
#ifndef _ILOC_H_
#define _ILOC_H_

typedef enum {
    ILOC_OP_REG,   
    ILOC_OP_CONST,  
    ILOC_OP_LABEL   
} OperandType;

// Estrutura para um argumento (operando)
typedef struct {
    OperandType type;
    char *value;    
} ILOC_Operand;

// Estrutura para uma operação ILOC
typedef struct {
    char *opcode;           
    ILOC_Operand *args[3];  
    int num_args;           
} ILOC_Op;

// Estrutura para a lista de operações 
typedef struct iloc_node {
    char *label;            
    ILOC_Op *instr;         
    struct iloc_node *prev;
    struct iloc_node *next;
} ILOC_Node;

// Estrutura descritora da lista 
typedef struct {
    ILOC_Node *head;
    ILOC_Node *tail;
} ILOC_List;



// Protótipos de funções auxiliares 
ILOC_Operand* new_operand(OperandType type, char* value);
ILOC_Op* new_operation(char* opcode, ILOC_Operand* arg1, ILOC_Operand* arg2, ILOC_Operand* arg3);
ILOC_List* new_iloc_list(ILOC_Node* node);
ILOC_Node* new_label_node(char* label);
void free_iloc_list(ILOC_List* list);

ILOC_Node* new_iloc_node(ILOC_Op* op);
void concat_iloc_lists(ILOC_List* list1, ILOC_List* list2);

char *new_label();

char *new_temp();

ILOC_List* safe_concat(ILOC_List* list1, ILOC_List* list2);

void print_program(ILOC_List* program);

#endif // _ILOC_H_
