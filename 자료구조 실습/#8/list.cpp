#include "poly.h"
#include <stdlib.h>

POLY *avail;

POLY *getNode()
{
	POLY* new_node;

	if (avail) {
		new_node = avail;
		avail = avail->next;
	}
	else
		new_node = (POLY *)malloc(sizeof(POLY));

	return new_node;
}

void cerase(POLY** start)
{
	POLY* ptr;

	if (*start == NULL)
		return;

	ptr = *start;
	*start = (*start)->next;
	ptr->next = avail;
	avail = *start;
	*start = NULL;
}

void garbageCollect() //������ ����Ʈ�� ���� �޸𸮿� ��ȯ�ϴ� �Լ�
{
	POLY* ptr;
	for (ptr = avail; avail != NULL;) //avail�� NULL�϶� ����
	{
		avail = avail->next;
		free(ptr);
		ptr = avail; //��� ������ ���ʷ� ��ȯ�մϴ�.
	}
}