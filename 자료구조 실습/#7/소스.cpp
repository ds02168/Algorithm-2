#include <stdio.h>
#include <stdlib.h>

struct node {
	int data;
	struct node* next;
};

struct node* insert_front(struct node*, int);
struct node* insert_last(struct node*, int);
void print_list(const char*, struct node*);
int delete_front(struct node**);
struct node* invert(struct node*);
struct node* concatenate(struct node*, struct node*);
struct node* delete_any(struct node*, int);
int search(struct node*, int);

void main()
{
	struct node *A = NULL, * B = NULL, *C = NULL, *D = NULL;

	for (int i = 1; i <4; i++) {
		A = insert_front(A, i * 10);
		print_list("insert_front = ", A);
	}
	D = insert_last(D, 40);
	print_list("insert_last = ", D);
	D = insert_last(D, 50);
	print_list("insert_last = ", D);
	D = insert_last(D, 60);
	print_list("insert_last = ", D);
	A = concatenate(A, D);
	print_list("concatenate = ", A);
	A = invert(A);
	print_list("invert = ", A);
	delete_front(&A);
	print_list("delete_front = ", A);
	A = delete_any(A,20);
	print_list("delete_any = ", A);
	printf("\n");

	B = insert_front(B, 10);
	print_list("push = ", B);
	B = insert_front(B, 20);
	print_list("push = ", B);
	delete_front(&B);
	print_list("pop = ", B);
	B = insert_front(B, 30);
	print_list("push = ", B);
	delete_front(&B);
	print_list("pop = ", B);

	printf("\n");

	C = insert_last(C, 10);
	print_list("addq = ", C);
	C = insert_last(C, 20);
	print_list("addq = ", C);
	C = insert_last(C, 30);
	print_list("addq = ", C);
	delete_front(&C);
	print_list("deleteq = ", C);
	delete_front(&C);
	print_list("deleteq = ", C);
}

struct node* insert_front(struct node* start, int data)
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

	for (ptr = start; ptr->next != NULL; ptr = ptr->next);
	ptr->next = new_node;

	return start;
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

void print_list(const char* msg, struct node* start)
{
	struct node* ptr;
	printf("%s [ ", msg);
	for (ptr = start; ptr != NULL; ptr = ptr->next)
		printf("%d ", ptr->data);
	printf("]\n");
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

struct node* delete_any(struct node* start, int data)
{
	struct node* deleted, * ptr;

	if (start == NULL)
		return NULL;

	if (start->data == data)
	{
		deleted = start;
		start = start->next;
		free(deleted);
		return start;
	}

	for(ptr = start;ptr->next!=NULL;ptr=ptr->next)
		if (ptr->next->data == data) {
			deleted = ptr->next;
			ptr->next = deleted->next;
			free(deleted);
			break;
		}

	return start;
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