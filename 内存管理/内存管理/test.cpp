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

//对于new和delete的应用
struct ListNode
{
	ListNode* prev;
	ListNode* next;
	int _val;

	ListNode(int val)//初始化列表
		:prev(nullptr)
		,next(nullptr)
		,_val(val)
	{}



};

class List
{
public:
	List()//双向带头循环链表,构造函数初始化
	{
		_head = new ListNode(-1);
		_head->next = _head;
		_head->prev = _head;
	}
	void pushback(int val)
	{
		ListNode* newnode = new ListNode(val);//这样用的话就是用一次就删除一次，因为new调用operator new ，operator new又调用malloc，
		//所以我们就可以存在一个新的operator new，使用内存池
		ListNode* tail = _head->prev;
		tail->next = newnode;
		newnode->prev = tail;
		_head->prev = newnode;
		newnode->next = _head;

	}

private:
	ListNode* _head;
};





class Stack
{
private:
	int _top;
	int _capacity;
	int* _a;
public:
	Stack(int capacity = 4)
		:_top(0)
		,_capacity(4)
	{
		_a = new int[capacity];//对于*a的处理初始化非常方便
	}
	~Stack()
	{
		delete[] _a;
		_a = nullptr;
	}
};
//int main()
//{
//	//c
//	struct ListNode* n1 = (struct ListNode*)malloc(sizeof(ListNode));
//	n1->prev = nullptr;
//	n1->next = nullptr;
//	n1->_val = 0;
//
//	//cpp
//	ListNode* n2 = new ListNode(0);//更加容易
//
//	//现在就不用在malloc之后调用init和destroy会自动自己调用
//	Stack* s1 = new Stack;//会自动调用构造函数和开空间，
//	delete s1;//调用析构函数，清理对象中的资源再释放空间，先把里面的资源给干掉，再释放掉s1指向的这空间给释放掉
//
//
//}
//




//int main()
//{
//	//总结malloc/free和new/delete 对于内置类型没有本质的区别，只有用法上的区别
//
//
//	//动态申请int和5个int的数组
//
//	//c语言
//
//	int* ptr1 = (int *)malloc(sizeof(int));
//	int* ptr2 = (int*)malloc(sizeof(int) * 5);
//
//	//c++
//	int* p3 = new int;
//	int* p4 = new int[5];//动态申请5个int的空间
//	int* p5 = new int(5);//申请1个int空间，初始化为5
//	int* p6 = new int[5]{ 1,2 };//5个int也可以这样初始化
//
//
//	//删除
//	free(ptr1);
//	free(ptr2);
//	ptr1 = nullptr;
//	ptr2 = nullptr;
//	delete p3;
//	delete[] p4;
//	p3 = nullptr;
//	p4 = nullptr;
//
//	A* pa = (A*)malloc(sizeof(A));
//	A* pa2 = new A;
//	//对于自定义类型，new还可以调用其初始化，还可以开空间
//	//malloc只会开空间
//
//	A* pa3 = (A*)malloc(sizeof(A) * 5);
//	A* pa4 = new A[5];
//
//	//delete要先调用指针类型的析构函数，再去释放空间给堆上
//	delete pa3;
//	delete[] pa4;
//
//
//
//	return 0;
//
//}




//new 和delete的底层

//int main()
//{
//	//跟malloc的用法是一样的
//	Stack* ps1 = (Stack*)operator new(sizeof(Stack));//只会开空间不会调用构造函数，
//	
//	//operator new中调用malloc申请内存，失败以后，改为抛异常处理错误，这样符合c++面向对象语言处理错误的方式
//	//这个operator是给new用的一般不是给我们用的，
//
//	//operator delete ps1;//就只会销毁空间，和free差不多
//	
//
//	return 0;
//}

//池化技术，使用内存池申请空间，提高效率，就不用使用一次就申请空间
//让列表每次插入数据的时候快一点，不要每次用一次就申请空间



//定位new
//定位new对已经分配的原始内存空间中调用构造函数初始化一个对象
class A
{
public:
	A(int a)
		:_a(a)
	{}
	~A()
	{

	}
private:
	int _a;
};

int main()
{
	A* p = (A*)malloc(sizeof(A));
	new(p)A(1);//new(地址)类型，对一块已经分配好的内存调用初始化构造函数，不开辟空间
	//对于内存池来的就用定位new

	//析构函数
	p->~A();//
	operator delete(p);
	return 0;
}



//内存泄露
//1--动态申请的内存，不使用了，又没有主动释放，就存在内存泄漏了
//2--内存泄露的危害：
//a，出现内存泄露的进程会正常结束，进程结束时这些内存会还给系统，不会又危害
//b，出现内存泄露的进程非正常结束，比如僵尸内存，系统用的内存越来越少
//c。需要长期运行的程序出现内存泄露，危害很大，系统会越来越满，甚至卡死宕机  ---服务器程序，
