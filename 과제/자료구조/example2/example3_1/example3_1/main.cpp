//조건 1. 리스트를 생성 및 초기화 한 후 숫자를 입력하여 저장을 한다.
//조건 2. 리스트에 저장된 값을 합 과 평균을 계산후 출력한다.
//조건 3. 홀수값을 모두 제거
//조건 4. 제거를 한 뒤 출력한다.
#include <stdio.h>
#include "ArrayList.h"

void ListInit(List* plist)
{
	(plist->numOfData) = 0; // 리스트에 저장된 데이터의 수는 0!
	(plist->curPosition) = -1; // 현재 아무 위치도 가리키지 않음!
}

void Linsert(List* plist, LData data)
{
	if (plist->numOfData >= LIST_LEN) // 더 이상 저장할 공간이 없다면…
	{
		puts("저장이 불가능합니다.");
		return;
	}

	plist->arr[plist->numOfData] = data; // 데이터 저장
	(plist->numOfData)++; // 저장된 데이터의 수 증가
}

int LFirst(List* plist, LData* pdata) // 첫 번째 조회
{
	if (plist->numOfData == 0) // 저장된 데이터가 하나도 없다면!
		return FALSE;

	(plist->curPosition) = 0; // 참조 위치 초기화! 첫 번째 데이터의 참조를 의미!
	*pdata = plist->arr[0]; // pdata가 가리키는 공간에 데이터 저장

	return TRUE;
}

int LNext(List* plist, LData* pdata) // 두 번째 이후 조회
{
	if (plist->curPosition >= (plist->numOfData) - 1) // 더 이상 참조할 데이터가 없다면!
		return FALSE;

	(plist->curPosition)++;
	*pdata = plist->arr[plist->curPosition];

	return TRUE;
}

LData LRemove(List* plist)
{
	int rpos = plist->curPosition; // 삭제할 데이터의 인덱스 값 참조
	int num = plist->numOfData;
	LData rdata = plist->arr[rpos]; // 삭제할 데이터를 임시로 저장
									// 삭제를 위한 데이터의 이동을 진행하는 반복문
	for (int i = rpos; i < num - 1; i++)
		plist->arr[i] = plist->arr[i + 1];

	(plist->numOfData)--; // 데이터의 수 감소
	(plist->curPosition)--; // 참조 위치를 하나 되돌린다.
	return rdata;		   // 삭제된 데이터의 반환
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
		printf("1. 숫자를 입력하세요.\n");
		printf("2. 입력한 값의 합 과 평균 출력.\n");
		printf("3. 홀수값 모두 제거.\n");
		printf("4. 모두 출력.\n");
		printf("5. 종료.\n");
		scanf("%d", &Select);
		switch (Select)
		{
		case 1://리스트를 생성 및 초기화 한 후 숫자를 입력하여 저장을 한다.
			scanf("%d", &number);
			Linsert(list, number);
			break;
		case 2:// 리스트에 저장된 값을 합 과 곱을 계산후 출력한다.
			LFirst(list, &number); //처음걸 더하고 반복문으로 더하기
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
			Average = sum / list->numOfData; // 평균
			printf("합 : %d  평균 : %.2f", sum, Average);
			break;
		case 3://홀수값을 모두 제거
			LFirst(list, &number);
			printf("삭제된 값 : ");
			for (int i = 0; i < LIST_LEN; i++)
			{
				if (number % 2 != 0)
					printf("%d ,", LRemove(list));
				LNext(list, &number);
			}
			break;
		case 4://제거를 한 뒤 출력한다.
			for (int i = 0; i < LIST_LEN; i++)
				printf("%d ", list->arr[i]);
			break;
		case 5://종료
			return;
		}
	}
}