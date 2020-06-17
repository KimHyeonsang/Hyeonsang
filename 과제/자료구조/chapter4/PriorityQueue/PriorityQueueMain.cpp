#include <stdio.h>
#include<string.h>
#include<Windows.h>
#include "PriorityQueue.h"

int DataPriorityComp(const char* ch1,const char *ch2)
{
	if(strlen(ch2) != strlen(ch1))//길이가 다를 경우
		return strlen(ch2) - strlen(ch1);
	else //같을 경우
	{
		for (int i = 0; i < strlen(ch2); i++)
		{
			if (ch1[i] != ch2[i])
			{
				return ch2 - ch1;
			}
		}
	}
}

int main(void)
{
	PQueue pq;
	char Ccrr[CHAR_LEN];
	PQueueInit(&pq, DataPriorityComp);
	PEnqueue(&pq, "apple");
	PEnqueue(&pq, "banana");
	PEnqueue(&pq, "peach");

	PEnqueue(&pq, "Strawberry");
	PEnqueue(&pq, "Kiwi");
	PEnqueue(&pq, "tangerine");

	while (!PQIsEmpty(&pq))
		printf("%s \n", PDequeue(&pq));

	system("pause");
	return 0;
}
