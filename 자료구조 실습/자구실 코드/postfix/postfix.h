#include "stack.h"

typedef enum {
	lparen, rparen, nnot, power, plus, minus, times,
	divide, mod, eos, operand
} precedence;

precedence get_token(char*, char*, int*);
