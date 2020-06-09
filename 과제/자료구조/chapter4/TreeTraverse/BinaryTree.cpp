#include <stdio.h>
#include <stdlib.h>
#include "BinaryTree.h"

BTreeNode * MakeBTreeNode(void)
{
	BTreeNode * nd = (BTreeNode*)malloc(sizeof(BTreeNode));

	nd->left = NULL;
	nd->right = NULL;
	return nd;
}

BTData GetData(BTreeNode * bt)
{
	return bt->data;
}

void SetData(BTreeNode * bt, BTData data)
{
	bt->data = data;
}

BTreeNode * GetLeftSubTree(BTreeNode * bt)
{
	return bt->left;
}

BTreeNode * GetRightSubTree(BTreeNode * bt)
{
	return bt->right;
}

void MakeLeftSubTree(BTreeNode * main, BTreeNode * sub)
{
	if (main->left != NULL)
		free(main->left);

	main->left = sub;
}

void MakeRightSubTree(BTreeNode * main, BTreeNode * sub)
{
	if (main->right != NULL)
		free(main->right);

	main->right = sub;
}

void DeleteTree(BTreeNode* main, BTreeNode* deleteNode)//������ ���
{
	if (main == NULL)    // bt�� NULL�̸� ��� Ż��! 
		return;

	DeleteTree(main->left, deleteNode);
	DeleteTree(main->right, deleteNode);
//	if (main->left == deleteNode)
//		testDeleteTree(main->left, deleteNode);
//	else if(main->right==deleteNode)
//		testDeleteTree(main->right, deleteNode);
	if (main->left == deleteNode)//���� �ε��϶�
	{
		BTreeNode* Node = main->left;
		if (Node->left == NULL && Node->right == NULL)//�ƹ��͵�������
		{
			free(Node);
			main->left = NULL;
		}
		else if (Node->left != NULL && Node->right == NULL)//�����ϳ�������
		{
			main->left = Node->left;
			free(Node);
		}
		else if (Node->left == NULL && Node->right != NULL)//�������ϳ�������
		{
			main->left = Node->right;
			free(Node);
		}
		else if (Node->left != NULL && Node->right != NULL)//�Ѵ� ������
		{
			BTreeNode* NextNode = Node->right;
			if (NextNode->left == NULL)
			{
				main->left = Node->right;
				main->left->left = Node->left;
				free(Node);
			}
			else
			{
				while (NextNode->left->left != NULL)
				{
					NextNode = NextNode->left;
				}
				main->left = NextNode->left;
				NextNode->left = NULL;
				main->left->right = Node->right;
				main->left->left = Node->left;
				free(Node);
			}

		}
	}
	else if (main->right == deleteNode)//���� �ε��϶�
	{
		BTreeNode* Node = main->right;
		if (Node->left == NULL && Node->right == NULL)//�ƹ��͵�������
		{
			free(Node);
			main->right = NULL;
		}
		else if (Node->left != NULL && Node->right == NULL)//�����ϳ�������
		{
			main->right = Node->left;
			free(Node);
		}
		else if (Node->left == NULL && Node->right != NULL)//�������ϳ�������
		{
			main->right = Node->right;
			free(Node);
		}
		else if (Node->left != NULL && Node->right != NULL)//�Ѵ� ������
		{
			BTreeNode* NextNode = Node->right;
			if (NextNode->left == NULL)
			{
				main->right = Node->right;
				main->right->left = Node->left;
				free(Node);
			}
			else
			{
				while (NextNode->left->left != NULL)
				{
					NextNode = NextNode->left;
				}
				main->right = NextNode->left;
				NextNode->left = NULL;
				main->right->right = Node->right;
				main->right->left = Node->left;
				free(Node);
			}
		}
	}
}