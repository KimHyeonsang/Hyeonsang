#include<stdio.h>
#include<stdlib.h>
#include"DQ_Stack.h"

void DeStackInit(Stack* pdeq)
{
	pdeq->head = NULL;
	pdeq->tail = NULL;
}

int DSlsEmpty(Stack * pdeq)
{
	if (pdeq->head == NULL)
		return TRUE;
	else
		return FALSE;
}

void DSAdd(Stack * pdeq, Data data)
{
	DS* newNode = (DS*)malloc(sizeof(DS));
	newNode->data = data;

	newNode->prev = pdeq->tail;

	if (DSlsEmpty(pdeq))
		pdeq->head = newNode;
	else
		pdeq->tail->next = newNode;

	newNode->next = NULL;
	pdeq->tail = newNode;
}

Data DQRemove(Stack * pdeq)
{
	DS* rnode = pdeq->tail;
	Data rdata = pdeq->tail->data;
	if (DSlsEmpty(pdeq))
	{
		printf("Stack Memory Error!");
		exit(-1);
	}
	pdeq->tail = pdeq->tail->prev;
	free(rnode);

	if (pdeq->tail == NULL)
	{
		pdeq->head = NULL;
	}
	else
		pdeq->tail->next = NULL;
	return rdata;
}
