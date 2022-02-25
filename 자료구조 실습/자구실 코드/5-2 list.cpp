#include <stdio.h>
#include <stdlib.h>

struct node {
	int data;
	struct node* next;
};

struct node* insert_front(struct node*, int);
struct node* insert_last(struct node*, int);
struct node* invert(struct node*);
struct node* concatenate(struct node*, struct node*);
int search(struct node*, int);
int delete_front(struct node**);
struct node* delete_any(struct node*, int);
void print_list(const char *, struct node*);

void main()
{
	int search_num;
	struct node* A = NULL, *B = NULL;

	for (int i = 0; i < 10; i++)
		A = insert_front(A, i * 10);

	print_list("A = ", A);
	
	/*
	A = invert(A);
	print_list("invert 후 A = ", A);
	*/

	for (int i = 0; i < 10; i++)
		B = insert_last(B, i * 10);

	print_list("B = ", B);

	/*
	A = concatenate(A, B);
	print_list("concatenate 후 A = ", A);
	printf("어떤 데이터를 A에서 찾을까요? ");
	scanf("%d", &search_num);
	printf("%d는 %d번째 노드에 있습니다\n", search_num, search(A, search_num));
	

	for (int i = 0; i < 10; i++) {
		printf("%d번째 삭제의 결과 = %d\n", i, delete_front(&A));
		print_list("삭제 후 A = ", A);
	}
	*/
	printf("어떤 데이터를 A에서 지울까요? ");
	scanf("%d", &search_num);
	A = delete_any(A, search_num);
	print_list("삭제 후 A = ", A);
}

struct node *insert_front(struct node* start, int data)
{
	struct node* new_node;

	new_node = (struct node*)malloc(sizeof(struct node));
	new_node->data = data;
	new_node->next = start;
	return new_node;
}

struct node* insert_last(struct node* start, int data)
{
	struct node* new_node, *ptr;

	new_node = (struct node*)malloc(sizeof(struct node));
	new_node->data = data;
	new_node->next = NULL;

	if (start == NULL)
		return new_node;

	for (ptr = start; ptr->next != NULL; ptr = ptr->next)
		;
	ptr->next = new_node;

	return start;
}

struct node* invert(struct node* lead)
{
	struct node* middle = NULL, * tail;

	while (lead != NULL) {
		tail = middle;
		middle = lead;
		lead = lead->next;
		middle->next = tail;
	}
	return middle;
}

struct node* concatenate(struct node* A, struct node* B)
{
	struct node* ptr;

	if (A == NULL)
		return B;

	if (B == NULL)
		return A;

	for (ptr = A; ptr->next != NULL; ptr = ptr->next)
		;
	ptr->next = B;
	return A;
}

int search(struct node* start, int search_num)
{
	int position = 0;
	struct node* ptr;

	for (ptr = start; ptr != NULL; ptr = ptr->next, position++)
		if (ptr->data == search_num)
			return position;
	return -1;
}

int delete_front(struct node** start)
{
	struct node* deleted;
	int return_value;

	if (*start == NULL)
		return -1;

	deleted = *start;
	*start = (*start)->next;
	return_value = deleted->data;
	free(deleted);
	return return_value;
}

struct node* delete_any(struct node* start, int data)
{
	struct node* deleted, *ptr;

	if (start == NULL)
		return NULL;

	if (start->data == data) {
		deleted = start;
		start = start->next;
		free(deleted);
		return start;
	}

	for (ptr = start; ptr->next != NULL; ptr = ptr->next)
		if (ptr->next->data == data) {
			deleted = ptr->next;
			ptr->next = deleted->next;
			free(deleted);
			break;
		}

	return start;
}

void print_list(const char *msg, struct node* start)
{
	struct node* ptr;

	printf("%s [ ", msg);
	for (ptr = start; ptr != NULL; ptr = ptr->next)
		printf("%d ", ptr->data);
	printf("]\n");
}