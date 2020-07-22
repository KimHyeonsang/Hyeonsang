#include<iostream>
#include<List>
#include<vector>
using namespace std;

//void main()
//{
//	list<int> lt;
//	list<int> lt2;
//	lt.push_back(10);
//	lt.push_back(20);
//	lt.push_back(30);
//	lt.push_back(70);
//	lt.push_back(60);
//	lt.push_back(50);
//
//
//	lt2.push_back(80);
//	lt2.push_back(90);
//	lt2.push_back(70);
//
//	
//	list<int>::iterator iter;
//	for (iter = lt.begin(); iter != lt.end(); ++iter)
//	{
//		cout << *iter<<" ";
//	}
//	cout << endl;
//
//	for (iter = lt2.begin(); iter != lt2.end(); ++iter)
//	{
//		cout << *iter << " ";
//	}
//	cout << endl;
//
////	lt.merge(lt2);
//
//	lt.reverse();
//	cout << "lt : ";
//	for (iter = lt.begin(); iter != lt.end(); ++iter)
//	{
//		cout << *iter << " ";
//	}
//	cout << endl;
//
//	cout << "기본적인 오름차순 : ";
//	lt.sort();
//	for (iter = lt.begin(); iter != lt.end(); ++iter)
//	{
//		cout << *iter << " ";
//	}
//	cout << endl;
//
//	cout << "내림차순 : ";
//	lt.sort(greater<int>());
//	for (iter = lt.begin(); iter != lt.end(); ++iter)
//	{
//		cout << *iter << " ";
//	}
//	cout << endl;
//
//	cout << "lt에 lt2를 잘라 붙이기 : ";
//	lt.splice(iter, lt2);
//	for (iter = lt.begin(); iter != lt.end(); ++iter)
//	{
//		cout << *iter << " ";
//	}
//
//	lt.splice(iter, lt2, 90);
//	lt.splice(iter, lt2, lt.begin(), lt.begin() + 2);
//
//	list<int> lt;
//	lt.push_back(10);
//	lt.push_back(20);
//	lt.push_back(30);
//	lt.push_back(40);
//	lt.push_back(50);
//	list<int>::iterator iter = lt.begin();
//	list<int>::iterator iter2;
//	++iter;
//	++iter;
//	iter2 = lt.erase(iter); //iter(30)의 원소를 제거합니다.
//	for (iter = lt.begin(); iter != lt.end(); ++iter)
//		cout << *iter << ' ';
//	cout << endl;
//	cout << "iter2 : " << *iter2 << endl;
//	iter = iter2;
//	iter2 = lt.insert(iter, 300); //iter2(40)이 가리키는 위치에 300을 삽입합니다.
//	for (iter = lt.begin(); iter != lt.end(); ++iter)
//		cout << *iter << ' ';
//	cout << endl;
//	cout << "iter2 : " << *iter2 << endl;//
//}

//void main()//List 와vector의 삽입동작차이
//{
//	vector<int> v;
//	list<int> It;
//
//	v.push_back(10);  //vector 에 10,20,30,40,50 순으로 저장을한다.
//	v.push_back(20);
//	v.push_back(30);
//	v.push_back(40);
//	v.push_back(50);
//
//	It.push_back(10); // list에 뒤로 10 20 30 40 50을 저장한다.
//	It.push_back(20);
//	It.push_back(30);
//	It.push_back(40);
//	It.push_back(50);
//
//	vector<int>::iterator viter = v.begin(); //vector의 반복자를 벡터의 첫번째 값을 가르킴
//	++viter; //하나 더하여서 20의 원소를 가르킴
//	list<int>::iterator liter = It.begin(); //list의 반복자를 리스트의 첫번쨰 값을 가르킴
//	++liter;//더하여 20의 원소를 가르킴
//
//	viter = v.insert(viter, 600); //20에 가르키는곳에 600을 삽입
//	liter = It.insert(liter, 600);// 20을 가르키는곳에 600을 삽입
//
//	cout << "vectoer: " << *viter << endl; //600
//	cout << "list: " << *liter << endl; //600
//
//	cout << "vector :"; //벡터는 배열로서 저장이 되어있는것에 새로운것을 추가하면
//						//다시 크기를 할당하고 삽입을 한다.
//	for (viter = v.begin(); viter != v.end(); ++viter)
//		cout << *viter << " ";//10,600,20,30,40,50
//	cout << endl;
//	cout << "List :";//리스트는 값을 넣는게 유동적이며 앞에서 넣을수도 제거 할수도 뒤에 넣을수도 앞에 넣을수도 있어 많이 유용하다.
//	for (liter = It.begin(); liter != It.end(); ++liter)
//		cout << *liter << " ";//10,600,20,30,40,50
//	cout << endl;
//}


//void main()//remove()예제
//{
//	list<int> it;
//	it.push_back(10);
//	it.push_back(20);
//	it.push_back(30);
//	it.push_back(10);
//	it.push_back(40);
//	it.push_back(50);
//	it.push_back(10);
//	it.push_back(10);
//
//	list<int>::iterator iter;
//	for (iter = it.begin(); iter != it.end(); ++iter)
//		cout << *iter << " "; //10,20,30,10,40,50,10,10
//	cout << endl;
//
//	it.remove(10);//10의 값을 지움
//	for (iter = it.begin(); iter != it.end(); ++iter)
//		cout << *iter << " "; //20,30,40,50으로 출력
//	cout << endl;
//}

//bool Predicate(int n)
//{
//	return 10 <= n && n <= 30;
//}
//
//void main()//remove_if() 사용예제
//{
//	list<int>it;
//	it.push_back(10);
//	it.push_back(20);
//	it.push_back(30);
//	it.push_back(40);
//	it.push_back(50);
//	it.push_back(10);
//
//	list<int>::iterator iter;
//	for (iter = it.begin(); iter != it.end(); ++iter)
//		cout << *iter << " ";  //10,20,30,40,50,10으로 출력
//	cout << endl;
//
//	it.remove_if(Predicate); //bool형에서 10이상 30이하인 수는 참으로 반환하여 제거
//	for (iter = it.begin(); iter != it.end(); ++iter)
//		cout << *iter << " "; //40,50
//	cout << endl;
//}

//void main()//splice() 사용예제  splice 자르기
//{
//	list<int>it1;
//	list<int>it2;
//
//	it1.push_back(10);
//	it1.push_back(20);
//	it1.push_back(30);
//	it1.push_back(40);
//	it1.push_back(50);
//
//	it2.push_back(100);
//	it2.push_back(200);
//	it2.push_back(300);
//	it2.push_back(400);
//	it2.push_back(500);
//
//	list<int>::iterator iter;
//	cout << "it1 :";
//	for (iter = it1.begin(); iter != it1.end(); ++iter)
//		cout << *iter << " "; //10,20,30,40,50 출력
//	cout << endl;
//
//	cout << "it2 :";
//	for (iter = it2.begin(); iter != it2.end(); ++iter)
//		cout << *iter << " "; //100,200,300,400,500출력
//	cout << endl << "===============" << endl;
//
//	iter = it1.begin(); //10의 값을 가르킴
//	++iter; //20
//	++iter;//30
//
//	it1.splice(iter, it2);//세번째 자리에 it2의 값을 넣음
//
//	cout << "it1 :";
//	for (iter = it1.begin(); iter != it1.end(); ++iter)
//		cout << *iter << " "; //10,20,100,200,300,400,500,30,40,50
//	cout << endl;
//
//	cout << "it2 :";
//	for (iter = it2.begin(); iter != it2.end(); ++iter)
//		cout << *iter << " ";//...
//	cout << endl;
//}

//void main() //splice 활용
//{
//	list<int> lt1;
//	list<int> lt2;
//	lt1.push_back(10);
//	lt1.push_back(20);
//	lt1.push_back(30);
//	lt1.push_back(40);
//	lt1.push_back(50);
//
//	lt2.push_back(100);
//	lt2.push_back(200);
//	lt2.push_back(300);
//	lt2.push_back(400);
//	lt2.push_back(500);
//
//	list<int>::iterator iter1; 
//	list<int>::iterator iter2;
//
//	cout << "lt1: ";
//	for (iter1 = lt1.begin(); iter1 != lt1.end(); ++iter1)
//		cout << *iter1 << ' ';
//	cout << endl;
//	cout << "lt2: ";
//	for (iter2 = lt2.begin(); iter2 != lt2.end(); ++iter2)
//		cout << *iter2 << ' ';
//	cout << endl << "=============" << endl;
//	iter1 = lt1.begin();
//	++iter1;
//	++iter1; // 30 원소의 위치를 가리킴
//
//	iter2 = lt2.begin();
//	++iter2; // 200 원소의 위치를 가리킴
//	//iter1이 가리키는 위치에 iter2가 가리키는 위치의 lt2의 원소를 잘라 붙임
//	lt1.splice(iter1, lt2, iter2); // 
//	cout << "lt1: ";
//	for (iter1 = lt1.begin(); iter1 != lt1.end(); ++iter1)
//		cout << *iter1 << ' '; //10 20 200 30 40 50
//	cout << endl;
//	cout << "lt2: ";
//	for (iter2 = lt2.begin(); iter2 != lt2.end(); ++iter2)
//		cout << *iter2 << ' ';  //100 300 400 500
//	cout << endl << "=============" << endl;
//	//lt1.end()가 가리키는 위치에 순차열 [lt2.begin(), lt2.end())를 잘라 붙임
//
//
//	lt1.splice(lt1.end(), lt2, lt2.begin(), lt2.end());
//	cout << "lt1: ";
//	for (iter1 = lt1.begin(); iter1 != lt1.end(); ++iter1)
//		cout << *iter1 << ' ';//10 20 200 30 40 50 100 300 400 500
//	cout << endl;
//	cout << "lt2: ";
//	for (iter2 = lt2.begin(); iter2 != lt2.end(); ++iter2)
//		cout << *iter2 << ' ';  //x
//	cout << endl;
//}

//void main()//reverse() 활용
//{
//	list<int>it;
//
//	it.push_back(10);
//	it.push_back(20);
//	it.push_back(30);
//	it.push_back(40);
//	it.push_back(50);
//
//	list<int>::iterator iter;
//	for (iter = it.begin(); iter != it.end(); ++iter)
//		cout << *iter << " ";   //10,20,30,40,50
//	cout << endl;
//
//	it.reverse();//반전
//	for (iter = it.begin(); iter != it.end(); ++iter)
//		cout << *iter << " ";  //50,40,30,20,10
//	cout << endl;
//}

//void main() //unlque()
//{
//	list<int> lt;
//	lt.push_back(10);
//	lt.push_back(10);
//	lt.push_back(20);
//	lt.push_back(30);
//	lt.push_back(30);
//	lt.push_back(30);
//	lt.push_back(40);
//	lt.push_back(50);
//	lt.push_back(10);//
//	list<int>::iterator iter;
//	for (iter = lt.begin(); iter != lt.end(); ++iter)
//		cout << *iter << ' ';
//	cout << endl;
//
//	lt.unique(); //양옆에 같은 값이 있으면 삭제
//
//	for (iter = lt.begin(); iter != lt.end(); ++iter)
//		cout << *iter << " ";  //10,20,30,40,50,10
//	cout << endl;
//}

//void main() //sort()
//{
//	list<int>lt;
//
//	lt.push_back(20);
//	lt.push_back(10);
//	lt.push_back(50);
//	lt.push_back(30);
//	lt.push_back(40);
//
//	list<int>::iterator iter;
//	for (iter = lt.begin(); iter != lt.end(); ++iter)
//		cout << *iter << " ";
//	cout << endl;
//
//	lt.sort();//자동으로 오름차순
//	for (iter = lt.begin(); iter != lt.end(); ++iter)
//		cout << *iter << " ";
//	cout << endl;
//}

//struct Greater
//{
//	bool operator()(int left, int right)const
//	{
//		return left > right;
//	}
//};
//
//void main() //sort() 예제
//{
//	list<int>lt;
//
//	lt.push_back(20);
//	lt.push_back(10);
//	lt.push_back(50);
//	lt.push_back(30);
//	lt.push_back(40);
//
//	list<int>::iterator iter;
//	for (iter = lt.begin(); iter != lt.end(); ++iter)
//		cout << *iter << " ";
//	cout << endl;
//
//	lt.sort(greater<int>()); //내림차순
//	for (iter = lt.begin(); iter != lt.end(); ++iter)
//		cout << *iter << " ";
//	cout << endl;
//
//	lt.sort(less<int>());//오름차순
//	for (iter = lt.begin(); iter != lt.end(); ++iter)
//		cout << *iter << " ";
//	cout << endl;
//
//	lt.sort(Greater());
//	for (iter = lt.begin(); iter != lt.end(); ++iter)
//		cout << *iter << " ";
//	cout << endl;
//}

//
//void main()
//{
//	list<int> lt1;
//	list<int> lt2;
//	lt1.push_back(10);
//	lt1.push_back(20);
//	lt1.push_back(30);
//	lt1.push_back(40);
//	lt1.push_back(50);
//
//	lt2.push_back(15);
//	lt2.push_back(35);
//	lt2.push_back(55);
//
//	list<int>::iterator iter;
//	cout << "lt1: ";
//	for (iter = lt1.begin(); iter != lt1.end(); ++iter)
//		cout << *iter << ' ';
//	cout << endl;
//
//	cout << "lt2: ";
//	for (iter = lt2.begin(); iter != lt2.end(); ++iter)
//		cout << *iter << ' ';
//	cout << endl << "===============" << endl;
//
//	lt1.merge(lt2); // lt2를 lt1으로 합병 정렬합니다. 정렬 기준은 less
//	cout << "lt1: ";
//	for (iter = lt1.begin(); iter != lt1.end(); ++iter)
//		cout << *iter << ' ';
//	cout << endl;
//
//	cout << "lt2: ";
//	for (iter = lt2.begin(); iter != lt2.end(); ++iter)
//		cout << *iter << ' ';
//	cout << endl;
//}


void main() //merge 예제
{
	list<int>lt1;
	list<int>lt2;

	lt1.push_back(50);
	lt1.push_back(40);
	lt1.push_back(30);
	lt1.push_back(20);
	lt1.push_back(10);

	lt2.push_back(60);
	lt2.push_back(35);
	lt2.push_back(25);

	list<int>::iterator iter;
	cout << "lt1 :";
	for (iter = lt1.begin(); iter != lt1.end(); ++iter)
		cout << *iter << " ";
	cout << endl;

	cout << "lt2 :";
	for (iter = lt2.begin(); iter != lt2.end(); ++iter)
		cout << *iter << " ";
	cout << endl << "==============" << endl;

	lt1.merge(lt2, greater<int>());

	cout << "lt1 : ";
	for (iter = lt1.begin(); iter != lt1.end(); ++iter)
		cout << *iter << " ";
	cout << endl;

	cout << "lt2 : ";
	for (iter = lt2.begin(); iter != lt2.end(); ++iter)
		cout << *iter << " ";
	cout << endl;
}