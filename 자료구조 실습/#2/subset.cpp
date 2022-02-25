#pragma warning(disable:4996)
#include <stdio.h>
#include <time.h> //������� ����
#define MAX_SIZE 20 //���� �ִ� ũ��

void perm(int*, int*, int, int); //�Լ� ����

void main(void) //main�Լ�
{
	int i, n; //i=�ʱ�ȭ�� ���� ����,  n�� ����� �Է��� ������ ����
	int A[20]; //������ 1�� 0���� ����� �迭
	int B[20]; //�������� ������ ����� �迭
	clock_t start, stop; //�ð� ������ ���� ����
	printf("21712184_������ �ڷᱸ���ǽ� ����#2\n");
	while (1) //���� ����(������� ���)
	{
		printf("���� ���� n�� �Է�(�ִ� 20����,�����Է½� ����):");
		scanf("%d", &n); //����ڷκ��� �Է¹���

		if (n < 0 || n > 20)
			break; //�����̰ų�, 20���� ū���� ����

		for (i = 0; i < MAX_SIZE; i++)
			A[i] = 0; //A�迭 �ʱ�ȭ

		for (i = 0; i < MAX_SIZE; i++)
			B[i] = i + 1; //B�迭 �ʱ�ȭ


		printf("%d���� �� ������ \n", n);
		start = clock(); //���� ����
		perm(A, B, 0, n); //����Լ� ȣ��
		stop = clock(); //���� ����

		printf("\n�ð� = %.2f\n\n\n", ((double)(stop - start)) / CLOCKS_PER_SEC); //�ɸ� �ð�(����ð� - ���� �ð�) ���
	}
	printf("�̿��� �ּż� �����մϴ�.\n");

}

void perm(int* list, int* list2, int i, int n)
{
	int j;
	if (i == n) { //��������
		printf("{ ");
		for (j = 0; j < n; j++)
			if (list[j] == 0) {
				printf("%d ", list2[j]); //����(B,list2 �迭) ���
			}
		printf("}");
		printf("\n");
		return;
	}

	perm(list, list2, i + 1, n); //���
	list[i] = 1;
	perm(list, list2, i + 1, n);
	list[i] = 0;
}