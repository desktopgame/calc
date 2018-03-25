#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include "parse/parser.h"

char* readall(const char* filename) {
	FILE* fp = fopen(filename, "r");
	if(fp == NULL) {
		return NULL;
	}
	char* buf = (char*)malloc(sizeof(char) * 16);
	int bufsize = 16;
	int len = 0;
	memset(buf, '\0', 16);
	while(1) {
		char ch = fgetc(fp);
		if(ch == -1) {
			break;
		}
		if(len >= bufsize) {
			int newbufsize = bufsize + (bufsize / 2);
			char* temp = (char*)realloc(buf, sizeof(char) * newbufsize);
			bufsize = newbufsize;
			buf = temp;
			memset(buf + len, '\0', newbufsize - bufsize);
		}
		buf[len] = ch;
		len++;
	}
	if(len < bufsize) {
		char* repaire = (char*)malloc(sizeof(char) * (len + 1));
		memset(repaire, '\0', len + 1);
		for(int i=0; i<len; i++) {
			repaire[i] = buf[i];
		}
		free(buf);
		buf = repaire;
	}
	//TODO:バッファが余ることがあるので切り詰める
	return buf;
}

void test(const char* filename) {
	ast* a = parse_from_file(filename);
	char* source = readall(filename);
	ast* body = ast_first(a);
	printf("--------------------\n");
	printf("%s\n", source);
	printf("%s = %lf\n", filename, ast_eval(body));
	printf("--------------------\n");
	free(source);
	ast_delete(a);
}

void string_sub(const char* source, char* block, int offs, int len) {
	for(int i=offs; i<(offs+len); i++) {
		int real = (i - offs);
		block[real] = source[i];
	}
}

int main(int argc, char* argv[]) {
	//実行時ディレクトリの .calc をテスト
	const char* dirname = ".";
	DIR *dir = opendir(dirname);
	struct dirent *dp;
	struct stat fi;

	for (dp = readdir(dir); dp != NULL; dp = readdir(dir)) {
		if (dp->d_name[0] != '.') {
			//後ろ4文字を取り出す
			int len = strlen(dp->d_name);
			char block[256] = {0};
			string_sub(dp->d_name, block, len-4, 4);
			if(!strcmp(block, "calc")) {
				test(dp->d_name);
			}
		}
	}
	closedir(dir);
	return 0;
}