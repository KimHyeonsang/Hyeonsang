#include"BinarySearchTree.h"
#include"BinaryTree.h"
#include<stdio.h>
#include<stdlib.h>

void main()
{
	BTreeNode* BTN;
	BTreeNode* viewbtn;
	int data;
	BSTMakeAndInit(&BTN);
	BSTInsert(&BTN, 10);
	BSTInsert(&BTN, 15);
	BSTInsert(&BTN, 7);
	BSTInsert(&BTN, 12);
	BSTInsert(&BTN, 8);

	
	while (1)
	{
		printf("1~ 15 ������ ���� �Է��غ�����.\n");
		scanf("%d", &data);
		if (data > 15)
			printf("�Է� ���ڰ� �����ϴ�.\n");
		else if (data < 1)
			printf("�Է� ���ڰ� �۽��ϴ�.\n");
		else
		{
			viewbtn = BSTSearch(BTN, data);
			if (viewbtn == NULL)
				printf("���Ѽ��ڰ� �����ϴ�.\n");
			else
			{
				printf("%d�� ���ڸ� ã�ҽ��ϴ�.", viewbtn->data);
				break;
			}
		}
	}
	
}