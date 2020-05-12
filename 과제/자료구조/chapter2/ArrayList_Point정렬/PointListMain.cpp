#include <stdio.h>
#include <stdlib.h>
#include "ArrayList.h"
#include "Point.h"
int WholePrecede(LData d1, LData d2)//비교
{
	if (d1->xpos < d2->xpos)//x좌표가 다르면
		return 0;
	else if (d1->xpos == d2->xpos)//x좌표가 같으면
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

	/*** 4개의 데이터 저장 ***/
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


	/*** 저장된 데이터의 출력 ***/
	printf("현재 데이터의 수: %d \n", LCount(&list));
	printf("조건 1 x좌표의 값으로 오름차순\n");
	if (LFirst(&list, &ppos))
	{
		ShowPointPos(ppos);

		while (LNext(&list, &ppos))
			ShowPointPos(ppos);
	}
	printf("\n");

	/*** x좌표를 기준으로 오름차순 정렬***/
	//비교
/*	printf("조건 1 x좌표의 값으로 오름차순한 다음 y좌표 오름차순정렬\n");
	if (LFirst(&list, &ppos))//첫번쨰 구현
	{
		ShowPointPos(ppos);
		SetSortRule(&list, WholePrecede);
		while (LNext(&list, &ppos))//두번쨰..이후
			ShowPointPos(ppos);
	}
	printf("\n");*/
	/*** xpos가 2인 모든 데이터 삭제 ***/
	compPos.xpos = 2;
	compPos.ypos = 0;

	if (LFirst(&list, &ppos))
	{
		if (PointComp(ppos, &compPos) == 1)
		{
			//List에 구조체의 주소값이 저장된 경우
			//주소 값이 동적할당의 결과인경우를 구분해서 메모리 해제하는데는 무리가 있다.
			//소멸할 데이터를 반환하고 메모리를 해제 할 수 있는 기회를 주어야한다.
			//핵심을 주소값을 반환받고 직접 해제하는 코드를 작성하는것이 올바른 것이다.
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

	/*** 삭제 후 남은 데이터 전체 출력 ***/
	printf("현재 데이터의 수: %d \n", LCount(&list));

	if (LFirst(&list, &ppos))
	{
		ShowPointPos(ppos);

		while (LNext(&list, &ppos))
			ShowPointPos(ppos);
	}
	printf("\n");

	return 0;
}