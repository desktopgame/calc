#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include "parse/parser.h"

void test(const char* filename) {
	ast* a = parse_from_file(filename);
	ast_dump(a);
	ast* body = ast_first(a);
	printf("--------------------\n");
	printf("%s = %lf\n", filename, ast_eval(body));
	printf("--------------------\n");
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