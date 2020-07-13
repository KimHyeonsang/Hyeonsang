#include<iostream>
#include<string>
using namespace std;

//template <typename T>
//void Print(T a, T b)
//{
//	cout << a << "," << b << endl;
//}
//
//void main()
//{
//	Print(10, 20);
//	Print(0.123, 1.123);
//	Print("ABC", "abcde");
//
//	Print<int>(10, 20);
//	Print<double>(0.123, 1.123);
//	Print<const char*>("ABC", "abcde");
//}

//template<typename T1,typename T2>
//void Print(T1 a, T2 b)
//{
//	cout << a << "," << b << endl;
//}
//
//void main()
//{
//	Print(10, 1.5);//정수,실수 입력
//	Print("Hello!", 100);//문자열,정수 출력
//	Print(1.5, "Hello!");//실수,문자열 출력
//}

//template<typename T>
//void Swap(T &a, T &b)
//{
//	T temp = a;
//	a = b;
//	b = temp;
//}
//
//void main()
//{
//	int n1 = 10, n2 = 20;
//	double d1 = 1.1, d2 = 2.2;
//
//	cout << n1 << "," << n2 << endl;
//	Swap(n1, n2);
//	cout << n1 << "," << n2 << endl;
//	cout << endl;
//
//	cout << d1 << "," << d2 << endl;
//	Swap(d1, d2);
//	cout << d1 << "," << d2 << endl;
//}

//template<typename T,int size>//배열을 템플릿으로 사용가능
//void PrintArray(T* arr)
//{
//	for (int i = 0; i < size; ++i)
//	{
//		cout << "[" << i << "]" << arr[i] << endl;
//	}
//	cout << endl;
//}
//
//void main()
//{
//	int arr1[5] = { 10,20,30,40,50 };
//	PrintArray<int, 5>(arr1);//명시적 호출
//
//	//PrintArray(arr1);//임시로는 불가능 하다
//
//	double arr2[3] = { 1.1,2.2,3.3 };
//	PrintArray<double, 3>(arr2);
//}

//class Point
//{
//	int x; int y;
//public:
//	explicit Point(int _x = 0, int _y = 0) :x(_x), y(_y) {}
//	void Print()const { cout << x<<',' <<  y << endl; }
//};
//
//template<typename T>
//void Print(T a)
//{
//	cout << a << endl;
//}
//
//void main()
//{
//	int n = 10;
//	double d = 2.5;
//	Point pt(2, 3);
//
//	Print(n);
//	Print(d);
//	Print(pt);//cout<<pt;연산 불가능
//}

//class Point
//{
//	int x; int y;
//public:
//	explicit Point(int _x=0,int _y = 0):x(_x),y(_y){}
//	void Print()const { cout << x << ',' << y << endl; }
//};
//
//template<typename T>
//void Print(T a)
//{
//	cout << a << endl;
//}
//
//template<>
//void Print(Point a)
//{
//	cout << "Print 특수화 버전:";
//	a.Print();
//}
//
//void main()
//{
//	int n = 0;
//	double d = 2.5;
//	Point pt(2, 3);
//
//	Print(n);
//	Print<int>(n);
//	Print(d);
//	Print<double>(d);
//	Print(pt);
//	Print<Point>(pt);
//}

//class intArray
//{
//	int *buf;
//	int size;
//	int capacity;
//public:
//	explicit intArray(int cap = 100) :buf(0), size(0), capacity(cap)
//	{
//		buf = new int[capacity];
//	}
//	~intArray() { delete[] buf; }
//
//	void Add(int data) { buf[size++] = data; }
//	int operator[](int idx)const { return buf[idx]; }
//	int GetSize()const { return size; }
//
//};
//
//class StringArray
//{
//	string *buf;
//	int size;
//	int capacity;
//public:
//	explicit StringArray(int cap = 100) :buf(0), size(0), capacity(cap)
//	{
//		buf = new string[capacity];
//	}
//	~StringArray() { delete[] buf; }
//
//	void Add(string data) { buf[size++] = data; }
//	string operator[](int idx)const { return buf[idx]; }
//	int GetSize()const { return size; }
//};
//
//void main()
//{
//	intArray iarr;
//	iarr.Add(10);
//	iarr.Add(20);
//	iarr.Add(30);
//
//	for (int i = 0; i < iarr.GetSize(); ++i)
//		cout << iarr[i] << " ";
//
//	cout << endl;
//
//	StringArray sarr;
//	sarr.Add("abc");
//	sarr.Add("ABC");
//	sarr.Add("Hello!");
//
//	for (int i = 0; i < sarr.GetSize(); ++i)
//		cout << sarr[i] << " ";
//
//	cout << endl;
//}

//template<typename T = int,int capT = 100>
//class Array
//{
//	T * buf;
//	int size;
//	int capacity;
//public:
//	explicit Array(int cap = capT) :buf(0), size(0), capacity(cap)
//	{
//		buf = new T[capacity];
//	}
//	~Array() { delete[] buf; }
//
//	void Add(T data)
//	{
//		buf[size++] = data;
//	}
//
//	T operator[](int idx)const
//	{
//		return buf[idx];
//	}
//	int GetSize()const
//	{
//		return size;
//	}
//};
//
//void main()
//{
//	Array<>iarr;
//	iarr.Add(10);
//	iarr.Add(20);
//	iarr.Add(30);
//
//	for (int i = 0; i < iarr.GetSize(); ++i)
//		cout << iarr[i] << " ";
//
//	cout << endl;
//
//	Array<string,10>sarr;
//	sarr.Add("abc");
//	sarr.Add("ABC");
//	sarr.Add("Hello!");
//
//	for (int i = 0; i < sarr.GetSize(); ++i)
//		cout << sarr[i] << " ";
//
//	cout << endl;
//}

//template<typename IterT,typename Func>
//void For_each(IterT begin, IterT end, Func pf)
//{
//	while (begin != end)
//	{
//		pf(*begin++);
//	}
//}
//template<typename T>
//void Print(T data)
//{
//	cout << data << " ";
//}
//
//void main()
//{
//	int arr[5] = { 10,20,30,40,50 };
//	For_each(arr, arr + 5, Print<int>);//명시적으로 해줘야한다.
//	cout << endl;
//	For_each<int*, void(*)(int)>(arr, arr + 5, Print<int>);
//	cout << endl;
//
//	string sarr[3] = { "abc","ABCDE","Hello!" };
//	For_each(sarr, sarr + 3, Print<string>);
//	cout << endl;
//	For_each<string*, void(*)(string)>(sarr, sarr + 3, Print<string>);
//	cout << endl;
//}

//template <typename IterT, typename Func>
//void For_each(IterT begin, IterT end, Func pf)
//{
//	while (begin != end)
//	{
//		pf(*begin++);
//	}
//}
//template <typename T>
//class PrintFunctor
//{
//	string sep; // 출력 구분자 정보
//public:
//	explicit PrintFunctor(const string& s = " ") : sep(s) { }
//	void operator()(T data) const
//	{
//		cout << data << sep;
//	}
//};//void main()
//{
//	int arr[5] = { 10, 20, 30, 40, 50 };
//	For_each(arr, arr + 5, PrintFunctor<int>());
//	cout << endl;
//	string sarr[3] = { "abc","ABCDE","Hello!" };
//	For_each(sarr, sarr + 3, PrintFunctor<string>("*\n"));
//	cout << endl;
//}

template <typename RetType, typename ArgType>
class Functor
{
public:
	RetType operator( ) (ArgType data)
	{
		cout << data << endl;
		return RetType();
	}
};
void main()
{
	Functor< void, int > functor1;
	functor1(10);
	Functor< bool, string > functor2;
	functor2("Hello!");
}