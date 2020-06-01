#include<stdio.h>
#include"DQ_Stack.h"
//스택 입력한 반대로 나간다
int main(void)
{
	Stack destack;
	DeStackInit(&destack);

	DSAdd(&destack, 1);
	DSAdd(&destack, 2);
	DSAdd(&destack, 3);
	DSAdd(&destack, 4);
	DSAdd(&destack, 5);

	printf("스택 구조 : ");
	while (!DSlsEmpty(&destack))
		printf("%d ", DQRemove(&destack));

	printf("\n");
}