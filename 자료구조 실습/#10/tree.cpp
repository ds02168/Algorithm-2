#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct node {
	int data;
	struct node* lchild, *rchild;
};

struct node* make_tree_by_code();
struct node* make_tree_by_random(int);
void inorder(struct node*);
void preorder(struct node*);
void postorder(struct node*);
struct node* copy(struct node*);
struct node* swap(struct node*);
bool equal(struct node*, struct node*);
int height(struct node*);			// tree�� ����
int node_num(struct node*);			// ��� ��
int leaf_node_num(struct node*);	// ���� ����� ��

void main()
{
	int n;
	struct node* A, *B, *C, *D;

	srand(time(0));

	A = make_tree_by_code();
	B = copy(A);
	C = swap(A);

	printf("Ʈ�� A\n");
	printf("Inorder = [ ");
	inorder(A);
	printf("]\n\n");

	printf("Preorder = [ ");
	preorder(A);
	printf("]\n\n");

	printf("Postorder = [ ");
	postorder(A);
	printf("]\n\n");

	printf("Ʈ�� B = copy(A)\n");
	printf("Inorder = [ ");
	inorder(B);
	printf("]\n\n");

	printf("Preorder = [ ");
	preorder(B);
	printf("]\n\n");

	printf("Postorder = [ ");
	postorder(B);
	printf("]\n\n");

	printf("equal(A, B) : %s\n\n", equal(B, C) ? "true" : "false");

	printf("Ʈ�� C = swap(A)\n");
	printf("Inorder = [ ");
	inorder(C);
	printf("]\n\n");

	printf("Preorder = [ ");
	preorder(C);
	printf("]\n\n");

	printf("Postorder = [ ");
	postorder(C);
	printf("]\n\n");

	printf("��� ���� �Է�: ");
	scanf_s("%d", &n);
	D = make_tree_by_random(n);

	printf("Ʈ�� D :���� %d��\n", n);
	printf("Inorder = [ ");
	inorder(D);
	printf("]\n\n");

	printf("Preorder = [ ");
	preorder(D);
	printf("]\n\n");

	
	printf("Ʈ���� ���� = %d\n", height(A));
	printf("Ʈ���� �ִ� ��� �� = %d\n", node_num(A));
	printf("���� ����� �� = %d\n", leaf_node_num(A));
	
}

struct node* make_tree_by_code()
{
	struct node* five, *three, *eight, *one, *four;

	five = (struct node*)malloc(sizeof(struct node));
	five->data = 5;

	three = (struct node*)malloc(sizeof(struct node));
	three->data = 3;

	eight = (struct node*)malloc(sizeof(struct node));
	eight->data = 8;

	one = (struct node*)malloc(sizeof(struct node));
	one->data = 1;

	four = (struct node*)malloc(sizeof(struct node));
	four->data = 4;

	one->lchild = one->rchild = NULL;
	four->lchild = four->rchild = NULL;
	three->lchild = one;
	three->rchild = four;
	eight->lchild = eight->rchild = NULL;
	five->lchild = three;
	five->rchild = eight;

	return five;
}

void inorder(struct node* ptr)
{
	if (ptr != NULL) {
		inorder(ptr->lchild);
		printf("%d ", ptr->data);
		inorder(ptr->rchild);
	}
}

void preorder(struct node* ptr)
{
	if (ptr != NULL) {
		printf("%d ", ptr->data);
		preorder(ptr->lchild);
		preorder(ptr->rchild);
	}
}

void postorder(struct node* ptr)
{
	if (ptr != NULL) {
		postorder(ptr->lchild);
		postorder(ptr->rchild);
		printf("%d ", ptr->data);
	}
}

struct node* copy(struct node* original)
{
	struct node* new_node;

	if (original == NULL)
		return NULL;

	new_node = (struct node*)malloc(sizeof(struct node));
	new_node->data = original->data;
	new_node->lchild = copy(original->lchild);
	new_node->rchild = copy(original->rchild);

	return new_node;
}

struct node* swap(struct node* original)
{
	struct node* new_node;

	if (original == NULL)
		return NULL;

	new_node = (struct node*)malloc(sizeof(struct node));
	new_node->data = original->data;
	new_node->lchild = swap(original->rchild);
	new_node->rchild = swap(original->lchild);

	return new_node;
}

bool equal(struct node* tree1, struct node* tree2)
{
	return ((!tree1 && !tree2) || (tree1 && tree2 &&
		tree1->data == tree2->data &&
		equal(tree1->lchild, tree2->lchild) &&
		equal(tree1->rchild, tree2->rchild)));
}

struct node* make_tree_by_random(int n)
{
	struct node* root, *parent;

	if (n <= 0)
		return NULL;

	root = (struct node*)malloc(sizeof(struct node));
	root->data = 1;
	root->lchild = root->rchild = NULL;

	for (int i = 2; i <= n; i++) {
		parent = root;
		while (1) {
			if (rand() % 2 == 0) {
				if (parent->lchild != NULL)
					parent = parent->lchild;
				else {
					parent->lchild = (struct node*)malloc(sizeof(struct node));
					parent->lchild->data = i;
					parent->lchild->lchild = parent->lchild->rchild = NULL;
					break;
				}
			}
			else {
				if (parent->rchild != NULL)
					parent = parent->rchild;
				else {
					parent->rchild = (struct node*)malloc(sizeof(struct node));
					parent->rchild->data = i;
					parent->rchild->lchild = parent->rchild->rchild = NULL;
					break;
				}
			}
		}
	}
	return root;
}

int height(struct node* root) //���� ��� �Լ�
{
	int depth = 0; //�ʱ� 0
	int lheight, rheight;

	if (root != NULL)
	{
		lheight = height(root->lchild); //���� ����Ʈ���� ����
		rheight = height(root->rchild); //������ ����Ʈ���� ����
		if (lheight > rheight)
			depth = 1 + lheight;
		else
			depth = 1 + rheight; //ū�ʿ� +1 ����
	}

	return depth; //���� ��ȯ
}

int node_num(struct node* root) //���� ��� �Լ�
{
	int count = 0; //�ʱ� ��� ����0
	if (root != NULL)
		count = 1 + node_num(root->lchild) + node_num(root->rchild); //���� ����Ʈ����
																	 //���� + ������ ����Ʈ���� ����+1

	return count; //���� ��ȯ
}

int leaf_node_num(struct node* root) //���� ���� ��� �Լ�
{
	int leaf_count = 0; //���� ��� ��

	if (root != NULL) { //�� Ʈ������
		if (!root->lchild && !root->rchild) //���� ������ ��ũ�� ��� NULL�̸�
			leaf_count = 1; //���ܳ���̹Ƿ� 1��
		else //�ؿ� ��尡 �� ������
			leaf_count = leaf_node_num(root->lchild) + leaf_node_num(root->rchild); //���� ����Ʈ���� ������ ����Ʈ���� ���� ��� ���� ����
	}

	return leaf_count; //���� ��� ���� ��ȯ
}