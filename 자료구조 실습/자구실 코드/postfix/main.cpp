#include <stdio.h>
#include "stack.h"

int eval(char*);
void postfix(char*, char*);

void main()
{
	char expr[100];
	char new_expr[100];

	printf("������ �Է��Ͻÿ�: ");
	gets_s(expr);
	printf("Infix = %s\n", expr);
	postfix(expr, new_expr);
	printf("Postfix = %s\n", new_expr);
	printf("��� ��� = %d\n", eval(new_expr));

}