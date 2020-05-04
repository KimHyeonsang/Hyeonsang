#include <stdio.h>
#include <stdlib.h>

typedef struct _node
{
	int data;
	struct _node * next;
} Node;
//Node *Head = NULL;

//Node *MakeNewNode(int score) 
//{ //��带 �ϳ� ���� �Ҵ�, �� �ʱ�ȭ 
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
//	else { //������ ��带 ã��, �� ��� �ڿ� new_node ���� 
//		Node *list = Head; //list�� �������̸� �ʱⰪ�� head 
//		while (list->next != NULL) //list�� link���� null�� ��� ���� 
//			list = list->next;
//		list->next = new_node;
//	}
//}
//void printNodes() {
//	for (Node *list = Head; list != NULL; list = list->next)
//		//list != NULL ��: ����Ʈ�� ������ ����Ű�� ������. list == NULL ��: ����Ʈ�� ����Ű�� ���̾��ٴ� �� 
//		printf("%d \n",& list->data);
//} 
//void findNode(int score) 
//{
//	for (Node *list = Head; list; list = list->next)
//		//C������ 0���� �������� ����. ���� list != NULL�� �׳� list�� ���� ��쵵 �ִ�. 
//		if (list->data == score)
//			printf("I found it : %d \n", &list->data);
//} //����Ʈ ���� ����� 
//void reverseList() 
//{ 
//	Node *p, *q, *r; 
//	p = Head; // p�� ���� ����Ű�� ���, q�� ���� ��� 
//	q = NULL; //
//	r = NULL; 
//	while (p != NULL)
//	{ 
//		r = q; // r�� q, q�� p�� ���ʷ� ���󰣴�. 
//		q = p;
//		p = p->next; // p�� �̸� �Ű� ����. 
//		q->next = r; // q�� ��ũ ������ �ٲ۴�. 
//	}
//	Head = q; // q�� �������� �� ����Ʈ�� ��� ������ //return Head; 
//}

int main(void)
{
//	Node *new_node;
//	int std_num; //�л��� 
//	printf("Student Number : "); 
//	scanf("%d", &std_num); //�л� �� �Է� 
//	for (int i = 0; i < std_num; i++) 
//	{ 
//		int score; 
//		printf("Student # %d  : ",i+1);
//		scanf("%d", &score); //��Ʈ ����, ���Ḯ��Ʈ�� �߰� 
//		new_node = MakeNewNode(score); 
//		insert_at_rear(new_node); 
//	} 
//	printNodes(); 
//	reverseList(); 
//	printf("AFTER REVERSING\n");
//	printNodes(); 
//}
	Node * head = NULL;    // NULL ������ �ʱ�ȭ
	Node * tail = NULL;
	Node * cur = NULL;

	Node * newNode = NULL;
	int readData;

	/**** �����͸� �Է� �޴� ���� ****/
	while (1)
	{
		printf("�ڿ��� �Է�: ");
		scanf("%d", &readData);
		if (readData < 1)
			break;

		/*** ����� �߰����� ***/
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

	/**** �Է� ���� �������� ��°��� ****/
	printf("�Է� ���� �������� ��ü���! \n");
	if (head == NULL)
	{
		printf("����� �ڿ����� �������� �ʽ��ϴ�. \n");
	}
	else
	{
		cur = head;
		printf("%d  ", cur->data);   // ù ��° ������ ���

		while (cur->next != NULL)    // �� ��° ������ ������ ���
		{
			cur = cur->next;
			printf("%d  ", cur->data);
		}
	}
	printf("\n\n");
	printf("�Է� ���� �������� ��ü ���! (����)\n");
	Node *p, *q, *r; 
	p = head; // p�� ���� ����Ű�� ���, q�� ���� ���
	q = NULL; //
	r = NULL; 
	while (p != NULL) 
	{ 
		r = q; // r�� q, q�� p�� ���ʷ� ���󰣴�. 
		q = p; 
		p = p->next; // p�� �̸� �Ű� ����. 
		q->next = r; // q�� ��ũ ������ �ٲ۴�. 
	} 
	head = q;
	if (head == NULL)
	{
		printf("����� �ڿ����� �������� �ʽ��ϴ�. \n");
	}
	else
	{
		cur = head;
		printf("%d  ", cur->data);   // ù ��° ������ ���

		while (cur->next != NULL)    // �� ��° ������ ������ ���
		{
			cur = cur->next;
			printf("%d  ", cur->data);
		}
	}
	printf("\n\n");

	/**** �޸��� �������� ****/
	if (head == NULL)
	{
		return 0;    // ������ ��尡 �������� �ʴ´�.
	}
	else
	{
		Node * delNode = head;
		Node * delNextNode = head->next;

		printf("%d��(��) �����մϴ�. \n", head->data);
		free(delNode);    // ù ��° ����� ����

		while (delNextNode != NULL)    // �� ��° ������ ��� ���� ���� �ݺ���
		{
			delNode = delNextNode;
			delNextNode = delNextNode->next;

			printf("%d��(��) �����մϴ�. \n", delNode->data);
			free(delNode);    // �� ��° ������ ��� ����
		}
	}

	return 0;
}