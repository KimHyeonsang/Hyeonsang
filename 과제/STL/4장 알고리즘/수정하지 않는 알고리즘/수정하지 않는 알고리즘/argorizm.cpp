#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

//����1
//void main()
//{
//	vector<int> v;
//	v.push_back(10);
//	v.push_back(20);
//	v.push_back(30);
//	v.push_back(30);
//	v.push_back(40);
//	v.push_back(40);
//	v.push_back(50);
//
//	for (vector<int>::size_type i = 0; i < v.size(); ++i)
//		cout << v[i] << " ";
//	cout << endl;
//
//	vector<int>::iterator iter;
//	//����[v.begin(),v.end())���� ���� ���ҿ� ���� ���Ұ� �������� ù��° �ݺ��ڸ� ��ȯ
//	iter = adjacent_find(v.begin(), v.end());
//
//	if (iter != v.end())
//		cout << *iter << endl;
//
//	for (; iter != v.end(); ++iter)
//		cout << *iter << " ";
//	cout << endl;
//}


//���� 2 adjacent_find
//void main()
//{
//	vector<int> v;
//	v.push_back(10);
//	v.push_back(20);
//	v.push_back(30);
//	v.push_back(40);
//	v.push_back(50);
//
//	for (vector<int>::size_type i = 0; i < v.size(); ++i)
//		cout << v[i] << " ";
//	cout << endl;
//
//	vector<int>::iterator iter;
//	vector<int>::iterator iter_b = v.begin();
//	vector<int>::iterator iter_e = v.begin() + 2;
//
//	//�����Ѱ� �ִ��� ã�� ����ϴ� �ݺ���
//	iter = adjacent_find(iter_b, iter_e);
//
//	if (iter != iter_e)// ������ ���ۺ��� 2ĭ�� 30������ Ȯ���ϴµ� ���� iter�� ������ Ž���Ͽ� 30�̰� iter_e�� 30������ �´�ǥ��
//		cout << *iter << endl;
//
//	cout << "==============" << endl;
//	//�̰� iter�� iter_e���� Ž���� �Ͽ� 30�̶�� ���ڰ� �������� ������ Ž���� �Ͽ� ���ڰ� ����� �Ǿ���.
//	if (iter != v.end())
//		cout << *iter << endl;
//
//	iter_b = v.begin();
//	iter_e = v.end();
//	iter = adjacent_find(iter_b, iter_e);
//
//	//�Ѵ� ��� ���� �ʴ´�.
//	if (iter != iter_e)
//		cout << *iter << endl;
//	if (iter != v.end())
//		cout << *iter << endl;
//}

//����3 adjaoent_find ����

//bool Pred(int a, int b)
//{
//	return abs(b - a) > 10; //abs�� ���밪
//}
//void main()
//{
//	vector<int>v;
//	v.push_back(10);
//	v.push_back(20);
//	v.push_back(30);
//	v.push_back(50);
//	v.push_back(90);
//
//	for (vector<int>::size_type i = 0; i < v.size(); ++i)
//		cout << v[i] << " ";
//	cout << endl;
//
//	vector<int>::iterator iter;
//	iter = adjacent_find(v.begin(), v.end(), Pred);
//
//	if (iter != v.end())
//		cout << *iter << endl;
//
//	for (; iter != v.end(); ++iter)
//		cout << *iter << " ";
//	cout << endl;
//
//}

//���� 4(count ����)
//void main()
//{
//	vector<int> v;
//	v.push_back(10);
//	v.push_back(20);
//	v.push_back(30);
//	v.push_back(40);
//	v.push_back(30);
//	v.push_back(50);
//
//	for (vector<int>::size_type i = 0; i < v.size(); ++i)
//		cout << v[i] << " ";//�� ���
//	cout << endl;
//
//	int n = count(v.begin(), v.end(), 30);//30�� ���ۺ��� ������ � �ִ°�
//	cout << "30�� ����:" << n << endl;
//}

//����5 (count_if ��������)
//bool Pred(int n)
//{
//	return 25 < n;
//}
//void main()
//{
//	vector<int> v;
//	v.push_back(10);
//	v.push_back(20);
//	v.push_back(30);
//	v.push_back(40);
//	v.push_back(50);
//
//	for (vector<int>::size_type i = 0; i < v.size(); ++i)
//		cout << v[i] << " ";
//	cout << endl;
//
//	int n = count_if(v.begin(), v.end(), Pred);
//	cout << "25���� ū ������ ����:" << n << endl;
//}

//����6 equal()�� v1�� ���۰� ���� �˰� v2�� ù��°�� �Է��ϸ�  v1�� ũ�� ��ŭ ���� �� ������ ��

//void main()
//{
//	vector<int> v1;
//	v1.push_back(10);
//	v1.push_back(20);
//	v1.push_back(30);
//
//	vector<int>v2;
//	v2.push_back(10);
//	v2.push_back(20);
//	v2.push_back(30);
//	v2.push_back(40);
//	v2.push_back(50);
//
//	cout << "v1 :";
//	for (vector<int>::size_type i = 0; i < v1.size(); ++i)
//		cout << v1[i] << " ";
//	cout << endl;
//
//	cout << "v2 :";
//	for (vector<int>::size_type i = 0; i < v2.size(); ++i)
//		cout << v2[i] << " ";
//	cout << endl;
//
//	if (equal(v1.begin(), v1.end(), v2.begin()))
//		cout << "�� �������� �����ϴ�" << endl;
//	else
//		cout << "�� �������� ���� �ʽ��ϴ�" << endl;
//}


//���� 7  equal()������ �޸� �����ȿ� ù������ ù���� ���� ���ϰ� ������ ������ ��ȯ�Ѵ�
//bool Pred(int left, int right)
//{
//	return abs(right - left) < 5;
//}
//void main()
//{
//	vector<int> v1;
//	v1.push_back(10);
//	v1.push_back(24);
//	v1.push_back(30);
//	vector<int> v2;
//	v2.push_back(10);
//	v2.push_back(20);
//	v2.push_back(33);
//	cout << "v1 : ";
//	for (vector<int>::size_type i = 0; i < v1.size(); ++i)
//		cout << v1[i] << " ";
//	cout << endl;
//	cout << "v2 : ";
//	for (vector<int>::size_type i = 0; i < v2.size(); ++i)
//		cout << v2[i] << " ";
//	cout << endl;
//	//���� [v1.being(), v1.end)�� ���� [v2.begin(), v2.begin()+3)��
//	//�� �մϴ�.
//	if (equal(v1.begin(), v1.end(), v2.begin(), Pred))
//		cout << "�� �������� �����ϴ�." << endl;
//}

//���� 8  find(),find_if()��

//bool Pred(int n)
//{
//	return 35 < n;
//}
//
//void main()
//{
//	vector<int> v;
//	v.push_back(10);
//	v.push_back(20);
//	v.push_back(30);
//	v.push_back(40);
//	v.push_back(50);
//
//	for (vector<int>::size_type i = 0; i < v.size(); ++i)
//		cout << v[i] << " ";
//	cout << endl;
//
//	vector<int>::iterator iter;
//	iter = find(v.begin(), v.end(), 20); //20�� ã�°�
//
//	if (iter != v.end())
//		cout << *iter << "�� ã��!" << endl;
//
//	iter = find_if(v.begin(), v.end(), Pred); // 35���� ū���߿� ù��°���� ã��
//	if (iter != v.end())
//		cout << "���������� 35���� ū ù��° ����: " << *iter << endl;
//}

//����9 find_end() v2�� v1���� ��ġ �ϴ°��߿� ������ �������� ù���� �ݺ����̴�.
//void main()
//{
//	vector<int> v1;
//	v1.push_back(0);
//	v1.push_back(2);
//	v1.push_back(4);
//	v1.push_back(6);
//	v1.push_back(8);
//	v1.push_back(10);
//	v1.push_back(2);
//	v1.push_back(4);
//	v1.push_back(6);
//	v1.push_back(8);
//
//	vector<int> v2;
//	v2.push_back(2);
//	v2.push_back(4);
//	v2.push_back(10);
//
//	vector<int>::iterator iter;
//
//	iter = find_end(v1.begin(), v1.end(), v2.begin(), v2.end());
//
//	if (iter != v1.end())
//	{
//		cout << "iter :" << *iter << endl;
//		cout << "iter-1 :" << *(iter - 1) << endl;
//		cout << "iter+1 :" << *(iter + 1) << endl;
//	}
//}


//���� 10 find_end()�� �ڿ��� �ѿ��ҿ� �Ѱ��� ���ϰ� ������ ��ĭ �ö󰡼� �ٽ� ���Ѵ�
//bool Pred(int left, int right)
//{
//	return left <= right;
//}
//void main()
//{
//	vector<int> v1;
//	v1.push_back(10);
//	v1.push_back(15);
//	v1.push_back(20);
//	v1.push_back(40);
//	v1.push_back(50);
//	v1.push_back(60);
//	v1.push_back(10);
//	v1.push_back(11);
//	v1.push_back(12);
//	v1.push_back(80);
//
//	vector<int> v2;
//	v2.push_back(40);
//	v2.push_back(50);
//	v2.push_back(60);
//
//	vector<int>::iterator iter;
//	iter = find_end(v1.begin(), v1.end(), v2.begin(), v2.end(), Pred);
//	if (iter != v1.end())
//	{
//		// ��ġ�ϴ� ������ �������� ù ������ �ݺ��� iter
//		cout << "iter : " << *iter << endl;
//		cout << "iter-1 : " << *(iter - 1) << endl;
//		cout << "iter+1 : " << *(iter + 1) << endl;;
//	}
//}

//����11 find_first_of()�� v1�� ���� �ϳ��� v2�� ��� ���� Ȯ��
//void main()
//{
//	vector<int>v1;
//	v1.push_back(10);
//	v1.push_back(20);
//	v1.push_back(30);
//	v1.push_back(40);
//	v1.push_back(50);
//
//	vector<int>v2;
//	v2.push_back(40);
//	v2.push_back(80);
//	v2.push_back(20);
//
//	cout << "v1:";
//	for (vector<int>::size_type i = 0; i < v1.size(); ++i)
//		cout << v1[i] << " ";
//	cout << endl;
//	cout << "v2:";
//	for (vector<int>::size_type i = 0; i < v2.size(); ++i)
//		cout << v2[i] << " ";
//	cout << endl;
//
//	vector<int>::iterator iter;
//	iter = find_first_of(v1.begin(), v1.end(), v2.begin(), v2.end());
//
//	if (iter != v1.end())
//		cout << "iter: " << *iter << endl;
//}

//���� 12 find_first_of() ����
//bool Pred(int left, int right)
//{
//	return left > (right*1.5);
//}

//void main()
//{
//	vector<int> v1;
//	v1.push_back(10);
//	v1.push_back(20);
//	v1.push_back(30);
//	v1.push_back(40);
//	v1.push_back(50);
//
//	vector<int>v2;
//	v2.push_back(40);
//	v2.push_back(80);
//	v2.push_back(20);
//
//	cout << "v1:";
//	for (vector<int>::size_type i = 0; i < v1.size(); ++i)
//		cout << v1[i] << " ";
//	cout << endl;
//
//	cout << "v2:";
//	for (vector<int>::size_type i = 0; i < v2.size(); ++i)
//		cout << v2[i] << " ";
//	cout << endl;
//
//	vector<int>::iterator iter;
//	iter = find_first_of(v1.begin(), v1.end(), v2.begin(), v2.end(), Pred);
//
//	if (iter != v1.end())
//		cout << "iter :" << *iter << endl;
//}

//���� 13 for_each() ~����  ~����� 

//void Print(int n)
//{
//	cout << n << " ";
//}
//
//void main()
//{
//	vector<int>v;
//	v.push_back(10);
//	v.push_back(20);
//	v.push_back(30);
//	v.push_back(40);
//	v.push_back(50);
//
//	for_each(v.begin(), v.begin() + 2, Print);
//	cout << endl;
//	for_each(v.begin(), v.begin() + 4, Print);
//	cout << endl;
//
//	for_each(v.begin(), v.end(), Print);
//	cout << endl;
//}

//���� 14 for_each ����

//class PrintFunctor
//{
//	char fmt;
//public:
//	explicit PrintFunctor(char c = ' ') : fmt(c) { }
//	void operator ()(int n) const
//	{
//		cout << n << fmt;
//	}
//};
//void main()
//{
//	vector<int> v;
//	v.push_back(10);
//	v.push_back(20);
//	v.push_back(30);
//	v.push_back(40);
//	v.push_back(50);
//	for_each(v.begin(), v.end(), PrintFunctor()); // ������ ������ ' '��
//	cout << endl;
//	for_each(v.begin(), v.end(), PrintFunctor(','));// ������ ������ ','��
//	cout << endl;
//	for_each(v.begin(), v.end(), PrintFunctor('\n'));// ������ ������ '\n'��
//	cout << endl;
//}

//���� 15  lexlcographlcal_compare() �켱 ��

//void main()
//{
//	vector<int>v1;
//	v1.push_back(10);
//	v1.push_back(20);
//	v1.push_back(30);
//
//	vector<int> v2;
//	v2.push_back(10);
//	v2.push_back(20);
//	v2.push_back(50);
//
//	vector<int> v3;
//	v3.push_back(10);
//	v3.push_back(20);
//	v3.push_back(30);
//
//	if (lexicographical_compare(v1.begin(), v1.end(), v2.begin(), v2.end()))
//		cout << "v1<v2" << endl;
//	else
//		cout << "v1>=v2" << endl;
//
//	if (lexicographical_compare(v1.begin(), v1.end(), v3.begin(), v3.end()))
//		cout << "v1<v3" << endl;
//	else
//		cout << "v1>=v3" << endl;
//}

//���� 16
//template< typename T>
//struct Less
//{
//	bool operator()(const T& left, const T& right) const
//	{
//		return left < right;
//	}
//};
//
//void main()
//{
//	vector<int> v1;
//	v1.push_back(10);
//	v1.push_back(20);
//	v1.push_back(30);
//	vector<int> v2;
//	v2.push_back(10);
//	v2.push_back(25);
//	v2.push_back(30);
//	if (lexicographical_compare(v1.begin(), v1.end(), v2.begin(), v2.end(), less<int>()))
//		cout << "���� less v1�� v2�� ��: true" << endl;
//	else
//		cout << "���� less v1�� v2�� ��: false" << endl;
//	if (lexicographical_compare(v1.begin(), v1.end(), v2.begin(), v2.end(), greater<int>()))
//		cout << "���� greater v1�� v2�� ��: true" << endl;
//	else
//		cout << "���� greater v1�� v2�� ��: false" << endl;
//	if (lexicographical_compare(v1.begin(), v1.end(), v2.begin(), v2.end(), Less<int>()))
//		cout << "����� ���� Less v1�� v2�� ��: true" << endl;
//	else
//		cout << "����� ���� Less v1�� v2�� ��: false" << endl;
//}

//���� 17 max(),min()
//class Point
//{
//	int x, y;
//public:
//	explicit Point(int _x = 0, int _y = 0) :x(_x), y(_y) {}
//	int GetX()const { return x; }
//	int GetY()const { return y; }
//	void Print()const { cout << "(" << x << "," << y << ")" << endl; }
//};
//bool XCompare(const Point& left, const Point& right)
//{
//	return left.GetX() < right.GetX();
//}
//bool YCompare(const Point& left, const Point& right)
//{
//	return left.GetY() < right.GetY();
//}
//void main()
//{
//	int a = 10, b = 20;
//	int r;
//	r = max(a, b);
//	cout << "max:" << r << endl;
//
//	r = min(a, b);
//	cout << "min:" << r << endl;
//
//	Point pt1(5, 8), pt2(3, 9);
//	Point pt3;
//
//	pt3 = max(pt1, pt2, XCompare);
//	cout << "x max:"; pt3.Print();
//
//	pt3 = max(pt1, pt2, YCompare);
//	cout << "y max"; pt3.Print();
//}


//���� 18 max_element(), min_element() �˰��� ��� ����
//���;ȿ� ������ �񱳸� �Ͽ� ū�� ������ ��
//void main()
//{
//	vector<int>v;
//	v.push_back(30);
//	v.push_back(10);
//	v.push_back(20);
//	v.push_back(50);
//	v.push_back(40);
//
//	vector<int>::iterator iter;
//	iter = max_element(v.begin(), v.end());
//	cout << *iter << endl;
//
//	iter = min_element(v.begin(), v.end());
//	cout << *iter << endl;
//}

//���� 19 ���ϴ°��� true�̸� ������ �������� ���� ó������ �񱳸� �Ѵ�
//class Point
//{
//	int x, y;
//public:
//	explicit Point(int _x = 0, int _y = 0) :x(_x), y(_y) { }
//	int GetX() const { return x; }
//	int GetY() const { return y; }
//	void Print() const
//	{
//		cout << '(' << x << ',' << y << ')' << endl;
//	}
//};
//
//bool Compare(const Point& left, const Point& right)
//{
//	if (left.GetX() < right.GetX())
//		return true;
//	else if (left.GetX() > right.GetX())
//		return false;
//	else
//		return left.GetY() < right.GetY();
//}
//void main()
//{
//	vector<Point> v;
//	v.push_back(Point(3, 2));
//	v.push_back(Point(4, 5));
//	v.push_back(Point(5, 5));
//	v.push_back(Point(3, 3));
//	v.push_back(Point(3, 2));
//	vector<Point>::iterator iter;
//	iter = max_element(v.begin(), v.end(), Compare);
//	cout << "max: "; iter->Print(); //�ݺ��ڰ� ����Ű�� ��ü�� ����� -> �����ڷ� ����
//	cout << "max: "; (*iter).Print(); //���� ����
//}


//���� 20  ���⼭ Pred���� ���� �ٸ��� ���� ������ mismatch(����ġ)�ϸ� ���� ���� ���´�.
//bool Pred(int left, int right)
//{
//	return abs(right - left) <= 5;
//}
//
//void main()
//{
//	vector<int>v1;
//	v1.push_back(10);
//	v1.push_back(20);
//	v1.push_back(30);
//	v1.push_back(40);
//	v1.push_back(50);
//
//	vector<int> v2;
//	v2.push_back(11);
//	v2.push_back(25);
//	v2.push_back(33);
//	v2.push_back(46);
//	v2.push_back(50);
//
//	pair<vector<int>::iterator, vector<int>::iterator> iter_pair;
//	iter_pair = mismatch(v1.begin(), v1.end(), v2.begin(), Pred);
//
//	cout << "v1:" << *iter_pair.first << "," << "v2:" << *iter_pair.second << endl;
//
//}


//���� 21  search()�� find_end() �ʹ� �ݴ��̴�.find_end()�ڿ��� Ȯ��search�� �տ��� Ȯ��

//void main()
//{
//	vector<int> v1;
//	v1.push_back(10);
//	v1.push_back(20);
//	v1.push_back(30);
//	v1.push_back(40);
//	v1.push_back(50);
//	v1.push_back(60);
//	v1.push_back(70);
//	v1.push_back(30);
//	v1.push_back(40);
//	v1.push_back(50);
//
//	vector<int> v2;
//	v2.push_back(30);
//	v2.push_back(40);
//	v2.push_back(50);
//
//	vector<int>::iterator iter;
//	iter = search(v1.begin(), v1.end(), v2.begin(), v2.end());
//	if (iter != v1.end())
//	{
//		// ��ġ�ϴ� ù ��° �������� ù ������ �ݺ��� iter
//		cout << "iter : " << *iter << endl;
//		cout << "iter-1 : " << *(iter - 1) << endl;
//		cout << "iter+1 : " << *(iter + 1) << endl;
//	}
//}//���� 22bool Pred(int left, int right){	return abs(right - left) <= 5;}void main(){	vector<int>v;	v.push_back(10);	v.push_back(20);	v.push_back(30);	v.push_back(30);	v.push_back(30);	v.push_back(40);	v.push_back(50);	vector<int>::iterator iter;	iter = search_n(v.begin(), v.end(), 3, 30,Pred);	if (iter != v.end())	{		cout << "iter: " << *iter << endl;		cout << "iter-1:" << *(iter - 1) << endl;		cout << "iter+1:" << *(iter + 1) << endl;	}}