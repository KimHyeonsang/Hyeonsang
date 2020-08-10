#include<iostream>
#include<deque>
using namespace std;

void main()
{
	deque<int> dq(5);//n���� ������ 0���� �ʱ�ȭ 
	cout << "dq :";
	for (int i = 0; i < dq.size(); i++)
	{
		cout << dq[i] << " ";
	}
	cout << endl;
	deque<int>exdq1(5, 4);//n(5)���� ������ x(4)������ �Ҵ�
	cout << "exdq1 :";
	for (int i = 0; i < exdq1.size(); i++)
	{
		cout << exdq1[i] << " ";
	}
	cout << endl;

	deque<int>exdq2(exdq1);//exdq1�� �����̳� ����
	cout << "exdq2 :";
	for (int i = 0; i < exdq2.size(); i++)
	{
		cout << exdq2[i] << " ";
	}
	cout << endl;

	deque<int>exdq3(exdq2.begin(), exdq2.end() - 1);//exdq2.begin()����  exdq2.end() - 1���� �ʱ�ȭ�� ���Ҹ� ������.
	cout << "exdq3 :";
	for (int i = 0; i < exdq3.size(); i++)
	{
		cout << exdq3[i] << " ";
	}
	cout << endl;

	if (exdq1 == exdq2)
		cout << "����" << endl;
	else
		cout << "�ٸ���" << endl;

	dq.assign(5, 4);//x(4)�� 5(n)���� ���ҿ� �Ҵ�.
	cout << "dq :";
	for (int i = 0; i < dq.size(); i++)
	{
		cout << dq[i] << " ";
	}
	cout << endl;
	deque<int>exdq4;
	exdq4.assign(exdq2.begin(), exdq2.end() - 1);//����b~e���� ��´�.
	cout << "exdq4 :";
	for (int i = 0; i < exdq4.size(); i++)
	{
		cout << exdq4[i] << " ";
	}
	cout << endl;
	cout << "exdq4�� 3���� �ڸ��� ���� :" << exdq4.at(3) << endl;//at�� ������ ���� ���Ͽ� ����

	cout << "exdq4�� ������ ���Ұ��� :" << exdq4.back() << endl;

	deque<int>::iterator front;//deque�� �ݺ���
	front = exdq4.begin();
	cout << *front << endl;
	
	/*deque<int>::iterator End;  //��ư �������� �ִ� ���� ���
	End = exdq4.end();
	cout << *End << endl;*/

	exdq4.clear(); //���Ҹ� ��� �����Ѵ�.

	if (exdq4.empty())
		cout << "clear" << endl;
	exdq3.erase(exdq3.begin()+2);
	cout << "exdq3 :";
	for (int i = 0; i < exdq3.size(); i++)
	{
		cout << exdq3[i] << " ";
	}
	cout << endl;

	exdq3.erase(exdq3.begin(), exdq3.end() - 1);
	cout << "exdq3 :";
	for (int i = 0; i < exdq3.size(); i++)
	{
		cout << exdq3[i] << " ";
	}
	cout << endl;

	cout << "exdq3�� ù��° ���� ���� : " << exdq3.front() << endl;


	cout << "exdq3�� �������� 3ĭ�� 2�� ������ ���� : ";
	exdq3.insert(exdq3.begin(), 3, 2);
	for (int i = 0; i < exdq3.size(); i++)
	{
		cout << exdq3[i] << " ";
	}
	cout << endl;

	cout << "exdq3��  ����Ű�� ��ġ�� �ݺ��� ������ ���� : ";
	exdq3.insert(exdq3.begin(), exdq3.begin(), exdq3.end()-1);
	for (int i = 0; i < exdq3.size(); i++)
	{
		cout << exdq3[i] << " ";
	}
	cout << endl;
}