#include "poly.h"
#include <math.h>

#define COMPARE(x,y) ((x)<(y)?-1:(x)>(y)?1:0)

POLY* create_polynomial()
{
	int coef, exp;
	POLY *rear, *front;

	front = rear = getNode();
	front->exp = -1;

	printf("(계수, 지수)의 쌍을 입력, 마지막은 (-1 -1)입력:\n");
	while (1)
	{
		scanf("%d %d", &coef, &exp);
		if (exp == -1)
			break;
		attach(coef, exp, &rear);
	}
	rear->next = front;
	return front;
}

POLY* cpadd(POLY *A, POLY *B)
{
	bool done = false;
	POLY *rear, *front;

	front = rear = getNode();
	front->exp = -1;

	A = A->next;
	B = B->next;
	while (done != true)
	{
		switch (COMPARE(A->exp, B->exp))
		{
		case -1:
			attach(B->coef, B->exp, &rear);
			B = B->next;
			break;
		case 0:
			if (A->exp == -1) {
				done = true;
				break;
			}
			else
			{
				if (A->coef + B->coef != 0)
					attach(A->coef + B->coef, B->exp, &rear);
				A = A->next;
				B = B->next;
				break;
			}
		case 1:
			attach(A->coef, A->exp, &rear);
			A = A->next;
		}
	}
	rear->next = front;
	return front;
}

POLY* cpsubtract(POLY* A, POLY* B)
{
	bool done = false;
	POLY* front, *rear;

	front = rear = getNode();
	front->exp = -1;

	A = A->next;
	B = B->next;
	while (done != true)
	{
		switch (COMPARE(A->exp, B->exp))
		{
		case -1:
			attach(-B->coef, B->exp, &rear);
			B = B->next;
			break;
		case 1:
			attach(A->coef, A->exp, &rear);
			A = A->next;
			break;
		case 0:
			if (A->exp == -1)
			{
				done = true;
				break;
			}
			else
			{
				if (A->coef - B->coef != 0)
					attach(A->coef - B->coef, B->exp, &rear);
				A = A->next;
				B = B->next;
			}
		}
	}
	rear->next = front;
	return front;
}

POLY* cpmult(POLY* A, POLY* B) //다항식 곱셈 함수
{
	bool done = false;
	POLY* front, *rear, *Astart, *D; //Astart = A의 헤드노드, D는 각항 곱들의 덧셈입니다.

	D = getNode();
	D->exp = -1;
	D->next = D; //D 다항식 초기화 합니다.

	Astart = A; //Astart는 A의 헤드노드 입니다.
	B = B->next;
	while (done != true)
	{
		if (B->exp == -1) { //B가 헤드노드로 되돌아오면
			done = true; //모든 항들이 곱을 했으므로
			break; //종료 합니다.
		}

		front = rear = getNode(); //B의 항마다 초기화 해주어야 하므로 while문 안에서 초기화 합니다.
		front->exp = -1;

		A = A->next; //B의 다음항 1개와 다항식A를 곱하기위해 헤드노드를 건너뜁니다.

		while (A != Astart) //헤드 노드로 되돌아올때까지
		{
			attach(A->coef*B->coef, A->exp + B->exp, &rear); //단항곱들을 저장합니다.
			A = A->next;
		}
		rear->next = front; //1개의 단항곱을 원형리스트로 만듭니다.
		print_polynomial("Xi = ", front);

		D = cpadd(front, D); //단항곱의 식마다 더해줍니다.

		cerase(&front); //D에 더하여 다음 연산에 필요없는 원형리스트 삭제합니다.

		B = B->next; //B의 다음 항
	}

	return D; //최종결과(다항곱) 다항식을 리턴합니다.
}

void attach(int coef, int exp, POLY** rear)
{
	POLY *node = getNode();

	node->coef = coef;
	node->exp = exp;
	(*rear)->next = node;
	(*rear) = node;
}


void print_polynomial(const char *msg, POLY* start)
{
	POLY* ptr;

	printf("%s", msg);
	for (ptr = start->next; ptr != start; ptr = ptr->next) {
		if (ptr == start->next) {
			if (ptr->coef == -1) {
				if (ptr->exp == 0)
					printf("-1 ");
				else if (ptr->exp == 1)
					printf("-X ");
				else
					printf("-X^%d ", ptr->exp);
			}
			else if (ptr->coef == 1) {
				if (ptr->exp == 0)
					printf("1 ");
				else if (ptr->exp == 1)
					printf("X ");
				else
					printf("X^%d ", ptr->exp);
			}
			else {
				if (ptr->exp == 0)
					printf("%d ", ptr->coef);
				else if (ptr->exp == 1)
					printf("%dX ", ptr->coef);
				else
					printf("%dX^%d ", ptr->coef, ptr->exp);
			}
		}
		else {
			if (ptr->coef < 0)
				printf("- ");
			else
				printf("+ ");
			if (ptr->coef == -1 || ptr->coef == 1) {
				if (ptr->exp == 0)
					printf("1 ");
				else if (ptr->exp == 1)
					printf("X ");
				else
					printf("X^%d ", ptr->exp);
			}
			else {
				if (ptr->exp == 0)
					printf("%d ", abs(ptr->coef));
				else if (ptr->exp == 1)
					printf("%dX ", abs(ptr->coef));
				else
					printf("%dX^%d ", abs(ptr->coef), ptr->exp);
			}
		}
	}
	printf("\n");
}
