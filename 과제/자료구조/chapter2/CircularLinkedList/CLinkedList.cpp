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

void LInsertFront(List * plist, Data data,char* Name)//������ �̵����� �ʰ� ��常 ����
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
	if (plist->tail == NULL)    // ����� ��尡 ���ٸ�
		return FALSE;

	plist->before = plist->tail;
	plist->cur = plist->tail->next;

	*pdata = plist->cur->Number;
	*name = plist->cur->Name;
	return TRUE;
}

int LNext(List * plist, Data * pdata, char** name)
{
	if (plist->tail == NULL)    // ����� ��尡 ���ٸ�
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

	if (rpos == plist->tail)    // ���� ����� tail�� ����Ų�ٸ�
	{
		if (plist->tail == plist->tail->next)    // �׸��� ������ ���� �����
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
void FindList(List* plist, char** name, Data number)//��¥�����ϴ³� ���
{
	int count = 0;
	Node * rpos = plist->cur;// ������ǥ �ӽ÷� ����
	Node * Before = plist->cur->next;//������ǥ �ӽ� ����
	if (rpos->Name == *name)
		count = number % LCount(plist);//���ڰ� ������
	while (count)
	{
		plist->before = plist->cur;
		plist->cur = plist->cur->next;
		if (count == 1)
		{
			*name = plist->cur->Name;
			plist->before = Before;//������� ����
			plist->cur = rpos;
		}
		count--;
	}
}
int LCount(List * plist)
{
	return plist->numOfData;
}