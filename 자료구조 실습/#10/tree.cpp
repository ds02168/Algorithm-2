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
int height(struct node*);			// tree의 깊이
int node_num(struct node*);			// 노드 수
int leaf_node_num(struct node*);	// 리프 노드의 수

void main()
{
	int n;
	struct node* A, *B, *C, *D;

	srand(time(0));

	A = make_tree_by_code();
	B = copy(A);
	C = swap(A);

	printf("트리 A\n");
	printf("Inorder = [ ");
	inorder(A);
	printf("]\n\n");

	printf("Preorder = [ ");
	preorder(A);
	printf("]\n\n");

	printf("Postorder = [ ");
	postorder(A);
	printf("]\n\n");

	printf("트리 B = copy(A)\n");
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

	printf("트리 C = swap(A)\n");
	printf("Inorder = [ ");
	inorder(C);
	printf("]\n\n");

	printf("Preorder = [ ");
	preorder(C);
	printf("]\n\n");

	printf("Postorder = [ ");
	postorder(C);
	printf("]\n\n");

	printf("노드 수를 입력: ");
	scanf_s("%d", &n);
	D = make_tree_by_random(n);

	printf("트리 D :정수 %d개\n", n);
	printf("Inorder = [ ");
	inorder(D);
	printf("]\n\n");

	printf("Preorder = [ ");
	preorder(D);
	printf("]\n\n");

	
	printf("트리의 깊이 = %d\n", height(A));
	printf("트리에 있는 노드 수 = %d\n", node_num(A));
	printf("리프 노드의 수 = %d\n", leaf_node_num(A));
	
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

int height(struct node* root) //높이 계산 함수
{
	int depth = 0; //초기 0
	int lheight, rheight;

	if (root != NULL)
	{
		lheight = height(root->lchild); //왼쪽 서브트리의 높이
		rheight = height(root->rchild); //오른쪽 서브트리의 높이
		if (lheight > rheight)
			depth = 1 + lheight;
		else
			depth = 1 + rheight; //큰쪽에 +1 해줌
	}

	return depth; //높이 반환
}

int node_num(struct node* root) //노드수 계산 함수
{
	int count = 0; //초기 노드 갯수0
	if (root != NULL)
		count = 1 + node_num(root->lchild) + node_num(root->rchild); //왼쪽 서브트리의
																	 //노드수 + 오른쪽 서브트리의 노드수+1

	return count; //갯수 반환
}

int leaf_node_num(struct node* root) //말단 노드수 계산 함수
{
	int leaf_count = 0; //말단 노드 수

	if (root != NULL) { //빈 트리제외
		if (!root->lchild && !root->rchild) //왼쪽 오른쪽 링크가 모두 NULL이면
			leaf_count = 1; //말단노드이므로 1개
		else //밑에 노드가 더 있으면
			leaf_count = leaf_node_num(root->lchild) + leaf_node_num(root->rchild); //왼쪽 서브트리와 오른쪽 서브트리의 말단 노드 갯수 더함
	}

	return leaf_count; //말단 노드 갯수 반환
}