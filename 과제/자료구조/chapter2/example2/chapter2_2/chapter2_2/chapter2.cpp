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
	printf("�̸� : %s  ��ȭ��ȣ : %s \n", pcard->name, pcard->phone);
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
		printf("������ ���� ��ȭ��ȣ �Դϴ�. �ٽ� �Է����ּ���.\n");
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
		printf("1. �̸��� ��ȭ��ȣ�� �Է��ϼ���\n");
		printf("2. �̸� ��ȸ\n");
		printf("3. ��ȭ��ȣ ����\n");
		printf("4. ���� ����\n");
		printf("5. ��ü ��ȸ\n");
		printf("6. ����\n");
		scanf("%d", &select);
		switch (select)
		{
		case 1:
			if (check == true)
				break;
			system("cls");
			ArrayList[0] = MakeNameCard("ö��", "01012345678");
			ArrayList[0] = MakeNameCard("����", "01056781234");
			ArrayList[0] = MakeNameCard("��ö", "01013579246");
			check = true;
			system("pause");
			break;
		case 2:
			system("cls");
			printf("������ ã���ó���?\n");
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
			printf("������ ã���ó���?\n");
			scanf("%s", &name);
			for (int i = 0; i < MAX; i++)
			{
				if (NameCompare(ArrayList[i], name) == true)
				{
					while (1)
					{
						printf("���� ��ȭ��ȣ�� �Ͻðڽ��ϱ�?\n");
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
			printf("������ ã���ó���?\n");
			scanf("%s", &name);
			for (int i = 0; i < MAX; i++)
			{
				if (NameCompare(ArrayList[i], name) == true)
				{
					if (ArrayList[i] != NULL)
					{
						free(ArrayList[i]);
						ArrayList[i] = NULL;
						printf("�����߽��ϴ�.");
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
					printf("�����߽��ϴ�.");
				}
			}
			return;
		}
	}
}