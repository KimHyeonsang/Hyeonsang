#include<stdio.h>
#include"DQ_Stack.h"
//���� �Է��� �ݴ�� ������
int main(void)
{
	Stack destack;
	DeStackInit(&destack);

	DSAdd(&destack, 1);
	DSAdd(&destack, 2);
	DSAdd(&destack, 3);
	DSAdd(&destack, 4);
	DSAdd(&destack, 5);

	printf("���� ���� : ");
	while (!DSlsEmpty(&destack))
		printf("%d ", DQRemove(&destack));

	printf("\n");
}