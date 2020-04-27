//���� 1. ����Ʈ�� ���� �� �ʱ�ȭ �� �� ���ڸ� �Է��Ͽ� ������ �Ѵ�.
//���� 2. ����Ʈ�� ����� ���� �� �� ����� ����� ����Ѵ�.
//���� 3. Ȧ������ ��� ����
//���� 4. ���Ÿ� �� �� ����Ѵ�.
#include <stdio.h>
#include "ArrayList.h"

void ListInit(List* plist)
{
	(plist->numOfData) = 0; // ����Ʈ�� ����� �������� ���� 0!
	(plist->curPosition) = -1; // ���� �ƹ� ��ġ�� ����Ű�� ����!
}

void Linsert(List* plist, LData data)
{
	if (plist->numOfData >= LIST_LEN) // �� �̻� ������ ������ ���ٸ顦
	{
		puts("������ �Ұ����մϴ�.");
		return;
	}

	plist->arr[plist->numOfData] = data; // ������ ����
	(plist->numOfData)++; // ����� �������� �� ����
}

int LFirst(List* plist, LData* pdata) // ù ��° ��ȸ
{
	if (plist->numOfData == 0) // ����� �����Ͱ� �ϳ��� ���ٸ�!
		return FALSE;

	(plist->curPosition) = 0; // ���� ��ġ �ʱ�ȭ! ù ��° �������� ������ �ǹ�!
	*pdata = plist->arr[0]; // pdata�� ����Ű�� ������ ������ ����

	return TRUE;
}

int LNext(List* plist, LData* pdata) // �� ��° ���� ��ȸ
{
	if (plist->curPosition >= (plist->numOfData) - 1) // �� �̻� ������ �����Ͱ� ���ٸ�!
		return FALSE;

	(plist->curPosition)++;
	*pdata = plist->arr[plist->curPosition];

	return TRUE;
}

LData LRemove(List* plist)
{
	int rpos = plist->curPosition; // ������ �������� �ε��� �� ����
	int num = plist->numOfData;
	LData rdata = plist->arr[rpos]; // ������ �����͸� �ӽ÷� ����
									// ������ ���� �������� �̵��� �����ϴ� �ݺ���
	for (int i = rpos; i < num - 1; i++)
		plist->arr[i] = plist->arr[i + 1];

	(plist->numOfData)--; // �������� �� ����
	(plist->curPosition)--; // ���� ��ġ�� �ϳ� �ǵ�����.
	return rdata;		   // ������ �������� ��ȯ
}

void main()
{
	int Select,number,Count = 0;
	int sum = 0;
	float Average = 0;
	List* list = (List*)malloc(sizeof(List));
	ListInit(list);
	while (1)
	{
		printf("1. ���ڸ� �Է��ϼ���.\n");
		printf("2. �Է��� ���� �� �� ��� ���.\n");
		printf("3. Ȧ���� ��� ����.\n");
		printf("4. ��� ���.\n");
		printf("5. ����.\n");
		scanf("%d", &Select);
		switch (Select)
		{
		case 1://����Ʈ�� ���� �� �ʱ�ȭ �� �� ���ڸ� �Է��Ͽ� ������ �Ѵ�.
			scanf("%d", &number);
			Linsert(list, number);
			break;
		case 2:// ����Ʈ�� ����� ���� �� �� ���� ����� ����Ѵ�.
			LFirst(list, &number); //ó���� ���ϰ� �ݺ������� ���ϱ�
			sum += number;
			for (int i = 0; i < list->numOfData; i++)
			{
				if (i == 0)
				{
					LFirst(list, &number);
					sum += number;
				}
				else
				{
					LNext(list, &number);
					sum += number;
				}
			}
			Average = sum / list->numOfData; // ���
			printf("�� : %d  ��� : %.2f", sum, Average);
			break;
		case 3://Ȧ������ ��� ����
			LFirst(list, &number);
			printf("������ �� : ");
			for (int i = 0; i < LIST_LEN; i++)
			{
				if (number % 2 != 0)
					printf("%d ,", LRemove(list));
				LNext(list, &number);
			}
			break;
		case 4://���Ÿ� �� �� ����Ѵ�.
			for (int i = 0; i < LIST_LEN; i++)
				printf("%d ", list->arr[i]);
			break;
		case 5://����
			return;
		}
	}
}