#include <stdio.h>
#include <stdlib.h>
#include "ArrayList.h"
#include "Point.h"
#include<crtdbg.h>
int main(void)
{
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
	List list;
	Point compPos;
	Point * ppos;

	ListInit(&list);

	/*** 4���� ������ ���� ***/
	ppos = (Point*)malloc(sizeof(Point));
	SetPointPos(ppos, 2, 1);
	LInsert(&list, ppos->xpos, ppos->ypos);

	ppos = (Point*)malloc(sizeof(Point));
	SetPointPos(ppos, 2, 2);
	LInsert(&list, ppos->xpos, ppos->ypos);

	ppos = (Point*)malloc(sizeof(Point));
	SetPointPos(ppos, 3, 1);
	LInsert(&list, ppos->xpos, ppos->ypos);

	ppos = (Point*)malloc(sizeof(Point));
	SetPointPos(ppos, 3, 2);
	LInsert(&list, ppos->xpos, ppos->ypos);

	/*** ����� �������� ��� ***/
	printf("���� �������� ��: %d \n", LCount(&list));

	if (LFirst(&list, &ppos->xpos,&ppos->ypos))
	{
		ShowPointPos(ppos);

		while (LNext(&list, &ppos->xpos, &ppos->ypos))
			ShowPointPos(ppos);
	}
	printf("\n");

	/*** xpos�� 2�� ��� ������ ���� ***/
	compPos.xpos = 2;
	compPos.ypos = 0;

	if (LFirst(&list, &ppos->xpos, &ppos->ypos))
	{
		if (PointComp(ppos, &compPos) == 1)
		{
			//List�� ����ü�� �ּҰ��� ����� ���
			//�ּ� ���� �����Ҵ��� ����ΰ�츦 �����ؼ� �޸� �����ϴµ��� ������ �ִ�.
			//�Ҹ��� �����͸� ��ȯ�ϰ� �޸𸮸� ���� �� �� �ִ� ��ȸ�� �־���Ѵ�.
			//�ٽ��� �ּҰ��� ��ȯ�ް� ���� �����ϴ� �ڵ带 �ۼ��ϴ°��� �ùٸ� ���̴�.
			LRemove(&list);
		//	free(ppos);
		}

		while (LNext(&list, &ppos->xpos, &ppos->ypos))
		{
			if (PointComp(ppos, &compPos) == 1)
			{
				LRemove(&list);
			//	free(ppos);
			}
		}
	}

	/*** ���� �� ���� ������ ��ü ��� ***/
	printf("���� �������� ��: %d \n", LCount(&list));

	if (LFirst(&list, &ppos->xpos, &ppos->ypos))
	{
		ShowPointPos(ppos);

		while (LNext(&list, &ppos->xpos, &ppos->ypos))
			ShowPointPos(ppos);
	}
	printf("\n");

	return 0;
}