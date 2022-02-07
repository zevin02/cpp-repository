//c++语法特性
//
// 1.bool
//逻辑中用true来代替非0，false来代替0，可以提高代码可读性

#include<iostream>
#include<cstring>//相当于c语言的string.h
#include<cmath>//数学,三角函数，指数函数，浮点
#include<cstdlib>
using namespace std;
//int main()
//{
//	bool yes = true;//提高可读性
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


//c++标准库
//vector数组，
#include<vector>
//int main()
//{
//
//	//c语言实现数组
//	int arr2[100];
//	//c++
//	vector<int>arr1(100);//整数数组，
//	//vector还可以看作一个链表,动态的变长
//	vector<int >arr3(10);
//
//	vector<int>list;//链表,vector当作链表不弄大小
//	list.push_back(1);
//	list.push_back(2);
//	list.push_back(3);
//
//	//vector的遍历输入方式
//	int a;
//	vector<int> arr;
//	int n;
//	cin >> n;
//	//arr.size()就是数组有多少的数据
//	for (int i = 0; i < n; i++)
//	{
//		cin >> a;
//		arr.push_back(a);
//		//cout << arr[i] << endl;
//	}
//	//数组内容
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
//	//迭代器,iterator相当于c语言的指针，
//	vector<int>arr1(100);
//	arr1[0] = 100;
//	vector<int>::iterator p1 = arr1.begin();//p就是首地址的
//	cout << *p1 << endl;
//
//	//指针与迭代器的使用对比
//	vector<int>arr(100);
//	int arr2[100];
//	vector<int>::iterator p;
//	int* p2 = nullptr;
//	//for (p = arr.begin(); p != arr.end(); p++)//迭代器也可以自增,从首地址到末地址指针
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
//	//vector的常见操作
//	vector<int> list;
//
//	//可以计算数组的元素个数
//	//销毁数组，
//	list.push_back(2);
//	list.push_back(4);
//	cout<< list.size()<<endl;
//	list.clear();
//	list.empty();//用来判断是否为空，相当于size是否为0，
////		list.begin();//
////	list.erase(p)//删除迭代器p位置的数据
////		list.pop_back();//尾删
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
//	cout << str1.size() << endl;//str1.length()长度
//	str1.insert(1, "aaa");//在1的位置插入aaa
//	string str2 = "cpp";
//	str1.append(str2);// 相当于c语言的strcat
//	str1.compare(str2);//相当于c语言的strcmp(str1,str2);
//	str1.push_back('a');
//	str1 += 'bvc';
//	str1 == str2;//判断是否相同
//	cout << str1 << endl;
//	return 0;
//}

#include<algorithm>
bool cmp(int a,int b)
{
	return a > b;//大于的排前面
}
int main()
{
	int arr[] = { 2,3,1,5,4 };
	sort(arr, arr + 5);//第一个参数是数组的头指针，第二个参数是最后一个元素的下一个的地址，内部使用的快速排序
	vector<int>arr1{ 2,3,1,5,4 };//vector的初始化
	sort(arr1.begin(), arr1.end(),cmp);
//	nth_element(arr1.begin(), arr1.beign() + 2, arr1.end());
	swap(arr1[1],arr1[2]);//交换两个数
	reverse(arr1.begin(), arr1.end());//反转

	//unique可以去重
	vector<int>uni{ 1,1,2,2,3,4 };
//	int newlength = unique(uni.begin(), uni.end() - uni.begin());
	
	//二分查找


	return 0;
}