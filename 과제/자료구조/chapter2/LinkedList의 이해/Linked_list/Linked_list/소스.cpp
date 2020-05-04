#include <stdio.h>
#include <stdlib.h>

typedef struct _node
{
	int data;
	struct _node * next;
} Node;
//Node *Head = NULL;

//Node *MakeNewNode(int score) 
//{ //노드를 하나 동적 할당, 값 초기화 
//	Node *ptr; 
//	ptr = new Node(); 
//	ptr->data = score; 
//	ptr->next = NULL;
//	return ptr; 
//}
//void insert_at_rear(Node *new_node) 
//{
//	if (Head == NULL) 
//	{ 
//		Head = new_node;
//	}
//	else { //마지막 노드를 찾고, 그 노드 뒤에 new_node 연결 
//		Node *list = Head; //list는 포인터이며 초기값은 head 
//		while (list->next != NULL) //list의 link값이 null일 경우 끝남 
//			list = list->next;
//		list->next = new_node;
//	}
//}
//void printNodes() {
//	for (Node *list = Head; list != NULL; list = list->next)
//		//list != NULL 뜻: 리스트가 뭔가를 가리키고 있으면. list == NULL 뜻: 리스트가 가리키는 방이없다는 뜻 
//		printf("%d \n",& list->data);
//} 
//void findNode(int score) 
//{
//	for (Node *list = Head; list; list = list->next)
//		//C언어에서는 0만을 거짓으로 본다. 따라서 list != NULL을 그냥 list로 쓰는 경우도 있다. 
//		if (list->data == score)
//			printf("I found it : %d \n", &list->data);
//} //리스트 역순 만들기 
//void reverseList() 
//{ 
//	Node *p, *q, *r; 
//	p = Head; // p는 현재 가리키는 노드, q는 이전 노드 
//	q = NULL; //
//	r = NULL; 
//	while (p != NULL)
//	{ 
//		r = q; // r은 q, q는 p를 차례로 따라간다. 
//		q = p;
//		p = p->next; // p를 미리 옮겨 놓자. 
//		q->next = r; // q의 링크 방향을 바꾼다. 
//	}
//	Head = q; // q는 역순으로 된 리스트의 헤드 포인터 //return Head; 
//}

int main(void)
{
//	Node *new_node;
//	int std_num; //학생수 
//	printf("Student Number : "); 
//	scanf("%d", &std_num); //학생 수 입력 
//	for (int i = 0; i < std_num; i++) 
//	{ 
//		int score; 
//		printf("Student # %d  : ",i+1);
//		scanf("%d", &score); //노트 생성, 연결리스트에 추가 
//		new_node = MakeNewNode(score); 
//		insert_at_rear(new_node); 
//	} 
//	printNodes(); 
//	reverseList(); 
//	printf("AFTER REVERSING\n");
//	printNodes(); 
//}
	Node * head = NULL;    // NULL 포인터 초기화
	Node * tail = NULL;
	Node * cur = NULL;

	Node * newNode = NULL;
	int readData;

	/**** 데이터를 입력 받는 과정 ****/
	while (1)
	{
		printf("자연수 입력: ");
		scanf("%d", &readData);
		if (readData < 1)
			break;

		/*** 노드의 추가과정 ***/
		newNode = (Node*)malloc(sizeof(Node));
		newNode->data = readData;
		newNode->next = NULL;

		if (head == NULL)
			head = newNode;
		else
			tail->next = newNode;

		tail = newNode;
	}
	printf("\n");

	/**** 입력 받은 데이터의 출력과정 ****/
	printf("입력 받은 데이터의 전체출력! \n");
	if (head == NULL)
	{
		printf("저장된 자연수가 존재하지 않습니다. \n");
	}
	else
	{
		cur = head;
		printf("%d  ", cur->data);   // 첫 번째 데이터 출력

		while (cur->next != NULL)    // 두 번째 이후의 데이터 출력
		{
			cur = cur->next;
			printf("%d  ", cur->data);
		}
	}
	printf("\n\n");
	printf("입력 받은 데이터의 전체 출력! (역순)\n");
	Node *p, *q, *r; 
	p = head; // p는 현재 가리키는 노드, q는 이전 노드
	q = NULL; //
	r = NULL; 
	while (p != NULL) 
	{ 
		r = q; // r은 q, q는 p를 차례로 따라간다. 
		q = p; 
		p = p->next; // p를 미리 옮겨 놓자. 
		q->next = r; // q의 링크 방향을 바꾼다. 
	} 
	head = q;
	if (head == NULL)
	{
		printf("저장된 자연수가 존재하지 않습니다. \n");
	}
	else
	{
		cur = head;
		printf("%d  ", cur->data);   // 첫 번째 데이터 출력

		while (cur->next != NULL)    // 두 번째 이후의 데이터 출력
		{
			cur = cur->next;
			printf("%d  ", cur->data);
		}
	}
	printf("\n\n");

	/**** 메모리의 해제과정 ****/
	if (head == NULL)
	{
		return 0;    // 해제할 노드가 존재하지 않는다.
	}
	else
	{
		Node * delNode = head;
		Node * delNextNode = head->next;

		printf("%d을(를) 삭제합니다. \n", head->data);
		free(delNode);    // 첫 번째 노드의 삭제

		while (delNextNode != NULL)    // 두 번째 이후의 노드 삭제 위한 반복문
		{
			delNode = delNextNode;
			delNextNode = delNextNode->next;

			printf("%d을(를) 삭제합니다. \n", delNode->data);
			free(delNode);    // 두 번째 이후의 노드 삭제
		}
	}

	return 0;
}