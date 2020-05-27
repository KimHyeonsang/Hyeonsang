#include<stdio.h>
#include"ex_Stack.h"
int main(void)
{
	List stack;
	int nodeNum,data;
	ListInit(&stack);

	LInsert(&stack, 1); LInsert(&stack, 2);
	LInsert(&stack, 3); LInsert(&stack, 4);
	LInsert(&stack, 5);

	nodeNum = LCount(&stack);
	LFirst(&stack, &data);//1부터시작
	while (nodeNum)
	{
		if (nodeNum == 1)
		{
			printf("%d ", LRemove(&stack));
			nodeNum = LCount(&stack);
		}
		if (LFirst(&stack, &data))
		{
			for (int i = 0; i < nodeNum - 1; i++)
			{
				LNext(&stack, &data);
				if (i == nodeNum - 2)
				{					
					printf("%d ", LRemove(&stack));
					nodeNum = LCount(&stack);
				}
					
			}
		}
	}
	return 0;

}