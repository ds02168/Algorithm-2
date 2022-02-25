#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SWAP(x,y,t) ((t)=(x), (x)=(y), (y)=(t))
#define SIZE 50000

void sort(int[], int);
int is_sorted(int[], int);

void main(void)
{
	int A[SIZE], i;
	clock_t start, stop;
	double duration;


	srand(time(0));
	for (i = 0; i < SIZE; i++) {
		A[i] = rand();
		A[i] = A[i] << 16;
		A[i] += rand();
	}
	start = clock();
	sort(A, SIZE);
	stop = clock();

	duration = ((double)(stop - start)) / CLOCKS_PER_SEC;

	if (is_sorted(A, SIZE) == 1)
		printf("정렬완료\n");
	else
		printf("오류발생\n");

	printf("%d 일때 실행 시간 = %.2f\n", SIZE, duration);
}

void sort(int A[], int n)
{
	int i, j, temp, min;

	for (i = 0; i < n - 1; i++)
	{
		min = i;
		for (j = i + 1; j < n; j++)
			if (A[j] < A[min])
				min = j;
		SWAP(A[i], A[min], temp);
	}
}

int is_sorted(int A[], int n)
{
	for (int i = 1; i < n; i++)
		if (A[i] < A[i - 1])
			return 0;
	return 1;
}