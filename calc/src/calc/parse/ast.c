#include "ast.h"
#include <stdio.h>

//proto
static void ast_child_delete(vector_item item);
static void ast_dumpImpl(ast* self, int depth);

ast* ast_new(ast_tag tag) {
	ast* ret = (ast*)malloc(sizeof(ast));
	ret->tag = tag;
	ret->children = vector_new();
	return ret;
}

ast* ast_new_int(int ivalue) {
	ast* ret = ast_new(ast_int);
	ret->u.ivalue = ivalue;
	return ret;
}

ast* ast_new_double(double dvalue) {
	ast* ret = ast_new(ast_double);
	ret->u.dvalue = dvalue;
	return ret;
}

ast* ast_new_binary(ast_tag tag, ast* left, ast* right) {
	ast* ret = ast_new(tag);
	ast_push(ret, left);
	ast_push(ret, right);
	return ret;
}

void ast_push(ast* self, ast* a) {
	vector_push(self->children, a);
}

void ast_dump(ast* self) {
	ast_dumpImpl(self, 0);
}

void ast_print(ast* self) {
	#define p(a) printf((a)); break
	switch(self->tag) {
		case ast_int:
			printf("%d", self->u.ivalue);
			break;
		case ast_double:
			printf("%lf", self->u.dvalue);
			break;
		case ast_add: p("+");
		case ast_sub: p("-");
		case ast_mul: p("*");
		case ast_div: p("/");
		case ast_mod: p("%%");

		case ast_assign: p("=");
		case ast_add_assign: p("+=");
		case ast_sub_assign: p("-=");
		case ast_mul_assign: p("*=");
		case ast_div_assign: p("/=");
		case ast_mod_assign: p("%%=");
		default:
			printf("undefined");
			break;
	}
	#undef p
}

void ast_delete(ast* self) {
	vector_delete(self->children, ast_child_delete);
	free(self);
}

//private
static void ast_child_delete(vector_item item) {
	ast* e = (ast*)item;
	ast_delete(e);
}

static void ast_dumpImpl(ast* self, int depth) {
	for(int i=0; i<depth; i++) {
		printf(" ");
	}
	ast_print(self);
	printf("\n");
	for(int i=0; i<self->children->length; i++) {
		ast* e = (ast*)vector_at(self->children, i);
		ast_dumpImpl(e, depth + 1);
	}
}