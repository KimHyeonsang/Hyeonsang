#include"chapter2.h"

NameCard * MakeNameCard(char * name, char * phone)
{
	NameCard* ArrayList;
	ArrayList = (NameCard*)malloc(sizeof(NameCard));
	strcpy(ArrayList->name, name);
	strcpy(ArrayList->phone, phone);
	return ArrayList;
}

void ShowNameCardInfo(NameCard * pcard)
{
	printf("이름 : %s  전화번호 : %s \n", pcard->name, pcard->phone);
}

int NameCompare(NameCard * pcard, char * name)
{
	if (strcmp(pcard->name, name) == 0)
		return true;
	else
		return false;
}

void ChangePhoneNum(NameCard * pcard, char * phone)
{
	if (strcmp(pcard->phone, phone) == 0)
		printf("이전과 같은 전화번호 입니다. 다시 입력해주세요.\n");
	else
		strcpy(pcard->phone, phone);
}

void main()
{
	char name[NAME_LEN], phone[PHONE_LEN];
	int count = 0;
	bool check = false;
	int select;
	NameCard* ArrayList[MAX];
	while (1)
	{
		system("cls");
		printf("1. 이름과 전화번호를 입력하세요\n");
		printf("2. 이름 조회\n");
		printf("3. 전화번호 변경\n");
		printf("4. 정보 삭제\n");
		printf("5. 전체 조회\n");
		printf("6. 종료\n");
		scanf("%d", &select);
		switch (select)
		{
		case 1:
			if (check == true)
				break;
			system("cls");
			ArrayList[0] = MakeNameCard("철수", "01012345678");
			ArrayList[0] = MakeNameCard("영희", "01056781234");
			ArrayList[0] = MakeNameCard("기철", "01013579246");
			check = true;
			system("pause");
			break;
		case 2:
			system("cls");
			printf("어떤사람을 찾으시나요?\n");
			scanf("%s", &name);
			for (int i = 0; i < MAX; i++)
			{
				if (NameCompare(ArrayList[i], name) == true)
					ShowNameCardInfo(ArrayList[i]);
			}
			system("pause");
			break;
		case 3:
			system("cls");
			printf("어떤사람을 찾으시나요?\n");
			scanf("%s", &name);
			for (int i = 0; i < MAX; i++)
			{
				if (NameCompare(ArrayList[i], name) == true)
				{
					while (1)
					{
						printf("무슨 전화번호로 하시겠습니까?\n");
						scanf("%s", &phone);
						ChangePhoneNum(ArrayList[i], phone);
						if (strcmp(ArrayList[i]->phone, phone) != 0)
							return;
					}
				}
			}
			system("pause");
			break;
		case 4:
			system("cls");
			printf("어떤사람을 찾으시나요?\n");
			scanf("%s", &name);
			for (int i = 0; i < MAX; i++)
			{
				if (NameCompare(ArrayList[i], name) == true)
				{
					if (ArrayList[i] != NULL)
					{
						free(ArrayList[i]);
						ArrayList[i] = NULL;
						printf("삭제했습니다.");
					}
				}
			}
			system("pause");
			break;
		case 5:
			for (int i = 0; i < MAX; i++)
					ShowNameCardInfo(ArrayList[i]);
			system("pause");
			break;
		case 6:
			for (int i = 0; i < MAX; i++)
			{
				if (ArrayList[i] != NULL)
				{
					free(ArrayList[i]);
					ArrayList[i] = NULL;
					printf("삭제했습니다.");
				}
			}
			return;
		}
	}
}