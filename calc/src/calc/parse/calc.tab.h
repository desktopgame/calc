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
     AND_ASSIGN = 271,
     OR_ASSIGN = 272,
     LSHIFT_ASSIGN = 273,
     RSHIFT_ASSIGN = 274,
     EXC_OR_ASSIGN = 275,
     EQUAL = 276,
     NOTEQUAL = 277,
     INC = 278,
     DEC = 279,
     GT = 280,
     GE = 281,
     LT = 282,
     LE = 283,
     LSHIFT = 284,
     RSHIFT = 285,
     NOT = 286,
     BIT_AND = 287,
     BIT_OR = 288,
     LOGIC_AND = 289,
     LOGIC_OR = 290,
     LP = 291,
     RP = 292,
     EXC_OR = 293,
     IDENT = 294,
     POSITIVE = 295,
     NEGATIVE = 296,
     CHILDA = 297
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
#define AND_ASSIGN 271
#define OR_ASSIGN 272
#define LSHIFT_ASSIGN 273
#define RSHIFT_ASSIGN 274
#define EXC_OR_ASSIGN 275
#define EQUAL 276
#define NOTEQUAL 277
#define INC 278
#define DEC 279
#define GT 280
#define GE 281
#define LT 282
#define LE 283
#define LSHIFT 284
#define RSHIFT 285
#define NOT 286
#define BIT_AND 287
#define BIT_OR 288
#define LOGIC_AND 289
#define LOGIC_OR 290
#define LP 291
#define RP 292
#define EXC_OR 293
#define IDENT 294
#define POSITIVE 295
#define NEGATIVE 296
#define CHILDA 297




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 8 "calc.y"
{
	ast* ast_value;
	char* svalue;
}
/* Line 1529 of yacc.c.  */
#line 138 "calc.tab.h"
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
