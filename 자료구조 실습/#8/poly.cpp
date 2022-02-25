#include "poly.h"
#include <math.h>

#define COMPARE(x,y) ((x)<(y)?-1:(x)>(y)?1:0)

POLY* create_polynomial()
{
	int coef, exp;
	POLY *rear, *front;

	front = rear = getNode();
	front->exp = -1;

	printf("(���, ����)�� ���� �Է�, �������� (-1 -1)�Է�:\n");
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

POLY* cpmult(POLY* A, POLY* B) //���׽� ���� �Լ�
{
	bool done = false;
	POLY* front, *rear, *Astart, *D; //Astart = A�� �����, D�� ���� ������ �����Դϴ�.

	D = getNode();
	D->exp = -1;
	D->next = D; //D ���׽� �ʱ�ȭ �մϴ�.

	Astart = A; //Astart�� A�� ����� �Դϴ�.
	B = B->next;
	while (done != true)
	{
		if (B->exp == -1) { //B�� ������ �ǵ��ƿ���
			done = true; //��� �׵��� ���� �����Ƿ�
			break; //���� �մϴ�.
		}

		front = rear = getNode(); //B�� �׸��� �ʱ�ȭ ���־�� �ϹǷ� while�� �ȿ��� �ʱ�ȭ �մϴ�.
		front->exp = -1;

		A = A->next; //B�� ������ 1���� ���׽�A�� ���ϱ����� ����带 �ǳʶݴϴ�.

		while (A != Astart) //��� ���� �ǵ��ƿö�����
		{
			attach(A->coef*B->coef, A->exp + B->exp, &rear); //���װ����� �����մϴ�.
			A = A->next;
		}
		rear->next = front; //1���� ���װ��� ��������Ʈ�� ����ϴ�.
		print_polynomial("Xi = ", front);

		D = cpadd(front, D); //���װ��� �ĸ��� �����ݴϴ�.

		cerase(&front); //D�� ���Ͽ� ���� ���꿡 �ʿ���� ��������Ʈ �����մϴ�.

		B = B->next; //B�� ���� ��
	}

	return D; //�������(���װ�) ���׽��� �����մϴ�.
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
