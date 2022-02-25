#include<stdio.h>

struct node {
	int coef;
	int exp;
	struct node *next;
};
typedef struct node POLY;


POLY* getNode();
void cerase(POLY**);
void garbageCollect();
POLY* create_polynomial();
POLY* cpadd(POLY*, POLY*);
POLY* csubtract(POLY*, POLY*);
POLY* cpmult(POLY*, POLY*);
void attach(int, int, POLY**);
void print_polynomial(const char *, POLY*);