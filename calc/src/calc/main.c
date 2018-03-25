#include <stdio.h>
#include "parse/parser.h"

int main(int argc, char* argv[]) {
	ast* a =parse_from_file("main.calc");
	ast_dump(a);
	ast_delete(a);
	return 0;
}