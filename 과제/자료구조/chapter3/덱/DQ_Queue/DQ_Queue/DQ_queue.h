#pragma once
#ifndef __C_DQ_QUEUE_H__
#define __C_DQ_QUEUE_H__

#define TRUE 1
#define FALSE 0
//큐는 입력하고 입력한 순서대로 출력
typedef int Data;

typedef struct _DQ_Queue
{
	Data data;
	struct _DQ_Queue * next;
	struct _DQ_Queue * prev;
}DQ;

typedef struct _dlDeque
{
	DQ * head;
	DQ* tail;
}DLDeque;

typedef DLDeque Deque;

void DequeInit(Deque* pdeq);
int DQlsEmpty(Deque* pdeq);

void DQAddFirst(Deque * pdeq, Data data);
void DQAdd(Deque* pdeq, Data data);

Data DQRemove(Deque * pdeq);

Data DQGetFirst(Deque * pdeq);
#endif