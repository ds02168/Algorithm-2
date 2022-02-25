#include <stdio.h>
#include "stack.h"

int eval(char*);
void postfix(char*, char*);

void main()
{
	char expr[100];
	char new_expr[100];

	printf("수식을 입력하시오: ");
	gets_s(expr);
	printf("Infix = %s\n", expr);
	postfix(expr, new_expr);
	printf("Postfix = %s\n", new_expr);
	printf("계산 결과 = %d\n", eval(new_expr));

}