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
	//�ܽ�malloc/free��new/delete ������������û�б��ʵ�����ֻ���÷��ϵ�����


	//��̬����int��5��int������

	//c����

	int* ptr1 = (int *)malloc(sizeof(int));
	int* ptr2 = (int*)malloc(sizeof(int) * 5);

	//c++
	int* p3 = new int;
	int* p4 = new int[5];//��̬����5��int�Ŀռ�
	int* p5 = new int(5);//����1��int�ռ䣬��ʼ��Ϊ5
	int* p6 = new int[5]{ 1,2 };//5��intҲ����������ʼ��


	//ɾ��
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
	//�����Զ������ͣ�new�����Ե������ʼ���������Կ��ռ�
	//mallocֻ�Ὺ�ռ�

	A* pa3 = (A*)malloc(sizeof(A) * 5);
	A* pa4 = new A[5];

	//deleteҪ�ȵ���ָ�����͵�������������ȥ�ͷſռ������
	delete pa3;
	delete[] pa4;



	return 0;

}