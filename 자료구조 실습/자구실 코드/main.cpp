#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))
#define SIZE 100000

void sort(int[], int);
int is_sorted(int[], int);

void main()
{
	int A[SIZE], i;

	srand(time(0));
	for (i = 0; i < SIZE; i++) {
		A[i] = rand();
		A[i] = A[i] << 16;
		A[i] += rand();
	}

	sort(A, SIZE);
	if (is_sorted(A, SIZE) == 1)
		printf("정렬 완료\n");
	else
		printf("오류 발생\n");
}

void sort(int A[], int n)
{
	int i, j, temp, min;

	for (i = 0; i < n - 1; i++) {
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