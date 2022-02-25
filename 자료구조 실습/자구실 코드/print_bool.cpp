#include <stdio.h>
#include <time.h>

#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

void print_bool(char*, int, int);

void main()
{
	char A[30];
	int i, n;
	clock_t start, stop;

	for (n = 2; n <= 30; n++) {
		for (i = 0; i < n; i++)
			A[i] = 0;	// 모두 0(False)으로 초기화

		start = clock();
		print_bool(A, 0, n);
		stop = clock();

		printf("n = %d일 때, 시간 = %.2f\n", n,
			(double)(stop - start) / CLOCKS_PER_SEC);
	}
}

void print_bool(char* list, int i, int n)
{
	int j;
	char temp;

	if (i == n) {
		for (j = 0; j < n; j++)
			;
//			(list[j] == 0) ? printf("F ") : printf("T ");			
//		printf("\n");
		return;
	}

	print_bool(list, i + 1, n);	// i번째가 0으로 시작하는 진리값들
	list[i] = 1;
	print_bool(list, i + 1, n); // i번째가 1로 시작하는 진리값들
	list[i] = 0;
}