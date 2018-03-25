#include <stdio.h>
#include "parse/parser.h"

int main(int argc, char* argv[]) {
	ast* a =parse_from_file("main.calc");
	ast_dump(a);
	ast* body = ast_first(a);
	printf("--------------------\n");
	printf("%lf\n", ast_eval(body));
	printf("--------------------\n");
	ast_delete(a);
	return 0;
}