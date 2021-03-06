%{
//http://kmaebashi.com/programmer/devlang/diksam.html
#undef YY_INPUT
#define YY_INPUT(buf, result, max_size) (result = my_yyinput(buf, max_size))
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "ast.h"
#include "calc.tab.h"
#include "parser.h"

//for C4996
#ifdef _MSC_VER
#pragma warning(disable:4996)
#endif

static char* yaccSourceBuffer;
static int yaccSourceOffset;
static char* yaccErrorBuf;
static int yaccLineno;
static ast* yaccNode = NULL;

static int curr_line;
static int curr_col;

int yymain(void) {
	//yyparse();
	return(0);
}

//for clang
#ifndef SIGNAL_YYWRAP_PART
#define SIGNAL_YYWRAP_PART
int yywrap(void) {
	return 1;
}
#endif SIGNAL_YYWRAP_PART

int yyerror(char * err_str) {
	printf("error: %s<%d>\n", err_str, yaccLineno);
	return 1;
}

void yyexit() {
}

static int file_input(char *buf, int max_size) {
	int ch;
	int len;

	if (feof(yyin)) {
		return 0;
	}

	for (len = 0; len < max_size; len++) {
		ch = getc(yyin);
		if (ch == EOF)
			break;
		buf[len] = ch;
	}
    return len;
}

void yy_calc_start() {
	yaccLineno = 0;
	yaccNode = ast_new(ast_root);
}

void yy_register(ast* a) {
	assert(yaccNode != NULL);
	ast_push(yaccNode, a);
}

ast* yy_release() {
	ast* ret = yaccNode;
	yaccNode = NULL;
	return ret;
}

void yy_setstr(char* source) {
	yaccSourceBuffer = source;
	yaccSourceOffset = 0;
	yylineno = 0;
	curr_line = 0;
	curr_col = 0;
}

void yy_clearstr() {
	free(yaccSourceBuffer);
	yaccSourceBuffer = NULL;
	yaccSourceOffset = 0;
}

static int string_input(char *buf, int max_size) {
	int len = 0;
	int startOffset = yaccSourceOffset;
	for(; (yaccSourceOffset < yaccSourceOffset + max_size); yaccSourceOffset++) {
		if(yaccSourceBuffer[yaccSourceOffset] == '\0') {
			break;
		}
		buf[yaccSourceOffset - startOffset] = yaccSourceBuffer[yaccSourceOffset];
		len++;
	}
	return len;
}

static int my_yyinput(char *buf, int max_size) {
	int result;
	switch (parse_get_input_tag()) {
		case parser_input_from_file:
		result = file_input(buf, max_size);
		break;
	case parser_input_from_source:
		result = string_input(buf, max_size);
		break;
	default:
		return 0;
	}
	return result;
}
//error position
static void update_loc() {
  yylloc.first_line   = curr_line;
  yylloc.first_column = curr_col;

  {char * s; for(s = yytext; *s != '\0'; s++){
    if(*s == '\n'){
      curr_line++;
      curr_col = 1;
    }else{
      curr_col++;
    }
  }}

  yylloc.last_line   = curr_line;
  yylloc.last_column = curr_col-1;
}

//#define YY_USER_ACTION update_loc();
#define YY_USER_ACTION yylloc.first_line = yylloc.last_line = yylineno;
%}
%option yylineno
%option yy_scan_string
%option yy_scan_buffer
%option yy_scan_bytes
%start ML_COMMENT L_COMMENT
%%

<INITIAL>"+"				{ return (ADD); }
<INITIAL>"-"				{ return (SUB); }
<INITIAL>"*"				{ return (MUL); }
<INITIAL>"/"				{ return (DIV); }
<INITIAL>"%"				{ return (MOD); }
<INITIAL>"!"				{ return (NOT); }

<INITIAL>"="				{ return (ASSIGN); }
<INITIAL>"+="				{ return (ADD_ASSIGN); }
<INITIAL>"-="				{ return (SUB_ASSIGN); }
<INITIAL>"*="				{ return (MUL_ASSIGN); }
<INITIAL>"/="				{ return (DIV_ASSIGN); }
<INITIAL>"%="				{ return (MOD_ASSIGN); }

<INITIAL>"&="				{ return (AND_ASSIGN); }
<INITIAL>"|="				{ return (OR_ASSIGN); }
<INITIAL>"^="				{ return (EXC_OR_ASSIGN); }
<INITIAL>"<<="				{ return (LSHIFT_ASSIGN); }
<INITIAL>">>="				{ return (RSHIFT_ASSIGN); }

<INITIAL>"=="				{ return (EQUAL); }
<INITIAL>"!="				{ return (NOTEQUAL); }

<INITIAL>"<<"				{ return (LSHIFT); }
<INITIAL>">>"				{ return (RSHIFT); }

<INITIAL>"++"				{ return (INC); }
<INITIAL>"--"				{ return (DEC); }

<INITIAL>">"				{ return (GT); }
<INITIAL>">="				{ return (GE); }
<INITIAL>"<"				{ return (LT); }
<INITIAL>"<="				{ return (LE); }

<INITIAL>"&"				{ return (BIT_AND); }
<INITIAL>"&&"			{ return (LOGIC_AND); }
<INITIAL>"|"				{ return (BIT_OR); }
<INITIAL>"||"			{ return (LOGIC_OR); }
<INITIAL>"^"			{ return (EXC_OR); }
<INITIAL>"~"			{ return (CHILDA); }

<INITIAL>"("				{ return (LP); }
<INITIAL>")"			{ return (RP); }

<INITIAL>"0" {
	yylval.ast_value = ast_new_int(0);
	return INT;
}

<INITIAL>"\n" {
	yaccLineno++;
}

<INITIAL>[1-9][0-9]* {
	yylval.ast_value = ast_new_int(atoi(yytext));
	return INT;
}

<INITIAL>[0-9]+\.[0-9]+ {
	yylval.ast_value = ast_new_double(atof(yytext));
	return DOUBLE;
}

<INITIAL>[A-Za-z_][A-Za-z_0-9]* {
	yylval.svalue = strdup(yytext);
	return IDENT;
}

<INITIAL>"/*"     BEGIN ML_COMMENT;
<INITIAL>"//"     BEGIN L_COMMENT;
<ML_COMMENT>\n     {
	yaccLineno++;
}
<ML_COMMENT>"*/"     {
    BEGIN INITIAL;
}
<ML_COMMENT>.      ;
<L_COMMENT>\n  {
	yaccLineno++;
	BEGIN INITIAL;
}
<L_COMMENT><<EOF>>   {
	BEGIN INITIAL;
}

%%
