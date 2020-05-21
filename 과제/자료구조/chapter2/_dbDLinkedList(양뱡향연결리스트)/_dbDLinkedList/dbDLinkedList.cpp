#include<stdio.h>
#include<stdlib.h>
#include "dbDLinkedList.h"

void Listlnit(List* plist)
{
	plist->head = (Node*)malloc(sizeof(Node));//더미노드
	plist->cur = plist->head;
	plist->tail = (Node*)malloc(sizeof(Node));//더미
	plist->head->next = plist->tail;
	plist->head->prev = NULL;
	plist->tail->next = NULL;
	plist->tail->prev = plist->head;
	plist->numOfData = 0;
}

void LInsert(List* plist, Data data)
{
	Node* newNode = (Node*)malloc(sizeof(Node));//동적할당
	//Node* DomHead = plist->head;
	newNode->data = data;

	newNode->prev = plist->cur;
	if (plist->cur != NULL)
		plist->cur->next = newNode;
	newNode->next = plist->tail;
	if (plist->tail != NULL)
		plist->tail->prev = newNode;

	plist->cur = newNode;
	(plist->numOfData)++;
}

int LFirst(List* plist, Data* pdata)
{
	if (plist->head->next == NULL)
		return FALSE;

	plist->cur = plist->head->next;
	*pdata = plist->cur->data;
	return TRUE;
}

int LNext(List* plist, Data * pdata)
{
	if (plist->cur->next == NULL)
		return FALSE;
	if (plist->tail == plist->cur->next)
		return FALSE;
	plist->cur = plist->cur->next;
	*pdata = plist->cur->data;

	return TRUE;
}
int LList(List* plist, Data* pdata)
{
	if (plist->tail->prev == NULL)
		return FALSE;

	plist->cur = plist->tail->prev;
	*pdata = plist->cur->data;
	return TRUE;
}

int LPrevious(List* plist,Data *pdata)
{
	if (plist->cur->prev == NULL)
		return FALSE;
	if (plist->head == plist->cur->prev)
		return FALSE;
	plist->cur = plist->cur->prev;
	*pdata = plist->cur->data;

	return TRUE;
}

void LRemove(List* plist)
{ 
	Node* rpos = plist->cur->next;
	while (plist->cur->next != NULL)
	{
		plist->cur->prev = NULL;
		plist->cur = rpos;
		rpos = rpos->next;
	}
	plist->cur->prev = NULL;
}

int LCount(List * plist)
{
	return plist->numOfData;
}