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
//	cout << "�⺻���� �������� : ";
//	lt.sort();
//	for (iter = lt.begin(); iter != lt.end(); ++iter)
//	{
//		cout << *iter << " ";
//	}
//	cout << endl;
//
//	cout << "�������� : ";
//	lt.sort(greater<int>());
//	for (iter = lt.begin(); iter != lt.end(); ++iter)
//	{
//		cout << *iter << " ";
//	}
//	cout << endl;
//
//	cout << "lt�� lt2�� �߶� ���̱� : ";
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
//	iter2 = lt.erase(iter); //iter(30)�� ���Ҹ� �����մϴ�.
//	for (iter = lt.begin(); iter != lt.end(); ++iter)
//		cout << *iter << ' ';
//	cout << endl;
//	cout << "iter2 : " << *iter2 << endl;
//	iter = iter2;
//	iter2 = lt.insert(iter, 300); //iter2(40)�� ����Ű�� ��ġ�� 300�� �����մϴ�.
//	for (iter = lt.begin(); iter != lt.end(); ++iter)
//		cout << *iter << ' ';
//	cout << endl;
//	cout << "iter2 : " << *iter2 << endl;//
//}

//void main()//List ��vector�� ���Ե�������
//{
//	vector<int> v;
//	list<int> It;
//
//	v.push_back(10);  //vector �� 10,20,30,40,50 ������ �������Ѵ�.
//	v.push_back(20);
//	v.push_back(30);
//	v.push_back(40);
//	v.push_back(50);
//
//	It.push_back(10); // list�� �ڷ� 10 20 30 40 50�� �����Ѵ�.
//	It.push_back(20);
//	It.push_back(30);
//	It.push_back(40);
//	It.push_back(50);
//
//	vector<int>::iterator viter = v.begin(); //vector�� �ݺ��ڸ� ������ ù��° ���� ����Ŵ
//	++viter; //�ϳ� ���Ͽ��� 20�� ���Ҹ� ����Ŵ
//	list<int>::iterator liter = It.begin(); //list�� �ݺ��ڸ� ����Ʈ�� ù���� ���� ����Ŵ
//	++liter;//���Ͽ� 20�� ���Ҹ� ����Ŵ
//
//	viter = v.insert(viter, 600); //20�� ����Ű�°��� 600�� ����
//	liter = It.insert(liter, 600);// 20�� ����Ű�°��� 600�� ����
//
//	cout << "vectoer: " << *viter << endl; //600
//	cout << "list: " << *liter << endl; //600
//
//	cout << "vector :"; //���ʹ� �迭�μ� ������ �Ǿ��ִ°Ϳ� ���ο���� �߰��ϸ�
//						//�ٽ� ũ�⸦ �Ҵ��ϰ� ������ �Ѵ�.
//	for (viter = v.begin(); viter != v.end(); ++viter)
//		cout << *viter << " ";//10,600,20,30,40,50
//	cout << endl;
//	cout << "List :";//����Ʈ�� ���� �ִ°� �������̸� �տ��� �������� ���� �Ҽ��� �ڿ� �������� �տ� �������� �־� ���� �����ϴ�.
//	for (liter = It.begin(); liter != It.end(); ++liter)
//		cout << *liter << " ";//10,600,20,30,40,50
//	cout << endl;
//}


//void main()//remove()����
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
//	it.remove(10);//10�� ���� ����
//	for (iter = it.begin(); iter != it.end(); ++iter)
//		cout << *iter << " "; //20,30,40,50���� ���
//	cout << endl;
//}

//bool Predicate(int n)
//{
//	return 10 <= n && n <= 30;
//}
//
//void main()//remove_if() ��뿹��
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
//		cout << *iter << " ";  //10,20,30,40,50,10���� ���
//	cout << endl;
//
//	it.remove_if(Predicate); //bool������ 10�̻� 30������ ���� ������ ��ȯ�Ͽ� ����
//	for (iter = it.begin(); iter != it.end(); ++iter)
//		cout << *iter << " "; //40,50
//	cout << endl;
//}

//void main()//splice() ��뿹��  splice �ڸ���
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
//		cout << *iter << " "; //10,20,30,40,50 ���
//	cout << endl;
//
//	cout << "it2 :";
//	for (iter = it2.begin(); iter != it2.end(); ++iter)
//		cout << *iter << " "; //100,200,300,400,500���
//	cout << endl << "===============" << endl;
//
//	iter = it1.begin(); //10�� ���� ����Ŵ
//	++iter; //20
//	++iter;//30
//
//	it1.splice(iter, it2);//����° �ڸ��� it2�� ���� ����
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

//void main() //splice Ȱ��
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
//	++iter1; // 30 ������ ��ġ�� ����Ŵ
//
//	iter2 = lt2.begin();
//	++iter2; // 200 ������ ��ġ�� ����Ŵ
//	//iter1�� ����Ű�� ��ġ�� iter2�� ����Ű�� ��ġ�� lt2�� ���Ҹ� �߶� ����
//	lt1.splice(iter1, lt2, iter2); // 
//	cout << "lt1: ";
//	for (iter1 = lt1.begin(); iter1 != lt1.end(); ++iter1)
//		cout << *iter1 << ' '; //10 20 200 30 40 50
//	cout << endl;
//	cout << "lt2: ";
//	for (iter2 = lt2.begin(); iter2 != lt2.end(); ++iter2)
//		cout << *iter2 << ' ';  //100 300 400 500
//	cout << endl << "=============" << endl;
//	//lt1.end()�� ����Ű�� ��ġ�� ������ [lt2.begin(), lt2.end())�� �߶� ����
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

//void main()//reverse() Ȱ��
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
//	it.reverse();//����
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
//	lt.unique(); //�翷�� ���� ���� ������ ����
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
//	lt.sort();//�ڵ����� ��������
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
//void main() //sort() ����
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
//	lt.sort(greater<int>()); //��������
//	for (iter = lt.begin(); iter != lt.end(); ++iter)
//		cout << *iter << " ";
//	cout << endl;
//
//	lt.sort(less<int>());//��������
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
//	lt1.merge(lt2); // lt2�� lt1���� �պ� �����մϴ�. ���� ������ less
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


void main() //merge ����
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