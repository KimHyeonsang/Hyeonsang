#include "Point.h"
#ifndef __ARRAY_LIST_H__
#define __ARRAY_LIST_H__
#define TRUE	1
#define FALSE	0

typedef int LData;

typedef struct _node
{
	LData data1;
	LData data2;
	struct _node * next;
} Node;

typedef struct _linkedList
{
	Node * head;
	Node * cur;
	Node * before;
	int numOfData;
	int(*comp)(LData d1, LData d2);
} LinkedList;


typedef LinkedList List;

void ListInit(List * plist);
void LInsert(List * plist, LData data1, LData data2);

int LFirst(List * plist, LData * pdata1, LData * pdata2);
int LNext(List * plist, LData * pdata1, LData * pdata2);

LData LRemove(List * plist);
int LCount(List * plist);

void SetSortRule(List * plist, int(*comp)(LData d1, LData d2));

#endif