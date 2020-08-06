#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

//예제1
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
//	//구간[v.begin(),v.end())에서 현재 원소와 다음 원소가 같아지는 첫번째 반복자를 반환
//	iter = adjacent_find(v.begin(), v.end());
//
//	if (iter != v.end())
//		cout << *iter << endl;
//
//	for (; iter != v.end(); ++iter)
//		cout << *iter << " ";
//	cout << endl;
//}


//예제 2 adjacent_find
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
//	//동일한게 있는지 찾고 출력하는 반복자
//	iter = adjacent_find(iter_b, iter_e);
//
//	if (iter != iter_e)// 위에서 시작부터 2칸인 30까지를 확인하는데 위에 iter도 끝까지 탐색하여 30이고 iter_e도 30까지니 맞는표현
//		cout << *iter << endl;
//
//	cout << "==============" << endl;
//	//이건 iter은 iter_e까지 탐색을 하여 30이라는 숫자가 나왔지만 끝까지 탐색을 하여 숫자가 출력이 되었다.
//	if (iter != v.end())
//		cout << *iter << endl;
//
//	iter_b = v.begin();
//	iter_e = v.end();
//	iter = adjacent_find(iter_b, iter_e);
//
//	//둘다 출력 되지 않는다.
//	if (iter != iter_e)
//		cout << *iter << endl;
//	if (iter != v.end())
//		cout << *iter << endl;
//}

//예제3 adjaoent_find 조건

//bool Pred(int a, int b)
//{
//	return abs(b - a) > 10; //abs는 절대값
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

//예제 4(count 문제)
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
//		cout << v[i] << " ";//다 출력
//	cout << endl;
//
//	int n = count(v.begin(), v.end(), 30);//30이 시작부터 끝까지 몇개 있는가
//	cout << "30의 개수:" << n << endl;
//}

//예제5 (count_if 예제문제)
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
//	cout << "25보다 큰 원소의 개수:" << n << endl;
//}

//예제6 equal()는 v1의 시작과 끝을 알고 v2의 첫번째를 입력하면  v1의 크기 만큼 숫자 가 같은지 비교

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
//		cout << "두 순차열은 같습니다" << endl;
//	else
//		cout << "두 순차열은 같지 않습니다" << endl;
//}


//예제 7  equal()조건을 달면 범위안에 첫번쨰는 첫번쨰 끼리 비교하고 맞으면 참으로 반환한다
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
//	//구간 [v1.being(), v1.end)와 구간 [v2.begin(), v2.begin()+3)을
//	//비교 합니다.
//	if (equal(v1.begin(), v1.end(), v2.begin(), Pred))
//		cout << "두 순차열은 같습니다." << endl;
//}

//예제 8  find(),find_if()문

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
//	iter = find(v.begin(), v.end(), 20); //20을 찾는것
//
//	if (iter != v.end())
//		cout << *iter << "을 찾다!" << endl;
//
//	iter = find_if(v.begin(), v.end(), Pred); // 35보다 큰수중에 첫번째원소 찾기
//	if (iter != v.end())
//		cout << "순차열에서 35보다 큰 첫번째 원소: " << *iter << endl;
//}

//예제9 find_end() v2가 v1에서 일치 하는것중에 마지막 순차열의 첫원소 반복자이다.
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


//예제 10 find_end()는 뒤에서 한원소에 한개씩 비교하고 없으면 한칸 올라가서 다시 비교한다
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
//		// 일치하는 마지막 순차열의 첫 원소의 반복자 iter
//		cout << "iter : " << *iter << endl;
//		cout << "iter-1 : " << *(iter - 1) << endl;
//		cout << "iter+1 : " << *(iter + 1) << endl;;
//	}
//}

//예제11 find_first_of()는 v1의 원소 하나에 v2에 모든 원소 확인
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

//예제 12 find_first_of() 예제
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

//예제 13 for_each() ~에서  ~기까지 

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

//예제 14 for_each 응용

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
//	for_each(v.begin(), v.end(), PrintFunctor()); // 원소의 구분을 ' '로
//	cout << endl;
//	for_each(v.begin(), v.end(), PrintFunctor(','));// 원소의 구분을 ','로
//	cout << endl;
//	for_each(v.begin(), v.end(), PrintFunctor('\n'));// 원소의 구분을 '\n'로
//	cout << endl;
//}

//예제 15  lexlcographlcal_compare() 우선 비교

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

//예제 16
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
//		cout << "기준 less v1과 v2의 비교: true" << endl;
//	else
//		cout << "기준 less v1과 v2의 비교: false" << endl;
//	if (lexicographical_compare(v1.begin(), v1.end(), v2.begin(), v2.end(), greater<int>()))
//		cout << "기준 greater v1과 v2의 비교: true" << endl;
//	else
//		cout << "기준 greater v1과 v2의 비교: false" << endl;
//	if (lexicographical_compare(v1.begin(), v1.end(), v2.begin(), v2.end(), Less<int>()))
//		cout << "사용자 기준 Less v1과 v2의 비교: true" << endl;
//	else
//		cout << "사용자 기준 Less v1과 v2의 비교: false" << endl;
//}

//예제 17 max(),min()
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


//예제 18 max_element(), min_element() 알고리즘 사용 예제
//벡터안에 값들을 비교를 하여 큰지 작은지 비교
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

//예제 19 비교하는곳에 true이면 높은게 왼쪽으로 오고 처음부터 비교를 한다
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
//	cout << "max: "; iter->Print(); //반복자가 가리키는 객체의 멤버는 -> 연산자로 접근
//	cout << "max: "; (*iter).Print(); //위와 같음
//}


//예제 20  여기서 Pred에서 값이 다르면 빠져 나간다 mismatch(불일치)하면 값을 빠져 나온다.
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


//예제 21  search()는 find_end() 와는 반대이다.find_end()뒤에서 확인search는 앞에서 확인

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
//		// 일치하는 첫 번째 순차열의 첫 원소의 반복자 iter
//		cout << "iter : " << *iter << endl;
//		cout << "iter-1 : " << *(iter - 1) << endl;
//		cout << "iter+1 : " << *(iter + 1) << endl;
//	}
//}//예제 22bool Pred(int left, int right){	return abs(right - left) <= 5;}void main(){	vector<int>v;	v.push_back(10);	v.push_back(20);	v.push_back(30);	v.push_back(30);	v.push_back(30);	v.push_back(40);	v.push_back(50);	vector<int>::iterator iter;	iter = search_n(v.begin(), v.end(), 3, 30,Pred);	if (iter != v.end())	{		cout << "iter: " << *iter << endl;		cout << "iter-1:" << *(iter - 1) << endl;		cout << "iter+1:" << *(iter + 1) << endl;	}}