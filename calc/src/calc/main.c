#include <assert.h>
#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "parse/parser.h"
#include "util/string_buffer.h"

char* readall(const char* filename) {
        FILE* fp = fopen(filename, "r");
        if (fp == NULL) {
                return NULL;
        }
        string_buffer* buf = string_buffer_new();
        while (1) {
                char ch = fgetc(fp);
                if (ch == EOF) {
                        break;
                }
                string_buffer_append(buf, ch);
        }
        fclose(fp);
        // TODO:バッファが余ることがあるので切り詰める
        return string_buffer_release(buf);
}

void string_sub(const char* source, char* block, int offs, int len) {
        for (int i = offs; i < (offs + len); i++) {
                int real = (i - offs);
                block[real] = source[i];
        }
}

int main(int argc, char* argv[]) {
        int opt;
        while ((opt = getopt(argc, argv, "td:e:")) != -1) {
                switch (opt) {
                        // test
                        case 't':
                                fprintf(stderr, "t options is removed.");
                                abort();
                                break;
                        // dump source
                        case 'd': {
                                ast* a = parse_from_source(optarg);
                                ast_dump(ast_first(a));
                                ast_delete(a);
                                break;
                        }
                        // eval source
                        case 'e': {
                                ast* a = parse_from_source(optarg);
                                printf("%lf\n", ast_eval(ast_first(a)));
                                ast_delete(a);
                                break;
                        }
                        default:
                                printf("error! \'%c\' \'%c\'\n", opt, optopt);
                                return 1;
                }
        }
        return 0;
}