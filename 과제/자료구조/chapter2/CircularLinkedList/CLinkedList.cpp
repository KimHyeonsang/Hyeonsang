#include <stdio.h>
#include <stdlib.h>
#include "CLinkedList.h"

void ListInit(List * plist)
{
	plist->tail = NULL;
	plist->cur = NULL;
	plist->before = NULL;
	plist->numOfData = 0;
}

void LInsertFront(List * plist, Data data,char* Name)//꼬리는 이동하지 않고 헤드만 변경
{
	Node * newNode = (Node*)malloc(sizeof(Node));
	newNode->Number = data;
	newNode->Name = Name;

	if (plist->tail == NULL)
	{
		plist->tail = newNode;
		newNode->next = newNode;
	}
	else
	{
		newNode->next = plist->tail->next;
		plist->tail->next = newNode;
	}

	(plist->numOfData)++;
}

void LInsert(List * plist, Data data,char* Name)
{
	Node * newNode = (Node*)malloc(sizeof(Node));
	newNode->Number = data;
	newNode->Name = Name;

	if (plist->tail == NULL)
	{
		plist->tail = newNode;
		newNode->next = newNode;
	}
	else
	{
		newNode->next = plist->tail->next;
		plist->tail->next = newNode;
		plist->tail = newNode;
	}

	(plist->numOfData)++;
}

int LFirst(List * plist, Data * pdata,char** name)
{
	if (plist->tail == NULL)    // 저장된 노드가 없다면
		return FALSE;

	plist->before = plist->tail;
	plist->cur = plist->tail->next;

	*pdata = plist->cur->Number;
	*name = plist->cur->Name;
	return TRUE;
}

int LNext(List * plist, Data * pdata, char** name)
{
	if (plist->tail == NULL)    // 저장된 노드가 없다면
		return FALSE;

	plist->before = plist->cur;
	plist->cur = plist->cur->next;

	*pdata = plist->cur->Number;
	*name = plist->cur->Name;
	return TRUE;
}

Data LRemove(List * plist)
{
	Node * rpos = plist->cur;
	Data rdata = rpos->Number;

	if (rpos == plist->tail)    // 삭제 대상을 tail이 가리킨다면
	{
		if (plist->tail == plist->tail->next)    // 그리고 마지막 남은 노드라면
			plist->tail = NULL;
		else
			plist->tail = plist->before;
	}

	plist->before->next = plist->cur->next;
	plist->cur = plist->before;

	free(rpos);
	(plist->numOfData)--;
	return rdata;
}
void FindList(List* plist, char** name, Data number)//날짜를원하는날 당번
{
	int count = 0;
	Node * rpos = plist->cur;// 현재좌표 임시로 저장
	Node * Before = plist->cur->next;//꼬리좌표 임시 저장
	if (rpos->Name == *name)
		count = number % LCount(plist);//숫자가 같으면
	while (count)
	{
		plist->before = plist->cur;
		plist->cur = plist->cur->next;
		if (count == 1)
		{
			*name = plist->cur->Name;
			plist->before = Before;//원래대로 만듬
			plist->cur = rpos;
		}
		count--;
	}
}
int LCount(List * plist)
{
	return plist->numOfData;
}