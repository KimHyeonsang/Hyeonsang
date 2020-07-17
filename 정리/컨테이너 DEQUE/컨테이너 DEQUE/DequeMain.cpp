#include<iostream>
#include<deque>
using namespace std;

void main()
{
	deque<int> dq(5);//n개의 갯수를 0으로 초기화 
	cout << "dq :";
	for (int i = 0; i < dq.size(); i++)
	{
		cout << dq[i] << " ";
	}
	cout << endl;
	deque<int>exdq1(5, 4);//n(5)개의 공간의 x(4)값으로 할당
	cout << "exdq1 :";
	for (int i = 0; i < exdq1.size(); i++)
	{
		cout << exdq1[i] << " ";
	}
	cout << endl;

	deque<int>exdq2(exdq1);//exdq1의 컨테이너 복사
	cout << "exdq2 :";
	for (int i = 0; i < exdq2.size(); i++)
	{
		cout << exdq2[i] << " ";
	}
	cout << endl;

	deque<int>exdq3(exdq2.begin(), exdq2.end() - 1);//exdq2.begin()에서  exdq2.end() - 1까지 초기화된 원소를 가진다.
	cout << "exdq3 :";
	for (int i = 0; i < exdq3.size(); i++)
	{
		cout << exdq3[i] << " ";
	}
	cout << endl;

	if (exdq1 == exdq2)
		cout << "같다" << endl;
	else
		cout << "다르다" << endl;

	dq.assign(5, 4);//x(4)를 5(n)개의 원소에 할당.
	cout << "dq :";
	for (int i = 0; i < dq.size(); i++)
	{
		cout << dq[i] << " ";
	}
	cout << endl;
	deque<int>exdq4;
	exdq4.assign(exdq2.begin(), exdq2.end() - 1);//구간b~e까지 담는다.
	cout << "exdq4 :";
	for (int i = 0; i < exdq4.size(); i++)
	{
		cout << exdq4[i] << " ";
	}
	cout << endl;
	cout << "exdq4의 3번쨰 자리의 값은 :" << exdq4.at(3) << endl;//at은 지정한 곳에 관하여 참조

	cout << "exdq4의 마지막 원소값은 :" << exdq4.back() << endl;

	deque<int>::iterator front;//deque의 반복자
	front = exdq4.begin();
	cout << *front << endl;
	
	/*deque<int>::iterator End;  //암튼 마지막에 있는 원소 출력
	End = exdq4.end();
	cout << *End << endl;*/

	exdq4.clear(); //원소를 모두 제거한다.

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

	cout << "exdq3의 첫번째 원소 참조 : " << exdq3.front() << endl;


	cout << "exdq3의 시작점에 3칸을 2의 값으로 삽입 : ";
	exdq3.insert(exdq3.begin(), 3, 2);
	for (int i = 0; i < exdq3.size(); i++)
	{
		cout << exdq3[i] << " ";
	}
	cout << endl;

	cout << "exdq3의  가르키는 위치에 반복자 구간을 삽입 : ";
	exdq3.insert(exdq3.begin(), exdq3.begin(), exdq3.end()-1);
	for (int i = 0; i < exdq3.size(); i++)
	{
		cout << exdq3[i] << " ";
	}
	cout << endl;
}