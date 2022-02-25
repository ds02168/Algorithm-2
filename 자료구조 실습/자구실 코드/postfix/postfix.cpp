#include "postfix.h"

int isp[] = { 0, 19, 12, 12, 13, 13, 13, 0 };
int icp[] = { 20, 19, 12, 12, 13, 13, 13, 0 };

void print_token(precedence);
char get_symbol(precedence);

void postfix(char* expr, char *new_expr)
{
	precedence token;
	stack<precedence> st;
	char symbol;
	int n = 0, idx = 0;

	st.push(eos);
	for (token = get_token(expr, &symbol, &n); token != eos; token = get_token(expr, &symbol, &n)) {
		if (token == operand)
			new_expr[idx++] = symbol;
		else if (token == rparen) {
			while (st.peek() != lparen)
				new_expr[idx++] = get_symbol(st.pop());
			st.pop();
		}
		else {
			while (icp[token] <= isp[st.peek()])
				new_expr[idx++] = get_symbol(st.pop());
			st.push(token);
		}
	}
	while (st.peek() != eos)
		new_expr[idx++] = get_symbol(st.pop());
	new_expr[idx] = '\0';
}

void print_token(precedence token)
{
	switch (token) {
	case plus: printf("+"); break;
	case minus: printf("-"); break;
	case times: printf("*"); break;
	case divide: printf("/"); break;
	case mod: printf("%%"); break;
	}
}

char get_symbol(precedence token)
{
	switch (token) {
	case plus: return '+';
	case minus: return '-';
	case times: return '*';
	case divide: return '/';
	case mod: return '%';
	}
}