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
		printf("1~ 15 사이의 수를 입력해보세요.\n");
		scanf("%d", &data);
		if (data > 15)
			printf("입력 숫자가 높습니다.\n");
		else if (data < 1)
			printf("입력 숫자가 작습니다.\n");
		else
		{
			viewbtn = BSTSearch(BTN, data);
			if (viewbtn == NULL)
				printf("속한숫자가 없습니다.\n");
			else
			{
				printf("%d의 숫자를 찾았습니다.", viewbtn->data);
				break;
			}
		}
	}
	
}