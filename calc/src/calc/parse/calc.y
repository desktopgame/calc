%{
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#define YYDEBUG 1
#define YYERROR_VERBOSE 1
%}
%union {
	ast* ast_value;
	char* svalue;
}

%locations
%token <ast_value>			INT
%token <ast_value>			DOUBLE
%token 	ADD SUB MUL DIV MOD
		ASSIGN ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN
		EQUAL NOTEQUAL INC DEC
		GT GE LT LE LSHIFT RSHIFT
		NOT BIT_AND BIT_OR LOGIC_AND LOGIC_OR LP RP
		EXC_OR
		IDENT
%type <ast_value> expression primary
%left ADD SUB
%left MUL DIV MOD
%left BIT_AND
%left EXC_OR
%left BIT_OR
%left LOGIC_AND
%left LOGIC_OR
%right ASSIGN
%right ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN
%%
program
	: expression
	{
		extern void yy_register(ast* a);
		yy_register($1);
	}
	;
expression
	: primary
	| expression ADD expression
	{
		$$ = ast_new_binary(ast_add, $1, $3);
	}
	| expression SUB expression
	{
		$$ = ast_new_binary(ast_sub, $1, $3);
	}
	| expression MUL expression
	{
		$$ = ast_new_binary(ast_mul, $1, $3);
	}
	| expression DIV expression
	{
		$$ = ast_new_binary(ast_div, $1, $3);
	}
	| expression MOD expression
	{
		$$ = ast_new_binary(ast_mod, $1, $3);
	}
	| expression BIT_OR expression
	{
		$$ = ast_new_binary(ast_bit_or, $1, $3);
	}
	| expression BIT_AND expression
	{
		$$ = ast_new_binary(ast_bit_and, $1, $3);
	}
	| expression EXC_OR expression
	{
		$$ = ast_new_binary(ast_exc_or, $1, $3);
	}
	| expression LOGIC_OR expression
	{
		$$ = ast_new_binary(ast_bit_or, $1, $3);
	}
	| expression LOGIC_AND expression
	{
		$$ = ast_new_binary(ast_bit_and, $1, $3);
	}
	| expression ASSIGN expression
	{
		$$ = ast_new_binary(ast_bit_and, $1, $3);
	}
	| expression ADD_ASSIGN expression
	{
		$$ = ast_new_binary(ast_bit_and, $1, $3);
	}
	| expression SUB_ASSIGN expression
	{
		$$ = ast_new_binary(ast_bit_and, $1, $3);
	}
	| expression MUL_ASSIGN expression
	{
		$$ = ast_new_binary(ast_bit_and, $1, $3);
	}
	| expression DIV_ASSIGN expression
	{
		$$ = ast_new_binary(ast_bit_and, $1, $3);
	}
	| expression MOD_ASSIGN expression
	{
		$$ = ast_new_binary(ast_bit_and, $1, $3);
	}
	| LP expression RP
	{
		$$ = $2;
	}
	;
primary
	: INT
	| DOUBLE
	;
%%
