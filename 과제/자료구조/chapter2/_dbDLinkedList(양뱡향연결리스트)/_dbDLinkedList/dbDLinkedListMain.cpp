#include"dbDLinkedList.h"
#include<stdio.h>


int main(void)
{
	List list;
	int data;
	Listlnit(&list);

	LInsert(&list, 20); 
	LInsert(&list, 30);
	LInsert(&list, 40); 

	printf("순서대로 나열\n");
	if (LFirst(&list, &data))
	{
		printf("%d ",data);
			while(LNext(&list,&data))
				printf("%d ", data);
			printf("\n\n");
	}
	printf("역순으로 나열\n");
	if (LList(&list, &data))
	{
		printf("%d ", data);
		while (LPrevious(&list, &data))
			printf("%d ", data);
		printf("\n\n");
	}
	printf("LPrevious 삭제 \n");
	LRemove(&list);
	printf("순서대로 나열\n");
	if (LFirst(&list, &data))
	{
		printf("%d ", data);
		while (LNext(&list, &data))
			printf("%d ", data);
		printf("\n\n");
	}
	printf("삭제하고 역순으로 나열\n");
	if (LList(&list, &data))
	{
		printf("%d ", data);
		while (LPrevious(&list, &data))
			printf("%d ", data);
		printf("\n\n");
	}
	if (LList(&list, &data) == FALSE)
		printf("역순연결이 끊어졌습니다.\n");
	return 0;
}