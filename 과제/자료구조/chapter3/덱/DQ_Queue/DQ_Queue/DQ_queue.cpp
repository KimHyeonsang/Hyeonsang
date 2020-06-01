#include<stdio.h>
#include<stdlib.h>
#include"DQ_queue.h"

void DequeInit(Deque* pdeq)
{
	pdeq->head = NULL;
	pdeq->tail = NULL;
}

int DQlsEmpty(Deque * pdeq)
{
	if (pdeq->head == NULL)
		return TRUE;
	else
		return FALSE;
}

void DQAdd(Deque * pdeq, Data data)
{
	DQ* newNode = (DQ*)malloc(sizeof(DQ));
	newNode->data = data;

	newNode->prev = pdeq->tail;

	if (DQlsEmpty(pdeq))
		pdeq->head = newNode;
	else
		pdeq->tail->next = newNode;

	newNode->next = NULL;
	pdeq->tail = newNode;
}

Data DQRemove(Deque * pdeq)
{
	DQ* rnode = pdeq->head;
	Data rdata = pdeq->head->data;
	if (DQlsEmpty(pdeq))
	{
		printf("Deque Memory Error!");
		exit(-1);
	}
	pdeq->head = pdeq->head->next;
	free(rnode);

	if (pdeq->head == NULL)
	{
		pdeq->tail = NULL;
	}
	else
		pdeq->head->prev = NULL;
	return rdata;
}

Data DQGetFirst(Deque * pdeq)
{
	if (DQlsEmpty(pdeq))
	{
		printf("Deque Memory Error!");
		exit(-1);
	}

	return pdeq->head->data;
}