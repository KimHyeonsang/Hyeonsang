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


//���� 10
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