#include<iostream>
using namespace std;

//

class A
{

	int _a;
	int _b;
public:
	A()
	{
		cout << "A()" << endl;
	}
	~A()
	{
		cout << "~A()" << endl;
	}
};


int main()
{
	//总结malloc/free和new/delete 对于内置类型没有本质的区别，只有用法上的区别


	//动态申请int和5个int的数组

	//c语言

	int* ptr1 = (int *)malloc(sizeof(int));
	int* ptr2 = (int*)malloc(sizeof(int) * 5);

	//c++
	int* p3 = new int;
	int* p4 = new int[5];//动态申请5个int的空间
	int* p5 = new int(5);//申请1个int空间，初始化为5
	int* p6 = new int[5]{ 1,2 };//5个int也可以这样初始化


	//删除
	free(ptr1);
	free(ptr2);
	ptr1 = nullptr;
	ptr2 = nullptr;
	delete p3;
	delete[] p4;
	p3 = nullptr;
	p4 = nullptr;

	A* pa = (A*)malloc(sizeof(A));
	A* pa2 = new A;
	//对于自定义类型，new还可以调用其初始化，还可以开空间
	//malloc只会开空间

	A* pa3 = (A*)malloc(sizeof(A) * 5);
	A* pa4 = new A[5];

	//delete要先调用指针类型的析构函数，再去释放空间给堆上
	delete pa3;
	delete[] pa4;



	return 0;

}