//c++�﷨����
//
// 1.bool
//�߼�����true�������0��false������0��������ߴ���ɶ���

#include<iostream>
#include<cstring>//�൱��c���Ե�string.h
#include<cmath>//��ѧ,���Ǻ�����ָ������������
#include<cstdlib>
using namespace std;
//int main()
//{
//	bool yes = true;//��߿ɶ���
//	if (yes)
//	{
//		cout << "yes" << endl;
//	}
//	else
//	{
//		cout << "no" << endl;
//	}
//	return 0;
//}


//c++��׼��
//vector���飬
#include<vector>
//int main()
//{
//
//	//c����ʵ������
//	int arr2[100];
//	//c++
//	vector<int>arr1(100);//�������飬
//	//vector�����Կ���һ������,��̬�ı䳤
//	vector<int >arr3(10);
//
//	vector<int>list;//����,vector��������Ū��С
//	list.push_back(1);
//	list.push_back(2);
//	list.push_back(3);
//
//	//vector�ı������뷽ʽ
//	int a;
//	vector<int> arr;
//	int n;
//	cin >> n;
//	//arr.size()���������ж��ٵ�����
//	for (int i = 0; i < n; i++)
//	{
//		cin >> a;
//		arr.push_back(a);
//		//cout << arr[i] << endl;
//	}
//	//��������
//	for (int i = 0; i < arr.size(); i++)
//	{
//		cout << arr[i] << endl;
//	}
//
//	
//
//	return 0;
//}


//int main()
//{
//	//������,iterator�൱��c���Ե�ָ�룬
//	vector<int>arr1(100);
//	arr1[0] = 100;
//	vector<int>::iterator p1 = arr1.begin();//p�����׵�ַ��
//	cout << *p1 << endl;
//
//	//ָ�����������ʹ�öԱ�
//	vector<int>arr(100);
//	int arr2[100];
//	vector<int>::iterator p;
//	int* p2 = nullptr;
//	//for (p = arr.begin(); p != arr.end(); p++)//������Ҳ��������,���׵�ַ��ĩ��ַָ��
//	//{
//	//	cout << *p << endl;
//	//}
//	//int i = 0;
//	//for (p2 = arr2,i = 0; i < 100;p2++, i++)
//	//{
//	//	cout << *p2 << endl;
//	//}
//	//
//
//	//vector�ĳ�������
//	vector<int> list;
//
//	//���Լ��������Ԫ�ظ���
//	//�������飬
//	list.push_back(2);
//	list.push_back(4);
//	cout<< list.size()<<endl;
//	list.clear();
//	list.empty();//�����ж��Ƿ�Ϊ�գ��൱��size�Ƿ�Ϊ0��
////		list.begin();//
////	list.erase(p)//ɾ��������pλ�õ�����
////		list.pop_back();//βɾ
//
//	return 0;
//}


//string
#include<string>
//int main()
//{
//	string str1 = "hello";
//	str1 += "world";
//	cout << str1 << endl;
//	cout << str1.size() << endl;//str1.length()����
//	str1.insert(1, "aaa");//��1��λ�ò���aaa
//	string str2 = "cpp";
//	str1.append(str2);// �൱��c���Ե�strcat
//	str1.compare(str2);//�൱��c���Ե�strcmp(str1,str2);
//	str1.push_back('a');
//	str1 += 'bvc';
//	str1 == str2;//�ж��Ƿ���ͬ
//	cout << str1 << endl;
//	return 0;
//}

#include<algorithm>
bool cmp(int a,int b)
{
	return a > b;//���ڵ���ǰ��
}
int main()
{
	int arr[] = { 2,3,1,5,4 };
	sort(arr, arr + 5);//��һ�������������ͷָ�룬�ڶ������������һ��Ԫ�ص���һ���ĵ�ַ���ڲ�ʹ�õĿ�������
	vector<int>arr1{ 2,3,1,5,4 };//vector�ĳ�ʼ��
	sort(arr1.begin(), arr1.end(),cmp);
//	nth_element(arr1.begin(), arr1.beign() + 2, arr1.end());
	swap(arr1[1],arr1[2]);//����������
	reverse(arr1.begin(), arr1.end());//��ת

	//unique����ȥ��
	vector<int>uni{ 1,1,2,2,3,4 };
//	int newlength = unique(uni.begin(), uni.end() - uni.begin());
	
	//���ֲ���


	return 0;
}