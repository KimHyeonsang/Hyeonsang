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


void DeleteTree(BTreeNode * bt, BTreeNode * DeleteNode)
{
	if (bt == NULL)    // bt가 NULL이면 재귀 탈출! 
		return;
	BTreeNode* deletenode;
	DeleteTree(bt->left, DeleteNode);

	if (bt->left == DeleteNode)//왼쪽경우
	{
		deletenode = bt->left;
		if (deletenode->left == NULL && deletenode->right == NULL)//왼쪽,오른쪽아무것도없을경우
		{
			free(deletenode);
			bt->left = NULL;
		}
		else if (deletenode->left != NULL)//왼쪽만 있을경우
		{
			bt->left = deletenode->left;
			free(deletenode);
		}
		else if (deletenode->right != NULL)//오른쪽만 있을경우
		{
			bt->left = deletenode->right;
			free(deletenode);
		}
		else if (deletenode->left != NULL && deletenode->right != NULL)//양쪽다 있는경우
		{
			BTreeNode* Child;
			Child = deletenode->right;
			while (1)
			{
				if (Child->left->left != NULL)
				{
					Child = Child->left;
				}
				else if (Child->left->left == NULL)
				{
					bt->left = Child->left;
					Child->left = NULL;
					bt->left->right = Child;
					free(deletenode);
				}
			}
		}
	}
	else if (bt->right == DeleteNode)//오른쪽경우
	{
		deletenode = bt->right;
		if (deletenode->left == NULL && deletenode->right == NULL)//왼쪽,오른쪽아무것도없을경우
		{
			free(deletenode);
			bt->right = NULL;
		}
		else if (deletenode->left != NULL)//왼쪽만 있을경우
		{
			bt->right = deletenode->left;
			free(deletenode);
		}
		else if (deletenode->right != NULL)//오른쪽만 있을경우
		{
			bt->right = deletenode->right;
			free(deletenode);
		}
		else if (deletenode->left != NULL && deletenode->right != NULL)//양쪽다 있는경우
		{
			BTreeNode* Child;
			Child = deletenode->right;
			while (1)
			{
				if (Child->left->left != NULL)
				{
					Child = Child->left;
				}
				else if (Child->left->left == NULL)
				{
					bt->right = Child->left;
					Child->left = NULL;
					bt->right->right = Child;
					free(deletenode);

				}
			}
		}
	}
	DeleteTree(bt->right, DeleteNode);;
}