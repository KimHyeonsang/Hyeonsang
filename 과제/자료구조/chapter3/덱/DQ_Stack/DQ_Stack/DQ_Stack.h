#pragma once
#ifndef __C_DQ_STACK_H__
#define __C_DQ_STACK_H__

#define TRUE 1
#define FALSE 0
//ť�� �Է��ϰ� �Է��� ������� ���
typedef int Data;

typedef struct _DQ_Stack
{
	Data data;
	struct _DQ_Stack * next;
	struct _DQ_Stack * prev;
}DS;

typedef struct _dlStack
{
	DS * head;
	DS* tail;
}DLStack;

typedef DLStack Stack;

void DeStackInit(Stack* pdeq);
int DSlsEmpty(Stack* pdeq);
void DSAdd(Stack* pdeq, Data data);
Data DQRemove(Stack * pdeq);

#endif