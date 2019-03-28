#include "parser.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

static parser_input_tag gParserInputTag;
static FILE *gFakeStdout = NULL;
static FILE *gRealStdout = NULL;

// proto
static void parser_stdout_swap_begin();
static void parser_stdout_swap_end();

ast *parse_from_file(const char *filename) {
        gParserInputTag = parser_input_from_file;
        parser_stdout_swap_begin();
        extern FILE *yyin;
        extern void yy_calc_start(void);
        extern int yyparse(void);
        extern ast *yy_release();
        FILE *fp = fopen(filename, "r");
        if (fp == NULL) {
                printf("can't opened file: %s", filename);
                parser_stdout_swap_end();
                return NULL;
        }
        yy_calc_start();
        yyin = fp;
        if (yyparse()) {
                //失敗
                parser_stdout_swap_end();
                return NULL;
        }
        parser_stdout_swap_end();
        return yy_release();
}

ast *parse_from_source(const char *source) {
        gParserInputTag = parser_input_from_source;
        parser_stdout_swap_begin();
        extern void yy_setstr(char *source);
        extern void yy_clearstr();
        extern void yy_calc_start(void);
        extern int yyparse(void);
        extern ast *yy_release();
        yy_calc_start();
        yy_setstr(strdup(source));
        if (yyparse()) {
                yy_clearstr();
                parser_stdout_swap_end();
                return NULL;
        }
        yy_clearstr();
        parser_stdout_swap_end();
        return yy_release();
}

parser_input_tag parse_get_input_tag() { return gParserInputTag; }
// private
static void parser_stdout_swap_begin() {
        //本物を取っておく
        gRealStdout = stdout;
        //適当なファイルを開く
        char template[] = "temp/cacheXXXXXX";
        int fd = mkstemp(template);
        if (fd == -1) {
                perror("parser_stdout_swap_begin");
                return;
        }
        FILE *fp = fdopen(fd, "w");
        if (fp == NULL) {
                perror("parser_stdout_swap_begin");
        }
        assert(fp != NULL);
        // stdoutをすり替える
        gFakeStdout = fp;
        stdout = fp;
}

static void parser_stdout_swap_end() {
        //閉じる
        if (gFakeStdout != NULL) {
                fclose(gFakeStdout);
        }
        //戻す
        stdout = gRealStdout;
        gRealStdout = NULL;
        gFakeStdout = NULL;
}