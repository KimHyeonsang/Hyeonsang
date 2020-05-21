#pragma once
#ifndef __DBD_LINKED_LIST_H__
#define __DBD_LINKED_LIST_H__
#define TRUE 1
#define FALSE 0

typedef int Data;

typedef struct _node
{
	Data data;
	struct _node* next;
	struct _node* prev;
}Node;

typedef struct _dbdLinkedList
{
	Node * head;
	Node * tail;
	Node * cur;
	int numOfData;
}DBDLinkedList;

typedef DBDLinkedList List;

void Listlnit(List* plist);
void LInsert(List* plist, Data data);//꼬리에 노드를 추가

int LFirst(List * plist, Data* pdata);
int LNext(List* plist, Data* pdata);
int LPrevious(List * plist, Data * pdata);
int LList(List *plist, Data* pdata);
void LRemove(List* plist);//앞서 참조가 이뤄진 노드를 삭제한다.
int LCount(List* plist);
#endif