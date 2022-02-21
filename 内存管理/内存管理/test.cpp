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

//����new��delete��Ӧ��
struct ListNode
{
	ListNode* prev;
	ListNode* next;
	int _val;

	ListNode(int val)//��ʼ���б�
		:prev(nullptr)
		,next(nullptr)
		,_val(val)
	{}



};

class List
{
public:
	List()//˫���ͷѭ������,���캯����ʼ��
	{
		_head = new ListNode(-1);
		_head->next = _head;
		_head->prev = _head;
	}
	void pushback(int val)
	{
		ListNode* newnode = new ListNode(val);//�����õĻ�������һ�ξ�ɾ��һ�Σ���Ϊnew����operator new ��operator new�ֵ���malloc��
		//�������ǾͿ��Դ���һ���µ�operator new��ʹ���ڴ��
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
		_a = new int[capacity];//����*a�Ĵ����ʼ���ǳ�����
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
//	ListNode* n2 = new ListNode(0);//��������
//
//	//���ھͲ�����malloc֮�����init��destroy���Զ��Լ�����
//	Stack* s1 = new Stack;//���Զ����ù��캯���Ϳ��ռ䣬
//	delete s1;//����������������������е���Դ���ͷſռ䣬�Ȱ��������Դ���ɵ������ͷŵ�s1ָ�����ռ���ͷŵ�
//
//
//}
//




//int main()
//{
//	//�ܽ�malloc/free��new/delete ������������û�б��ʵ�����ֻ���÷��ϵ�����
//
//
//	//��̬����int��5��int������
//
//	//c����
//
//	int* ptr1 = (int *)malloc(sizeof(int));
//	int* ptr2 = (int*)malloc(sizeof(int) * 5);
//
//	//c++
//	int* p3 = new int;
//	int* p4 = new int[5];//��̬����5��int�Ŀռ�
//	int* p5 = new int(5);//����1��int�ռ䣬��ʼ��Ϊ5
//	int* p6 = new int[5]{ 1,2 };//5��intҲ����������ʼ��
//
//
//	//ɾ��
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
//	//�����Զ������ͣ�new�����Ե������ʼ���������Կ��ռ�
//	//mallocֻ�Ὺ�ռ�
//
//	A* pa3 = (A*)malloc(sizeof(A) * 5);
//	A* pa4 = new A[5];
//
//	//deleteҪ�ȵ���ָ�����͵�������������ȥ�ͷſռ������
//	delete pa3;
//	delete[] pa4;
//
//
//
//	return 0;
//
//}




//new ��delete�ĵײ�

//int main()
//{
//	//��malloc���÷���һ����
//	Stack* ps1 = (Stack*)operator new(sizeof(Stack));//ֻ�Ὺ�ռ䲻����ù��캯����
//	
//	//operator new�е���malloc�����ڴ棬ʧ���Ժ󣬸�Ϊ���쳣���������������c++����������Դ������ķ�ʽ
//	//���operator�Ǹ�new�õ�һ�㲻�Ǹ������õģ�
//
//	//operator delete ps1;//��ֻ�����ٿռ䣬��free���
//	
//
//	return 0;
//}

//�ػ�������ʹ���ڴ������ռ䣬���Ч�ʣ��Ͳ���ʹ��һ�ξ�����ռ�
//���б�ÿ�β������ݵ�ʱ���һ�㣬��Ҫÿ����һ�ξ�����ռ�



//��λnew
//��λnew���Ѿ������ԭʼ�ڴ�ռ��е��ù��캯����ʼ��һ������
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
	new(p)A(1);//new(��ַ)���ͣ���һ���Ѿ�����õ��ڴ���ó�ʼ�����캯���������ٿռ�
	//�����ڴ�����ľ��ö�λnew

	//��������
	p->~A();//
	operator delete(p);
	return 0;
}



//�ڴ�й¶
//1--��̬������ڴ棬��ʹ���ˣ���û�������ͷţ��ʹ����ڴ�й©��
//2--�ڴ�й¶��Σ����
//a�������ڴ�й¶�Ľ��̻��������������̽���ʱ��Щ�ڴ�ỹ��ϵͳ��������Σ��
//b�������ڴ�й¶�Ľ��̷��������������罩ʬ�ڴ棬ϵͳ�õ��ڴ�Խ��Խ��
//c����Ҫ�������еĳ�������ڴ�й¶��Σ���ܴ�ϵͳ��Խ��Խ������������崻�  ---����������
