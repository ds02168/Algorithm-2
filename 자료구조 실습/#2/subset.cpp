#pragma warning(disable:4996)
#include <stdio.h>
#include <time.h> //헤더파일 참조
#define MAX_SIZE 20 //순열 최대 크기

void perm(int*, int*, int, int); //함수 선언

void main(void) //main함수
{
	int i, n; //i=초기화를 위한 변수,  n은 사용자 입력을 저장할 변수
	int A[20]; //순열을 1과 0으로 계산할 배열
	int B[20]; //오름차순 순열을 출력할 배열
	clock_t start, stop; //시간 측정을 위한 변수
	printf("21712184_유태형 자료구조실습 과제#2\n");
	while (1) //무한 루프(종료까지 계속)
	{
		printf("양의 정수 n을 입력(최대 20까지,음수입력시 종료):");
		scanf("%d", &n); //사용자로부터 입력받음

		if (n < 0 || n > 20)
			break; //음수이거나, 20보다 큰수면 종료

		for (i = 0; i < MAX_SIZE; i++)
			A[i] = 0; //A배열 초기화

		for (i = 0; i < MAX_SIZE; i++)
			B[i] = i + 1; //B배열 초기화


		printf("%d개의 의 순열은 \n", n);
		start = clock(); //측정 시작
		perm(A, B, 0, n); //재귀함수 호출
		stop = clock(); //측정 종료

		printf("\n시간 = %.2f\n\n\n", ((double)(stop - start)) / CLOCKS_PER_SEC); //걸린 시간(종료시간 - 시작 시간) 출력
	}
	printf("이용해 주셔서 감사합니다.\n");

}

void perm(int* list, int* list2, int i, int n)
{
	int j;
	if (i == n) { //종료조건
		printf("{ ");
		for (j = 0; j < n; j++)
			if (list[j] == 0) {
				printf("%d ", list2[j]); //순열(B,list2 배열) 출력
			}
		printf("}");
		printf("\n");
		return;
	}

	perm(list, list2, i + 1, n); //재귀
	list[i] = 1;
	perm(list, list2, i + 1, n);
	list[i] = 0;
}