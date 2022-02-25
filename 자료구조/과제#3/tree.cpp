#pragma warning(disable:4996)
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 500
#define BUF_SIZE 50
#define START_A 97
#define END_Z 122

using namespace std;

struct node {
	char* data;
	int num = 0;
	struct node* lchild;
	struct node* rchild;
};

class Binary_Search {
public:
	int count;
	struct node* start;
	Binary_Search() {
		count = 0;
		start = NULL;
	}
	void Read_Data();
	void insert(char*);
	struct node* modified_search(struct node*, char*);
	void Print_tree();
	void Inorder(struct node*, FILE*);
	void Search_tree();
	struct node* iterSearch(struct node*, char*);
	struct node* find_parent(struct node*, char*);
	void Delete_tree();
	void one_delete(struct node**, struct node**);
	void two_delete(struct node**, struct node**);
	void three_delete(struct node**, struct node**);
	int height_tree(struct node*);
};


void Binary_Search::Read_Data() {
	char name[20];
	FILE* fp;
	char buf[MAX_SIZE];
	char* word;
	const char* delim = " %.,-_'\"?!()[]:\t\n;";

	printf("파일 이름? ");
	scanf("%s", name);


	if ((fp = fopen(name, "r")) == NULL) {
		printf("실패!! 존재하지 않는 파일입니다.");
		exit(1);
	}

	while (!feof(fp))
	{
		fgets(buf, MAX_SIZE, fp);

		word = strtok(buf, delim);

		while (word != NULL)
		{
			strlwr(word);
			Binary_Search::insert(word);

			word = strtok(NULL, delim);
		}
	}

	fclose(fp);
}

void Binary_Search::insert(char* word)
{
	char fir = word[0];
	struct node* root, * ptr, * parent;

	if (fir >= START_A && fir <= END_Z)
	{
		root = this->start;
		parent = Binary_Search::modified_search(root, word);

		if (parent || !root) {
			ptr = (struct node*)malloc(sizeof(struct node));
			ptr->data = (char*)malloc(strlen(word) + 1);
			strcpy(ptr->data, word);
			ptr->num = 1;
			ptr->lchild = ptr->rchild = NULL;
			this->count++;


			if (root) {
				if (strcmp(word, parent->data) < 0)
					parent->lchild = ptr;
				else
					parent->rchild = ptr;
			}
			else {
				this->start = ptr;
			}
		}

	}
}

struct node* Binary_Search::modified_search(struct node* root, char* word)
{
	for (struct node* ptr = root; ptr != NULL;) {
		if (strcmp(ptr->data, word) == 0) {
			ptr->num++;
			return NULL;
		}
		if (strcmp(word, ptr->data) < 0) {
			if (ptr->lchild == NULL) return ptr;
			else ptr = ptr->lchild;
		}
		else {
			if (ptr->rchild == NULL) return ptr;
			else ptr = ptr->rchild;
		}
	}
	return NULL;
}

void Binary_Search::Print_tree()
{
	char name[20];
	FILE* fp2;

	printf("저장할 파일의 이름 :");
	scanf("%s", name);

	if ((fp2 = fopen(name, "w")) == NULL)
	{
		printf("실패!! 파일에 저장할 수 없습니다.\n");
		return;
	}


	Binary_Search::Inorder(this->start, fp2);

	fprintf(fp2, "\n트리에 저장된 단어 수: %d\n", this->count);
	fprintf(fp2, "루트 노드의 단어 : %s", this->start->data);

	fclose(fp2);
}

void Binary_Search::Inorder(struct node* root, FILE* fp2)
{
	if (root != NULL)
	{
		Binary_Search::Inorder(root->lchild, fp2);
		fprintf(fp2, "%s : %d\n", root->data, root->num);
		Binary_Search::Inorder(root->rchild, fp2);
	}
}

void Binary_Search::Search_tree()
{
	char Search[BUF_SIZE];
	struct node* root = this->start;

	printf("찾고자 하는 단어? ");
	scanf("%s", Search);

	root = iterSearch(root, Search);
	if (root == NULL) {
		printf("실패!! 단어가 존재하지 않습니다.\n");
		return;
	}

	printf("%s : %d\n", root->data, root->num);
}

struct node* Binary_Search::iterSearch(struct node* tree, char* word)
{
	while (tree != NULL) {
		if (strcmp(word, tree->data) == 0) return tree;
		if (strcmp(word, tree->data) < 0)
			tree = tree->lchild;
		else
			tree = tree->rchild;
	}
	return NULL;
}

void Binary_Search::Delete_tree()
{
	char Search[BUF_SIZE];
	struct node* ptr;
	struct node* parent;
	struct node* root = this->start;

	printf("단어 삭제: ");
	scanf("%s", Search);

	ptr = iterSearch(root, Search);
	if (ptr == NULL) {
		printf("단어가 존재하지 않습니다.\n");
		return;
	}
	parent = Binary_Search::find_parent(root, Search);

	if (!ptr->lchild && !ptr->rchild)
		Binary_Search::one_delete(&ptr, &parent);

	else if ((!ptr->lchild && ptr->rchild) || (ptr->lchild && !ptr->rchild))
		Binary_Search::two_delete(&ptr, &parent);

	else if (ptr->lchild && ptr->rchild)
		Binary_Search::three_delete(&ptr, &parent);

	else
	{
		printf("실패!! 삭제 ERROR");
		return;
	}

	printf("%s : %d 단어 삭제\n", ptr->data, ptr->num);

	this->count--;
	free(ptr);
}

struct node* Binary_Search::find_parent(struct node* root, char* word)
{
	for (struct node* ptr = root; ptr != NULL;)
	{
		if (ptr->lchild != NULL)
			if (strcmp(ptr->lchild->data, word) == 0)
				return ptr;

		if (ptr->rchild != NULL)
			if (strcmp(ptr->rchild->data, word) == 0)
				return ptr;

		if (strcmp(word, ptr->data) < 0)
			ptr = ptr->lchild;
		else
			ptr = ptr->rchild;
	}

	return NULL;
}

void Binary_Search::one_delete(struct node** ptr, struct node** parent)
{
	if ((*parent)->lchild == *ptr)
		(*parent)->lchild = NULL;
	else
		(*parent)->rchild = NULL;

}
void Binary_Search::two_delete(struct node** ptr, struct node** parent)
{
	if ((*parent)->lchild == *ptr)
	{
		if ((*ptr)->lchild != NULL)
			(*parent)->lchild = (*ptr)->lchild;
		else
			(*parent)->lchild = (*ptr)->rchild;
	}
	else
	{
		if ((*ptr)->lchild != NULL)
			(*parent)->rchild = (*ptr)->lchild;
		else
			(*parent)->rchild = (*ptr)->rchild;
	}
}

void Binary_Search::three_delete(struct node** ptr, struct node** parent)
{
	struct node* temp;
	struct node* tempp;
	struct node* root = this->start;

	if (height_tree((*ptr)->lchild) > height_tree((*ptr)->rchild))
	{
		temp = (*ptr)->lchild;
		while (temp->rchild != NULL)
			temp = temp->rchild;
	}
	else
	{
		temp = (*ptr)->rchild;
		while (temp->lchild != NULL)
			temp = temp->lchild;
	}

	tempp = Binary_Search::find_parent(root, temp->data);

	if (!temp->lchild && !temp->rchild)
		one_delete(&temp, &tempp);


	else if ((!temp->lchild && temp->rchild) || (temp->lchild && !temp->rchild))
		two_delete(&temp, &tempp);

	temp->lchild = (*ptr)->lchild;
	temp->rchild = (*ptr)->rchild;
	if ((*parent)->lchild == (*ptr))
		(*parent)->lchild = temp;
	else
		(*parent)->rchild = temp;
}

int Binary_Search::height_tree(struct node* ptr) {
	int depth = 0;
	int ldepth, rdepth;
	if (ptr != NULL) {
		ldepth = height_tree(ptr->lchild);
		rdepth = height_tree(ptr->rchild);
		if (ldepth > rdepth)
			depth = ldepth + 1;
		else
			depth = rdepth + 1;
	}

	return depth;
}



void main(void)
{
	int menu;

	printf("컴퓨터공학과 21712184_유태형\n");

	Binary_Search bins;

	while (true)
	{
		printf("1: 입력, 2: 출력, 3: 검색, 4: 삭제, 5: 종료 ? ");
		scanf("%d", &menu);
		switch (menu) {
		case 1: bins.Read_Data(); break;
		case 2: bins.Print_tree(); break;
		case 3: bins.Search_tree(); break;
		case 4: bins.Delete_tree(); break;
		case 5: printf("프로그램을 종료합니다.\n"); return;
		default: printf("1에서 5사이 정수를 입력해주세요.\n");
		}
	}
}
