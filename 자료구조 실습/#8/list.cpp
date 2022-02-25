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

void garbageCollect() //가용노드 리스트내 노드들 메모리에 반환하는 함수
{
	POLY* ptr;
	for (ptr = avail; avail != NULL;) //avail이 NULL일때 까지
	{
		avail = avail->next;
		free(ptr);
		ptr = avail; //모든 노드들을 차례로 반환합니다.
	}
}