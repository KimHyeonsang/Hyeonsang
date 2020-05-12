#include <stdio.h>
#include <stdlib.h>
#include "ArrayList.h"
#include "Point.h"
int WholePrecede(LData d1, LData d2)//��
{
	if (d1->xpos < d2->xpos)//x��ǥ�� �ٸ���
		return 0;
	else if (d1->xpos == d2->xpos)//x��ǥ�� ������
	{
		if (d1->ypos < d2->ypos)
			return 0;
		else
			return 1;
	}
	else
		return 1;
}

int main(void)
{
	List list;
	Point compPos;
	Point * ppos;

	ListInit(&list);

	/*** 4���� ������ ���� ***/
	SetSortRule(&list, WholePrecede);
	ppos = (Point*)malloc(sizeof(Point));
	SetPointPos(ppos, 2, 4);
	LInsert(&list, ppos);


	ppos = (Point*)malloc(sizeof(Point));
	SetPointPos(ppos, 3, 2);
	LInsert(&list, ppos);


	ppos = (Point*)malloc(sizeof(Point));
	SetPointPos(ppos, 2, 2);
	LInsert(&list, ppos);


	ppos = (Point*)malloc(sizeof(Point));
	SetPointPos(ppos, 3, 1);
	LInsert(&list, ppos);


	/*** ����� �������� ��� ***/
	printf("���� �������� ��: %d \n", LCount(&list));
	printf("���� 1 x��ǥ�� ������ ��������\n");
	if (LFirst(&list, &ppos))
	{
		ShowPointPos(ppos);

		while (LNext(&list, &ppos))
			ShowPointPos(ppos);
	}
	printf("\n");

	/*** x��ǥ�� �������� �������� ����***/
	//��
/*	printf("���� 1 x��ǥ�� ������ ���������� ���� y��ǥ ������������\n");
	if (LFirst(&list, &ppos))//ù���� ����
	{
		ShowPointPos(ppos);
		SetSortRule(&list, WholePrecede);
		while (LNext(&list, &ppos))//�ι���..����
			ShowPointPos(ppos);
	}
	printf("\n");*/
	/*** xpos�� 2�� ��� ������ ���� ***/
	compPos.xpos = 2;
	compPos.ypos = 0;

	if (LFirst(&list, &ppos))
	{
		if (PointComp(ppos, &compPos) == 1)
		{
			//List�� ����ü�� �ּҰ��� ����� ���
			//�ּ� ���� �����Ҵ��� ����ΰ�츦 �����ؼ� �޸� �����ϴµ��� ������ �ִ�.
			//�Ҹ��� �����͸� ��ȯ�ϰ� �޸𸮸� ���� �� �� �ִ� ��ȸ�� �־���Ѵ�.
			//�ٽ��� �ּҰ��� ��ȯ�ް� ���� �����ϴ� �ڵ带 �ۼ��ϴ°��� �ùٸ� ���̴�.
			ppos = LRemove(&list);
			free(ppos);
		}

		while (LNext(&list, &ppos))
		{
			if (PointComp(ppos, &compPos) == 1)
			{
				ppos = LRemove(&list);
				free(ppos);
			}
		}
	}

	/*** ���� �� ���� ������ ��ü ��� ***/
	printf("���� �������� ��: %d \n", LCount(&list));

	if (LFirst(&list, &ppos))
	{
		ShowPointPos(ppos);

		while (LNext(&list, &ppos))
			ShowPointPos(ppos);
	}
	printf("\n");

	return 0;
}