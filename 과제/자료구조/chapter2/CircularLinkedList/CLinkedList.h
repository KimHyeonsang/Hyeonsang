#ifndef __C_LINKED_LIST_H__
#define __C_LINKED_LIST_H__

#define TRUE	1
#define FALSE	0



typedef int Data;

typedef struct _node
{
	Data Number;
	char* Name;
	struct _node * next;
} Node;

typedef struct _CLL
{
	Node * tail;
	Node * cur;
	Node * before;
	int numOfData;
} CList;


typedef CList List;

void ListInit(List * plist);

void LInsert(List * plist, Data data, char* Name);
void LInsertFront(List * plist, Data data, char* Name); // 두개 합칠시 enum을 추가해주면 유용

int LFirst(List * plist, Data * pdata, char** name);
int LNext(List * plist, Data * pdata, char** name);
Data LRemove(List * plist);
int LCount(List * plist);
void FindList(List* plist, char** name, Data  number);
#endif
