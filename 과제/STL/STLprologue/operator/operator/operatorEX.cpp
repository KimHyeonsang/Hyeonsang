#include<iostream>
using namespace std;

class A
{
	int x;
public:
	A(int _x = 0) :x(_x) {}
	void print()
	{
		cout << x << endl;
	}
	int GetX()const
	{
		return x;
	}
	A operator++()
	{
		++x;
		return x;
	}
	A operator++(int)
	{
		x++;
		x++;
		return x;
	}
	A operator>(int target)
	{
		if (this->x > target)
		{
			return this->x;
		}
		else
			return target;
	}

	A operator-(const A target)
	{
		return this->x - target.x;
	}
};
const A operator*(const A& a, const A& b)
{
	return A(a.GetX() * b.GetX());
}

void main()
{
	A a(10);
	A frontresult;
	A frontresults;

	A backresult;
	A backresults;

	A example1;
	int count = 15;
	A b(20);
	A dert;

	A num;

	frontresult = ++a;//전위 연산자
	cout << "x 전위 연산 = ";
	frontresult.print();
	cout << endl;

	cout << "x 전위 연산 = ";
	frontresults = a.operator++();
	frontresults.print();
	cout << endl;

	cout << "x 후위 연산 = ";
	backresult = a++; //후위연산자
	backresult.print();
	cout << endl;

	cout << "x 후위 연산 = ";
	backresults = a.operator++(0);
	backresults.print();
	cout << endl;
	
	cout << "x a와 b의크기비교  = ";
	example1 = count;//비교
	example1.print();
	cout << endl;

	cout << "x의 a와 b를 뺀 값 = ";
	dert = a - b;
	dert.print();
	cout << endl;

	cout << "x의 a와 b를 곱한 값 = ";
	num = a * b;
	num.print();
	cout << endl;
}