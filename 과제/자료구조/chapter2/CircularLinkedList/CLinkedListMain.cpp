#include <stdio.h>
#include <Windows.h>
#include "CLinkedList.h"
//���� ������ ����� �̸����� ����
int main(void)
{
	// ���� ���� ����Ʈ�� ���� �� �ʱ�ȭ ///////
	List list;
	int data, i, nodeNum;
	char* name;
	ListInit(&list);

	// ����Ʈ�� 5���� �����͸� ���� /////// 
	LInsert(&list, 12345,"ȫ�浿");
	LInsert(&list, 54231,"�Ѹ�");
	LInsert(&list, 45123,"��ġ");
	LInsert(&list, 55421,"�⿵");

	// ��� ����Ʈ ��� ///////
	if (LFirst(&list, &data,&name))
	{
		printf("��� ��ȣ : %d �̸� : %s\n", data , name);

		for (i = 0; i< LCount(&list) - 1; i++)
		{
			if (LNext(&list, &data,&name))
				printf("��� ��ȣ : %d �̸� : %s\n", data, name);
		}
	}
	printf("\n");

	printf("���� ���� ��� (15�ϵ���)\n");
	if (LFirst(&list, &data, &name))
	{
		printf("%s ->", name);

		for (i = 0; i < LCount(&list)*4 - 2; i++)
		{
			if (LNext(&list, &data, &name))
				printf(" %s ->", name);
		}
	}
	printf("\n");
	printf("\n");
	printf("ȫ�浿�� ������ ã�� 7�ϵڿ� ���� ��Ÿ���ϴ�.\n");
	
	nodeNum = LCount(&list);
	if (nodeNum != 0)
	{
		LFirst(&list, &data, &name);
		if (name == "ȫ�浿")//�̸��� ������
		{
			FindList(&list, &name, 7);
			printf("%s\n", name);//��¥�� �������� �˾Ƴ���
		}
		for (i = 0; i < nodeNum - 1; i++)
		{
			LNext(&list, &data, &name);
			if (name == "ȫ�浿")
			{
				FindList(&list, &name, 7);
				printf("%s\n", name);//��¥�� �������� �˾Ƴ���
			}				
		}
	}
	system("pause");
	return 0;
}