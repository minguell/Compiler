/* Augusto Mattei Grohmnann - 550429
 Miguel Dutra Fontes Guerra - 342573 */
/* iloc.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "iloc.h"

// --- ITEM 2.2: Rótulos e Temporários ---
// Variáveis estáticas para garantir unicidade
static int label_count = 0;
static int temp_count = 0;

char *new_label() {
    char buffer[64];
    // Gera rótulo no formato L0, L1, ... 
    snprintf(buffer, 64, "L%d", label_count++);
    return strdup(buffer);
}

char *new_temp() {
    char buffer[64];
    // Gera temporário no formato r0, r1, ...
    snprintf(buffer, 64, "r%d", temp_count++);
    return strdup(buffer);
}

// --- ITEM 2.1: Estruturas de Dados ---

// Cria um novo operando (Registrador, Constante ou Rótulo)
ILOC_Operand* new_operand(OperandType type, char* value) {
    ILOC_Operand* op = (ILOC_Operand*) malloc(sizeof(ILOC_Operand));
    op->type = type;
    op->value = strdup(value); // Copia a string para não depender do buffer original
    return op;
}

// Cria uma nova operação ILOC (ex: add r1, r2 => r3)
ILOC_Op* new_operation(char* opcode, ILOC_Operand* arg1, ILOC_Operand* arg2, ILOC_Operand* arg3) {
    ILOC_Op* new_op = (ILOC_Op*) malloc(sizeof(ILOC_Op));
    new_op->opcode = strdup(opcode);
    
    // Inicializa argumentos
    new_op->args[0] = arg1;
    new_op->args[1] = arg2;
    new_op->args[2] = arg3;
    
    // Define quantos argumentos existem (útil para impressão depois)
    new_op->num_args = 0;
    if (arg1) new_op->num_args++;
    if (arg2) new_op->num_args++;
    if (arg3) new_op->num_args++;
    
    return new_op;
}

// Cria um novo nó da lista encadeada contendo uma instrução
ILOC_Node* new_iloc_node(ILOC_Op* op) {
    ILOC_Node* node = (ILOC_Node*) malloc(sizeof(ILOC_Node));
    node->label = NULL; // Por padrão, a instrução não tem rótulo
    node->instr = op;
    node->prev = NULL;
    node->next = NULL;
    return node;
}

// Cria uma nova lista contendo inicialmente um único nó
ILOC_List* new_iloc_list(ILOC_Node* node) {
    if (!node) return NULL;
    ILOC_List* list = (ILOC_List*) malloc(sizeof(ILOC_List));
    list->head = node;
    list->tail = node;
    return list;
}

// Função utilitária para concatenar duas listas de código (essencial para a etapa 2.3)
// Adiciona a lista2 ao final da lista1. A lista2 é esvaziada/invalidada.
void concat_iloc_lists(ILOC_List* list1, ILOC_List* list2) {
    if (!list1 || !list2) return;
    if (!list2->head) return; // Lista 2 vazia, nada a fazer

    if (!list1->head) {
        // Se a lista 1 estava vazia, ela vira a lista 2
        list1->head = list2->head;
        list1->tail = list2->tail;
    } else {
        // Conecta o final da lista 1 ao início da lista 2
        list1->tail->next = list2->head;
        list2->head->prev = list1->tail;
        list1->tail = list2->tail;
    }
    
    // A estrutura descritora da lista 2 não é mais necessária (os nós agora pertencem à lista 1)
    // Mas CUIDADO: só libere o ponteiro da lista2, não seus nós.
    free(list2); 
}

// Libera toda a memória de uma lista de código ILOC
void free_iloc_list(ILOC_List* list) {
    if (!list) return;

    ILOC_Node* current = list->head;
    while (current != NULL) {
        ILOC_Node* next = current->next;
        
        // Libera a instrução dentro do nó
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
        
        // Libera o rótulo se houver
        if (current->label) free(current->label);
        
        // Libera o nó
        free(current);
        
        current = next;
    }
    // Libera a estrutura da lista
    free(list);
}

// Cria um nó contendo uma instrução NOP com um rótulo associado
ILOC_Node* new_label_node(char* label) {
    ILOC_Op* op = new_operation("nop", NULL, NULL, NULL);
    ILOC_Node* node = new_iloc_node(op);
    node->label = strdup(label); // Define o rótulo do nó
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

            // MUDANÇA AQUI: Apenas cbr e jumps usam ->
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