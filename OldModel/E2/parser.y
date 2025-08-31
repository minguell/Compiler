//Aluno: Miguel Dutra Fontes Guerra
//Cartão UFRGS: 00342573
%{
#include <cstdio>
#include <cstdlib>
#include "symbol.h"
int yylex(void);
void yyerror(const char *s);
int getLineNumber();
%}

%union {
    struct Symbol* symbol;
}



%token KW_BYTE
%token KW_INT            
%token KW_REAL  

%token KW_IF                
%token KW_ELSE                   
%token KW_DO
%token KW_WHILE   
%token KW_READ           
%token KW_PRINT          
%token KW_RETURN      

%token OPERATOR_LE       
%token OPERATOR_GE       
%token OPERATOR_EQ       
%token OPERATOR_DIF   

%token <symbol> TK_IDENTIFIER
%token <symbol> LIT_INT LIT_CHAR LIT_REAL LIT_STRING

%token TOKEN_ERROR        

%%

programa: declaration_list
    ;

declaration_list: declaration declaration_list
    | 
    ;

declaration: declaration_function 
    | declaration_global
    ;

// -----------------------------------
// -----------  Globals  -------------
// -----------------------------------

declaration_global: declaration_global_byte
    | declaration_global_int
    | declaration_global_real
    ;

declaration_global_byte: KW_BYTE TK_IDENTIFIER '=' literal ';'
    | KW_BYTE TK_IDENTIFIER '[' LIT_INT ']' ';'
    | KW_BYTE TK_IDENTIFIER '[' LIT_INT ']' '=' array_val ';'
    ;

declaration_global_int: KW_INT TK_IDENTIFIER '=' literal ';'
    | KW_INT TK_IDENTIFIER '[' LIT_INT ']' ';'
    | KW_INT TK_IDENTIFIER '[' LIT_INT ']' '=' array_val ';'
    ;

declaration_global_real: KW_REAL TK_IDENTIFIER '=' literal ';'
    | KW_REAL TK_IDENTIFIER '[' LIT_INT ']' ';'
    | KW_REAL TK_IDENTIFIER '[' LIT_INT ']' '=' array_val ';'
    ;

literal: LIT_INT
    | LIT_CHAR
    | LIT_REAL
    ;

array_val: literal
    | literal ',' array_val
    ;

// -----------------------------------
// ---------  Functions  -------------
// -----------------------------------

declaration_function: KW_BYTE TK_IDENTIFIER '(' declaration_function_args_or_empty ')' command_block
    | KW_INT TK_IDENTIFIER '(' declaration_function_args_or_empty ')' command_block
    | KW_REAL TK_IDENTIFIER '(' declaration_function_args_or_empty ')' command_block
    ;

declaration_function_args_or_empty: declaration_function_args
    |
    ;

declaration_function_args: type TK_IDENTIFIER
    | type TK_IDENTIFIER ',' declaration_function_args
    ;

type: KW_BYTE
    | KW_INT
    | KW_REAL
    ;

// -----------------------------------
// ----------  Commands  -------------
// -----------------------------------

command: attribution ';'
    | read ';'
    | print ';'
    | return ';'
    | flux_control
    | command_block
    | ';' // comando vazio
    ;

command_block: '{' command_list '}'
    ;

command_list: command command_list
    | 
    ;

attribution: TK_IDENTIFIER '=' expression
    | array_element '=' expression
    ;

array_element: TK_IDENTIFIER '[' expression ']'
    ;

read: KW_READ TK_IDENTIFIER
    ;

print: KW_PRINT print_list
    ;

print_list: print_item
    | print_item print_list
    ;

print_item: LIT_STRING
    | expression
    ;

return: KW_RETURN expression
    ;

// -----------------------------------
// --------  Flux Control  -----------
// -----------------------------------

flux_control: KW_IF '(' expression ')' command
    | KW_IF '(' expression ')' command KW_ELSE command
    | KW_WHILE expression KW_DO command
    | KW_DO command KW_WHILE expression ';'
    ;

// -----------------------------------
// ----------- Expressions -----------
// -----------------------------------

expression: literal
    | TK_IDENTIFIER
    | array_element
    | function_call
    | '(' expression ')'
    | expression '+' expression
    | expression '-' expression
    | expression '*' expression
    | expression '/' expression
    | expression '<' expression
    | expression '>' expression
    | expression OPERATOR_LE expression
    | expression OPERATOR_GE expression
    | expression OPERATOR_EQ expression
    | expression OPERATOR_DIF expression
    | expression '&' expression
    | expression '|' expression
    | '~' expression
    ;

function_call: TK_IDENTIFIER '(' function_args_or_empty ')'
    ;

function_args_or_empty: function_args
    | 
    ;

function_args: expression
    | expression ',' function_args
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Syntax error at line %d.\n Error %s \n ", getLineNumber(), s);
    exit(3);
}

