#include "parser.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

static parser_input_tag gParserInputTag;

ast *parse_from_file(const char *filename) {
        gParserInputTag = parser_input_from_file;
        extern FILE *yyin;
        extern void yy_calc_start(void);
        extern int yyparse(void);
        extern ast *yy_release();
        FILE *fp = fopen(filename, "r");
        if (fp == NULL) {
                printf("can't opened file: %s", filename);
                return NULL;
        }
        yy_calc_start();
        yyin = fp;
        if (yyparse()) {
                //失敗
                return NULL;
        }
        return yy_release();
}

ast *parse_from_source(const char *source) {
        gParserInputTag = parser_input_from_source;
        extern void yy_setstr(char *source);
        extern void yy_clearstr();
        extern void yy_calc_start(void);
        extern int yyparse(void);
        extern ast *yy_release();
        yy_calc_start();
        yy_setstr(strdup(source));
        if (yyparse()) {
                yy_clearstr();
                return NULL;
        }
        yy_clearstr();
        return yy_release();
}

parser_input_tag parse_get_input_tag() { return gParserInputTag; }
