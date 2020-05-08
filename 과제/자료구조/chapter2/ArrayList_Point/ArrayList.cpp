#include <stdio.h>
#include <stdlib.h>
#include "ArrayList.h"

void ListInit(List * plist)
{
	plist->head = (Node*)malloc(sizeof(Node));
	plist->head->next = NULL;
	plist->comp = NULL;
	plist->numOfData = 0;
}

void FInsert(List * plist, LData data1, LData data2)
{
	Node * newNode = (Node*)malloc(sizeof(Node));
	newNode->data1 = data1;
	newNode->data2 = data2;

	newNode->next = plist->head->next;
	plist->head->next = newNode;

	(plist->numOfData)++;
}

void SInsert(List * plist, LData data1, LData data2)
{
	Node * newNode = (Node*)malloc(sizeof(Node));
	Node * pred = plist->head;
	newNode->data1 = data1;
	newNode->data2 = data2;

	while (pred->next != NULL &&
		plist->comp(data1, pred->next->data1) != 0 &&
		plist->comp(data2, pred->next->data2) != 0)
	{
		pred = pred->next;
	}

	newNode->next = pred->next;
	pred->next = newNode;

	(plist->numOfData)++;
}


void LInsert(List * plist, LData data1,LData data2)
{
	if (plist->comp == NULL) // 정렬기준이 설정되어 있지 않으면..(정렬 기준이 없을 수도 있다.)
		FInsert(plist, data1,data2); // 머리에 Node를 추가!
	else
		SInsert(plist, data1,data2);
}
int LFirst(List * plist, LData * pdata1, LData * pdata2)
{
	if (plist->head->next == NULL)
		return FALSE;

	plist->before = plist->head;
	plist->cur = plist->head->next;

	*pdata1 = plist->cur->data1;
	*pdata2 = plist->cur->data2;
	return TRUE;
}

int LNext(List * plist, LData * pdata1, LData * pdata2)
{
	if (plist->cur->next == NULL)
		return FALSE;

	plist->before = plist->cur;
	plist->cur = plist->cur->next;

	*pdata1 = plist->cur->data1;
	*pdata2 = plist->cur->data2;
	return TRUE;
}

LData LRemove(List * plist)
{
	Node * rpos = plist->cur;
	LData rdata1 = rpos->data1;
	LData rdata2 = rpos->data2;
	plist->before->next = plist->cur->next;
	plist->cur = plist->before;

	free(rpos);
	(plist->numOfData)--;
	return rdata1;
}

int LCount(List * plist)
{
	return plist->numOfData;
}

void SetSortRule(List * plist, int(*comp)(LData d1, LData d2))
{

}