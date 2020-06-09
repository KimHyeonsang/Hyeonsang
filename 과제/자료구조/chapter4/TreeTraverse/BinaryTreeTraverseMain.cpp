#include <stdio.h>
#include "BinaryTree.h"

void InorderTraverse(BTreeNode * bt)
{
	if (bt == NULL)    // bt가 NULL이면 재귀 탈출! 
		return;

	InorderTraverse(bt->left);
	printf("%d \n", bt->data);
	InorderTraverse(bt->right);
}

int main(void)
{
	BTreeNode * bt1 = MakeBTreeNode();
	BTreeNode * bt2 = MakeBTreeNode();
	BTreeNode * bt3 = MakeBTreeNode();
	BTreeNode * bt4 = MakeBTreeNode();
	BTreeNode* bt5 = MakeBTreeNode();
	BTreeNode* bt6 = MakeBTreeNode();
	BTreeNode* bt7 = MakeBTreeNode();
	BTreeNode* bt8 = MakeBTreeNode();
	BTreeNode* bt9 = MakeBTreeNode();

	SetData(bt1, 1);
	SetData(bt2, 2);
	SetData(bt3, 3);
	SetData(bt4, 4);
	SetData(bt5, 5);
	SetData(bt6, 6);
	SetData(bt7, 7);
	SetData(bt8, 8);
	SetData(bt9, 9);

	MakeLeftSubTree(bt1, bt2);
	MakeRightSubTree(bt1, bt3);
	MakeLeftSubTree(bt2, bt4);
	MakeRightSubTree(bt2, bt5);
	MakeLeftSubTree(bt5, bt6);
	MakeRightSubTree(bt5, bt7);
	MakeLeftSubTree(bt3, bt8);
	MakeRightSubTree(bt3, bt9);

	InorderTraverse(bt1);

	printf("삭제 할것\n");
	DeleteTree(bt1, bt2);
	InorderTraverse(bt1);
	return 0;
}