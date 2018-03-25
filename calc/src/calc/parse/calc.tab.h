/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INT = 258,
     DOUBLE = 259,
     ADD = 260,
     SUB = 261,
     MUL = 262,
     DIV = 263,
     MOD = 264,
     ASSIGN = 265,
     ADD_ASSIGN = 266,
     SUB_ASSIGN = 267,
     MUL_ASSIGN = 268,
     DIV_ASSIGN = 269,
     MOD_ASSIGN = 270,
     EQUAL = 271,
     NOTEQUAL = 272,
     INC = 273,
     DEC = 274,
     GT = 275,
     GE = 276,
     LT = 277,
     LE = 278,
     LSHIFT = 279,
     RSHIFT = 280,
     NOT = 281,
     BIT_AND = 282,
     BIT_OR = 283,
     LOGIC_AND = 284,
     LOGIC_OR = 285,
     LP = 286,
     RP = 287,
     IDENT = 288
   };
#endif
/* Tokens.  */
#define INT 258
#define DOUBLE 259
#define ADD 260
#define SUB 261
#define MUL 262
#define DIV 263
#define MOD 264
#define ASSIGN 265
#define ADD_ASSIGN 266
#define SUB_ASSIGN 267
#define MUL_ASSIGN 268
#define DIV_ASSIGN 269
#define MOD_ASSIGN 270
#define EQUAL 271
#define NOTEQUAL 272
#define INC 273
#define DEC 274
#define GT 275
#define GE 276
#define LT 277
#define LE 278
#define LSHIFT 279
#define RSHIFT 280
#define NOT 281
#define BIT_AND 282
#define BIT_OR 283
#define LOGIC_AND 284
#define LOGIC_OR 285
#define LP 286
#define RP 287
#define IDENT 288




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 8 "calc.y"
{
	ast* ast_value;
	char* svalue;
}
/* Line 1529 of yacc.c.  */
#line 120 "calc.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif

extern YYLTYPE yylloc;
