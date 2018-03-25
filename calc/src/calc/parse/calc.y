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
		GT GE LT LE
		NOT BIT_AND BIT_OR LOGIC_AND LOGIC_OR
		IDENT
%type <ast_value> expression
%left ADD SUB
%left MUL DiV MOD
%%
program
	: expression
	{
		extern void yy_register(ast* a);
		yy_register($1);
	}
	;
expression
	: INT
	| DOUBLE
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
	;
%%
