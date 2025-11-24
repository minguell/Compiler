/* Augusto Mattei Grohmnann - 550429
 Miguel Dutra Fontes Guerra - 342573 */
// iloc.h
#ifndef _ILOC_H_
#define _ILOC_H_

// Tipos de operandos permitidos conforme o enunciado: temporários, constantes ou rótulos 
typedef enum {
    ILOC_OP_REG,    // Temporário/Registrador (ex: r1, r2)
    ILOC_OP_CONST,  // Valor Constante (ex: 10, 4)
    ILOC_OP_LABEL   // Rótulo (ex: L1, L2)
} OperandType;

// Estrutura para um argumento (operando)
typedef struct {
    OperandType type;
    char *value;    // Armazena o nome do reg, label ou valor da constante como string
} ILOC_Operand;

// Estrutura para uma operação ILOC
typedef struct {
    char *opcode;           // Mnemônico da instrução (ex: "add", "loadAI")
    ILOC_Operand *args[3];  // Operandos (máximo 3 geralmente: src1, src2, dest)
    int num_args;           // Controle de quantos args existem
} ILOC_Op;

// Estrutura para a lista de operações (Lista Duplamente Encadeada para facilitar concatenação) 
typedef struct iloc_node {
    char *label;            // Rótulo opcional precedendo a instrução
    ILOC_Op *instr;         // A instrução em si
    struct iloc_node *prev;
    struct iloc_node *next;
} ILOC_Node;

// Estrutura descritora da lista (facilita anexar listas inteiras de filhos na AST)
typedef struct {
    ILOC_Node *head;
    ILOC_Node *tail;
} ILOC_List;



// Protótipos de funções auxiliares sugeridas para a etapa 2.2 e 2.3
ILOC_Operand* new_operand(OperandType type, char* value);
ILOC_Op* new_operation(char* opcode, ILOC_Operand* arg1, ILOC_Operand* arg2, ILOC_Operand* arg3);
ILOC_List* new_iloc_list(ILOC_Node* node);
ILOC_Node* new_label_node(char* label);
void free_iloc_list(ILOC_List* list);

ILOC_Node* new_iloc_node(ILOC_Op* op);
void concat_iloc_lists(ILOC_List* list1, ILOC_List* list2);

// Gera um novo nome de rótulo único (ex: "L1")
char *new_label();

// Gera um novo nome de registrador temporário único (ex: "r5")
char *new_temp();

void print_program(ILOC_List* program);

#endif // _ILOC_H_
