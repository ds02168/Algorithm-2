#include <stdio.h>
#include <stdlib.h> //헤더파일

#define INIT_SIZE 10 //초기 상수크기
#define COMPARE(x,y) (((x)<(y)) ? -1 : ((x)==(y)) ? 0 : 1) //비교 매크로

struct poly { //구조체
	int exp; //계수
	int coef; //지수
};

struct poly *input_poly(); //입력함수
void print_poly(struct poly*); //출력함수

struct poly *padd(struct poly*, struct poly*); //덧셈

struct poly *single_multi(struct poly*, struct poly); //단항 곱

struct poly *pmulti(struct poly*, struct poly*); //다항 곱

void main(void)
{
	struct poly *A, *B, *C, *D, *E; //입력다항식:A,B 덧셈출력:C 단항곱 출력:D 다항곱출력:D 포인터

	A = input_poly();
	B = input_poly(); //입력

	printf("다항식 A: ");
	print_poly(A);

	printf("다항식 B: ");
	print_poly(B); //출력

	C = padd(A, B); //덧셈
	printf("A + B: ");
	print_poly(C); //출력

	for (int i = 0; B[i].exp != -1; i++) { //B다항식 요소마다
		D = single_multi(A, B[i]); //A다항식과 곱하여
		printf("\n%d번째 곱 = ", i);
		print_poly(D); //출력
	}

	E = pmulti(A, B); //단항식곱과 덧셈을 응용한 다항곱
	printf("\n");
	printf("A * B = ");
	print_poly(E); //출력

	free(A);
	free(B);
	free(C);
	free(D);
	free(E); //할당하였던 메모리들 반환
}

struct poly *input_poly() //다항식 입력 함수
{
	int size = INIT_SIZE, i; //크기초기화
	struct poly *p;

	p = (struct poly*)malloc(sizeof(struct poly)*size); //다항식 메모리 할당
	printf("다항식(계수, 지수)쌍 입력 (마지막항은 -1 -1): \n");
	for (i = 0;; i++)
	{
		scanf("%d %d", &p[i].coef, &p[i].exp);
		if (p[i].coef == -1 && p[i].exp == -1) //계수:-1, 지수:-1이면 그만입력받음
			break;
		if (i == size - 1) //크기가 부족할시
		{
			size = size * 2;
			p = (struct poly*)realloc(p, sizeof(struct poly)*size); //2배로 사이즈 늘림
		}
	}
	return p; //다항식 포인터 반환

}


void print_poly(struct poly* p) //다항식 출력 함수
{
	printf("{ ");
	for (int i = 0; p[i].exp != -1; i++) //0부터 지수가 -1인것까지
	{
		if (p[i].exp) {
			if (p[i].coef > 0)
				printf("+"); //양수이면 +
			printf("%dX^%d", p[i].coef, p[i].exp); //출력
		}
		else {
			if (p[i].coef > 0)
				printf("+"); //양수이면 +
			printf("%d", p[i].coef);
			break;
		}
	}
	printf(" }\n");
}

struct poly *padd(struct poly*A, struct poly*B) //덧셈 함수
{
	int ia, ib, ic, size = INIT_SIZE, coef; //a,b,c다항식의 index 저장하는 변수,계수의합을 저장할 변수
	struct poly* C;
	C = (struct poly*)malloc(sizeof(struct poly)*size); //덧셈결과를 C에 저장
	ia = ib = ic = 0; //index들 0으로 초기화

	while ((A[ia].exp != -1) && (B[ib].exp != -1)) //A와 B다항식 모두 요소가 남아있을때 까지
	{
		switch (COMPARE(A[ia].exp, B[ib].exp)) //A다항식과 B다항식 지수 비교
		{
		case -1: // A<B
			C[ic++] = B[ib++]; //C다항식에 B다항식 삽입
			break;
		case 0: //A=B
			coef = A[ia].coef + B[ib].coef; //A계수와 B계수를 합한값
			if (coef) { //0이아니면
				C[ic].coef = coef;
				C[ic].exp = A[ia].exp; //C다항식에 삽입
			}
			ia++;
			ib++;
			ic++; //index들 증가
			break;
		case 1: //A>B
			C[ic++] = A[ia++]; //C다항식에 A다항식 삽입
			break;
		}
		if (ic == size) //C다항식의 크기가 꽉차면
		{
			size = size * 2;
			C = (struct poly*)realloc(C, sizeof(struct poly)*size);
		} //2배로 늘려줌
	}

	//A또는 B다항식에 남아있는 요소들 삽입
	while (A[ia].exp != -1) //나머지 A다항식
	{
		if (ic == size) //C가 다차면 2배로 늘림
		{
			size = size * 2;
			C = (struct poly*)realloc(C, sizeof(struct poly)*size);
		}
		C[ic++] = A[ia++]; //삽입

	}

	while (B[ib].exp != -1) //나머지 B다항식
	{
		if (ic == size) //C가 다차면 2배로 늘림
		{
			size = size * 2;
			C = (struct poly*)realloc(C, sizeof(struct poly)*size);
		}

		C[ic++] = B[ib++]; //삽입
	}

	C[ic].exp = -1;
	C[ic].coef = -1;//마지막 지수와 계수를 -1로 두어서 끝

	return C;
}


struct poly *single_multi(struct poly *A, struct poly item) //단항곱 함수
{
	struct poly *p;
	int size, i;
	for (i = 0; A[i].exp != -1; i++);
	size = i + 1; //A배열의 크기

	p = (struct poly*)malloc(sizeof(struct poly)*size);
	for (i = 0; i<size - 1; i++) { //A배열 크기만큼
		p[i].coef = A[i].coef * item.coef;
		p[i].exp = A[i].exp + item.exp;//곱한값을 삽입
	}
	p[size - 1].exp = -1;
	p[size - 1].coef = -1; //마지막을 -1을 둠으로써 끝을 알림
	return p;
}
struct poly *pmulti(struct poly *A, struct poly *B) //다항곱 함수
{
	struct poly *p; //요소마다 곱
	struct poly *result; //다항곱 결과 저장
	int size, i;

	for (i = 0; B[i].exp != -1; i++);
	size = i + 1; //B배열 크기

	result = (struct poly*)malloc(sizeof(struct poly) * size);
	result[0].exp = -1;
	result[0].coef = -1; //결과를 저장할 다항식에 -1을 둠으로써 끝 플래그를 둠

	for (i = 0; i < size - 1; i++)//B다항식 요소마다
	{
		p = single_multi(A, B[i]); //A다항식과 곱하여
		result = padd(result, p); //단항곱들의 합을 result다항식에 저장
	}

	return result; //result다항식 반환
}
