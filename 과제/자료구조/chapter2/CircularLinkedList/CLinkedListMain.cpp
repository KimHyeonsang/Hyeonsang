#include <stdio.h>
#include <Windows.h>
#include "CLinkedList.h"
//직원 정보는 사번과 이름으로 구성
int main(void)
{
	// 원형 연결 리스트의 생성 및 초기화 ///////
	List list;
	int data, i, nodeNum;
	char* name;
	ListInit(&list);

	// 리스트에 5개의 데이터를 저장 /////// 
	LInsert(&list, 12345,"홍길동");
	LInsert(&list, 54231,"둘리");
	LInsert(&list, 45123,"또치");
	LInsert(&list, 55421,"기영");

	// 사원 리스트 출력 ///////
	if (LFirst(&list, &data,&name))
	{
		printf("사원 번호 : %d 이름 : %s\n", data , name);

		for (i = 0; i< LCount(&list) - 1; i++)
		{
			if (LNext(&list, &data,&name))
				printf("사원 번호 : %d 이름 : %s\n", data, name);
		}
	}
	printf("\n");

	printf("당직 순서 출력 (15일동안)\n");
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
	printf("홍길동의 당직을 찾고 7일뒤에 값을 나타냅니다.\n");
	
	nodeNum = LCount(&list);
	if (nodeNum != 0)
	{
		LFirst(&list, &data, &name);
		if (name == "홍길동")//이름이 같으면
		{
			FindList(&list, &name, 7);
			printf("%s\n", name);//날짜의 나머지를 알아내고
		}
		for (i = 0; i < nodeNum - 1; i++)
		{
			LNext(&list, &data, &name);
			if (name == "홍길동")
			{
				FindList(&list, &name, 7);
				printf("%s\n", name);//날짜의 나머지를 알아내고
			}				
		}
	}
	system("pause");
	return 0;
}