#include<stdio.h>
#include"DQ_queue.h"

int main(void)
{
	Deque deq;
	DequeInit(&deq);

	DQAdd(&deq, 1);
	DQAdd(&deq, 2);
	DQAdd(&deq, 3);
	DQAdd(&deq, 4);
	DQAdd(&deq, 5);

	while (!DQlsEmpty(&deq))
		printf("%d ", DQRemove(&deq));

	printf("\n");
}