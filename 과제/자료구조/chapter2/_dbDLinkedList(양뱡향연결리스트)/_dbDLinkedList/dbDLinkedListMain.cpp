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

	printf("������� ����\n");
	if (LFirst(&list, &data))
	{
		printf("%d ",data);
			while(LNext(&list,&data))
				printf("%d ", data);
			printf("\n\n");
	}
	printf("�������� ����\n");
	if (LList(&list, &data))
	{
		printf("%d ", data);
		while (LPrevious(&list, &data))
			printf("%d ", data);
		printf("\n\n");
	}
	printf("LPrevious ���� \n");
	LRemove(&list);
	printf("������� ����\n");
	if (LFirst(&list, &data))
	{
		printf("%d ", data);
		while (LNext(&list, &data))
			printf("%d ", data);
		printf("\n\n");
	}
	printf("�����ϰ� �������� ����\n");
	if (LList(&list, &data))
	{
		printf("%d ", data);
		while (LPrevious(&list, &data))
			printf("%d ", data);
		printf("\n\n");
	}
	if (LList(&list, &data) == FALSE)
		printf("���������� ���������ϴ�.\n");
	return 0;
}