#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1000
#define BUF_SIZE 50
#define NUM_ALPHA 26
#define START_A 97
#define END_Z 122

struct node {
	char voca[BUF_SIZE];
	int num = 0;
	struct node* link = NULL;
};

struct node alphabet[NUM_ALPHA];

void Read_Data();
void insert(char*);
void garbagecollect();
void Delete(char*);
void Print_Data();


void main(void)
{
	char input[BUF_SIZE];
	int menu = 0;

	printf("��ǻ�Ͱ��а� 21712184_������\n");

	Read_Data();

	while (menu != 3)
	{
		printf("���ϴ� �޴��� �����ϼ���(1: ����, 2:���, 3:����) :");
		scanf("%d", &menu);

		switch (menu)
		{
		case 1:
			printf("������ �ܾ� :");
			scanf("%s", input);
			Delete(input);
			break;
		case 2:
			Print_Data();
			break;
		case 3:
			break;
		default:
			printf("1���� 3������ �Է����ּ���\n");
			break;
		}
	}
	garbagecollect();

}

void Read_Data()
{
	char name[20];
	FILE* fp;
	char buf[MAX_SIZE];
	char* word;

	printf("���� �̸�? ");
	scanf("%s", name);


	if ((fp = fopen(name, "r")) == NULL) {
		printf("�������� �ʴ� �����Դϴ�.");
		exit(1);
	}

	while (!feof(fp))
	{
		fgets(buf, sizeof(buf), fp);

		word = strtok(buf, " % ., -_'\"?!()[]:\t\n;");

		while (word != NULL)
		{
			strlwr(word);
			insert(word);

			word = strtok(NULL, " % ., -_'\"?!()[]:\t\n;");
		}
	}

	fclose(fp);
}

void insert(char* word)
{
	char fir = word[0];

	if (fir >= START_A && fir <= END_Z)
	{
		int index = fir - START_A;

		struct node* ptr;
		struct node* before;

		struct node* temp;
		temp = (struct node*)malloc(sizeof(struct node));

		if (temp == NULL) {
			fprintf(stderr, "The memory is full\n"); exit(1);
		}
		else {
			temp->link = NULL;
			strcpy(temp->voca, word);
			temp->num = 1;
		}



		if (alphabet[index].link == NULL)
			alphabet[index].link = temp;

		else
		{

			for (ptr = alphabet[index].link; strcmp(ptr->voca, temp->voca) < 0; ptr = ptr->link) {
				if (ptr->link == NULL)
					break;
			}
			for (before = &alphabet[index]; before->link != ptr; before = before->link);

			if (strcmp(ptr->voca, temp->voca) == 0)
			{
				free(temp);
				ptr->num++;
			}
			else if (strcmp(ptr->voca, temp->voca) == 1)
			{
				temp->link = before->link;
				before->link = temp;
			}
			else if (strcmp(ptr->voca, temp->voca) == -1)
				ptr->link = temp;
		}

		alphabet[index].num++;
	}
}

void Delete(char* input)
{
	struct node* ptr, * before;

	char fir = input[0];
	if (fir >= START_A && fir <= END_Z)
	{
		int index = fir - START_A;
		for (ptr = alphabet[index].link; strcmp(ptr->voca, input) != 0; ptr = ptr->link)
			if (ptr->link == NULL)
			{
				printf("����!! %s�� �������� �ʽ��ϴ�.\n", input);
				return;
			}
		for (before = &alphabet[index]; before->link != ptr; before = before->link);


		if (ptr != NULL)
		{
			before->link = ptr->link;
			printf("����!! %s�� ���� �Ǿ����ϴ�.\n", ptr->voca);
			alphabet[index].num -= ptr->num;
			free(ptr);
		}

	}
	else
		printf("����!!�ҹ��ڷθ� ������ �ܾ �Է��� �ּ���\n");
}

void Print_Data()
{
	char name[20];
	FILE* fp2;
	struct node* ptr;
	int sum = 0;

	printf("������ ������ �̸� :");
	scanf("%s", name);

	if ((fp2 = fopen(name, "w")) == NULL)
	{
		printf("����!! ���Ͽ� ������ �� �����ϴ�.\n");
		return;
	}

	for (int index = 0; index < NUM_ALPHA; index++)
	{
		for (ptr = alphabet[index].link; ptr != NULL; ptr = ptr->link)
			fprintf(fp2, "%s, %d\n", ptr->voca, ptr->num);

		fprintf(fp2, "\n");
		sum += alphabet[index].num;
	}

	for (int index = 0; index < NUM_ALPHA; index++)
		fprintf(fp2, "%c�� �����ϴ� �ܾ�: %d��\n", (char)(index + START_A), alphabet[index].num);


	fprintf(fp2, "��ü �ܾ��� ����: %d���Դϴ�.\n", sum);
	fclose(fp2);
}


void garbagecollect()
{
	struct node* front, * rear;
	for (int i = 0; i < NUM_ALPHA; i++)
	{
		rear = alphabet[i].link;
		front = rear;
		while (rear != NULL)
		{
			rear = rear->link;
			free(front);
			front = rear;
		}
	}
}