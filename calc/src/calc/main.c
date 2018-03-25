#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <assert.h>
#include <errno.h>
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
			//memset(buf + len, '\0', newbufsize - bufsize);
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
	fclose(fp);
	//TODO:バッファが余ることがあるので切り詰める
	return buf;
}

void compile(const char* filename, const char* source) {
	char cfilename[1024] = {0};
	char ofilename[1024] = {0};
	//C言語のソースファイル名
	int res = sprintf(cfilename, "c/%s_c.c", filename);
	assert(res != -1);
	//C言語の実行ファイル名
	res = sprintf(ofilename,"c/%s_c.a", filename);
	assert(res != -1);
	//読み取り専用で開いてみて成功したらもうコンパイル済み
	FILE* fp = fopen(cfilename, "r");
	if(fp != NULL) {
		fclose(fp);
		return;
	}
	//まだ存在しないので作る
	fp = fopen(cfilename, "w");
	fprintf(fp, "#include <stdio.h>\n\n");
	fprintf(fp, "int main(int argc, char* argv[]) { \n");
	fprintf(fp, "    printf(\"%%d\", (int)(%s));\n", source);
	fprintf(fp, "    fflush(stdout);\n");
	fprintf(fp, "    return 0;\n");
	fprintf(fp, "}");
	fclose(fp);
	//コンパイルする
	char cmd[1024] = {0};
	res = sprintf(cmd, "clang %s -o %s", cfilename, ofilename);
	assert(res != -1);
	system(cmd);
}

int run(const char* filename) {
	char ofilename[1024] = {0};
	int res = sprintf(ofilename,"./c/%s_c.a", filename);
	assert(res != -1);
	//printf("%s", ofilename);
	//fflush(stdout);
	errno = 0;
	FILE* output = popen(ofilename, "r");
	if(output == NULL) {
		perror("fail");
		return -1;
	}
	char ret_buf[1024] = {0};
	int offs = 0;
	while(1) {
		char ch = fgetc(output);
		if(ch == -1) {
			break;
		}
		ret_buf[offs] = ch;
		offs++;
		assert(offs < 1024);
	}
	pclose(output);
	return atoi(ret_buf);
}

void test(const char* filename) {
	ast* a = parse_from_file(filename);
	char* source = readall(filename);
	compile(filename, source);
	ast* body = ast_first(a);
	printf("[%s]\n", filename);
	printf("%s\n", source);
	int cres = run(filename);
	int eres = (int)ast_eval(body);
	printf("C = %d\n", cres);
	printf("E = %d\n", eres);
	if(cres != eres) {
		ast_dump(body);
	}
	assert(cres == eres);
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