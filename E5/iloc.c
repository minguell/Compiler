/* Augusto Mattei Grohmnann - 550429
 Miguel Dutra Fontes Guerra - 342573 */
/* iloc.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "iloc.h"


static int label_count = 0;
static int temp_count = 0;

char *new_label() {
    char buffer[64];
    snprintf(buffer, 64, "L%d", label_count++);
    return strdup(buffer);
}

char *new_temp() {
    char buffer[64];
    snprintf(buffer, 64, "r%d", temp_count++);
    return strdup(buffer);
}


ILOC_Operand* new_operand(OperandType type, char* value) {
    ILOC_Operand* op = (ILOC_Operand*) malloc(sizeof(ILOC_Operand));
    op->type = type;
    op->value = strdup(value); 
    return op;
}


ILOC_Op* new_operation(char* opcode, ILOC_Operand* arg1, ILOC_Operand* arg2, ILOC_Operand* arg3) {
    ILOC_Op* new_op = (ILOC_Op*) malloc(sizeof(ILOC_Op));
    new_op->opcode = strdup(opcode);
    
    new_op->args[0] = arg1;
    new_op->args[1] = arg2;
    new_op->args[2] = arg3;
    
    new_op->num_args = 0;
    if (arg1) new_op->num_args++;
    if (arg2) new_op->num_args++;
    if (arg3) new_op->num_args++;
    
    return new_op;
}

ILOC_Node* new_iloc_node(ILOC_Op* op) {
    ILOC_Node* node = (ILOC_Node*) malloc(sizeof(ILOC_Node));
    node->label = NULL;
    node->instr = op;
    node->prev = NULL;
    node->next = NULL;
    return node;
}

ILOC_List* new_iloc_list(ILOC_Node* node) {
    if (!node) return NULL;
    ILOC_List* list = (ILOC_List*) malloc(sizeof(ILOC_List));
    list->head = node;
    list->tail = node;
    return list;
}

void concat_iloc_lists(ILOC_List* list1, ILOC_List* list2) {
    if (!list1 || !list2) return;
    if (!list2->head) return; 

    if (!list1->head) {

        list1->head = list2->head;
        list1->tail = list2->tail;
    } else {
        list1->tail->next = list2->head;
        list2->head->prev = list1->tail;
        list1->tail = list2->tail;
    }
    
    free(list2); 
}

// Libera toda a memória de uma lista de código ILOC
void free_iloc_list(ILOC_List* list) {
    if (!list) return;

    ILOC_Node* current = list->head;
    while (current != NULL) {
        ILOC_Node* next = current->next;
        
        if (current->instr) {
            for (int i = 0; i < 3; i++) {
                if (current->instr->args[i]) {
                    free(current->instr->args[i]->value);
                    free(current->instr->args[i]);
                }
            }
            free(current->instr->opcode);
            free(current->instr);
        }
        
        if (current->label) free(current->label);
        
        free(current);
        
        current = next;
    }
    free(list);
}

ILOC_Node* new_label_node(char* label) {
    ILOC_Op* op = new_operation("nop", NULL, NULL, NULL);
    ILOC_Node* node = new_iloc_node(op);
    node->label = strdup(label); 
    return node;
}

ILOC_List* safe_concat(ILOC_List* list1, ILOC_List* list2) {
    if (!list1) return list2;
    if (!list2) return list1;
    
    concat_iloc_lists(list1, list2);
    return list1;
}

void print_program(ILOC_List* program) {
    if (!program) return;
    ILOC_Node* current = program->head;
    while (current) {
        if (current->label) printf("%s: ", current->label);

        ILOC_Op* op = current->instr;
        if (op) {
            printf("%s", op->opcode);

            int is_arrow_control = (strcmp(op->opcode, "cbr") == 0 || 
                                    strcmp(op->opcode, "jump") == 0 ||
                                    strcmp(op->opcode, "jumpI") == 0);
            
            char* arrow = is_arrow_control ? "->" : "=>";

            // --- TRATAMENTO DE EXCEÇÕES DE FORMATO ---

            // CASO 1: loadI (Constante => Registrador)
            if (strcmp(op->opcode, "loadI") == 0) {
                printf(" %s => %s", op->args[0]->value, op->args[1]->value);
            }
            // CASO 2: storeAI (Origem => Base, Offset)
            else if (strcmp(op->opcode, "storeAI") == 0) {
                printf(" %s => %s, %s", op->args[0]->value, op->args[1]->value, op->args[2]->value);
            }
            // CASO 3: cbr (Condição -> LabelTrue, LabelFalse)
            else if (strcmp(op->opcode, "cbr") == 0) {
                 printf(" %s -> %s, %s", op->args[0]->value, op->args[1]->value, op->args[2]->value);
            }
            // CASO 4: jumpI (-> Label)
            else if (strcmp(op->opcode, "jumpI") == 0) {
                 printf(" -> %s", op->args[0]->value);
            }
            // CASO 5: jump (-> Register)
            else if (strcmp(op->opcode, "jump") == 0) {
                 printf(" -> %s", op->args[0]->value);
            }
            // CASO 6: Padrão Geral (inclui cmp_XX, add, sub, etc)
            else {
                 if (op->args[0]) printf(" %s", op->args[0]->value);
                 if (op->args[1]) printf(", %s", op->args[1]->value);
                 if (op->args[2]) printf(" %s %s", arrow, op->args[2]->value);
            }
        }
        printf("\n");
        current = current->next;
    }
}
