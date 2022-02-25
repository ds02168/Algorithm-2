#include "postfix.h"

int eval(char* expr)
{
	int n = 0;
	int op1, op2;
	char ch;
	precedence token;
	stack<int> st;

	for (token = get_token(expr, &ch, &n); token != eos;
		token = get_token(expr, &ch, &n)) {
		if (token == operand)
			st.push(ch - '0');
		else {
			op2 = st.pop();
			op1 = st.pop();
			switch (token) {
			case plus: st.push(op1 + op2); break;
			case minus: st.push(op1 - op2); break;
			case times: st.push(op1 * op2); break;
			case divide: st.push(op1 / op2); break;
			case mod: st.push(op1 % op2); break;
			}
		}
		printf("token = %c, stack = ", ch);
		st.print();
	}
	return st.pop();
}

precedence get_token(char* expr, char* symbol, int* n)
{
	*symbol = expr[(*n)++];
	switch (*symbol) {
	case '(': return lparen;
	case ')': return rparen;
	case '*': return times;
	case '/': return divide;
	case '%': return mod;
	case '+': return plus;
	case '-': return minus;
	case '\0': return eos;
	default: return operand;
	}
}