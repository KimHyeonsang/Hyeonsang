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
void main()
{
	vector<int> v1;
	v1.push_back(10);
	v1.push_back(20);
	v1.push_back(30);
	v1.push_back(40);
	v1.push_back(50);
	v1.push_back(60);
	v1.push_back(70);
	v1.push_back(30);
	v1.push_back(40);
	v1.push_back(50);

	vector<int> v2;
	v2.push_back(30);
	v2.push_back(40);
	v2.push_back(70);

	vector<int>::iterator iter;

	iter = find_end(v1.begin(), v1.end(), v2.begin(), v2.end());

	if (iter != v1.end())
	{
		cout << "iter :" << *iter << endl;
		cout << "iter-1 :" << *(iter - 1) << endl;
		cout << "iter+1 :" << *(iter + 1) << endl;
	}
}


//예제 10
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