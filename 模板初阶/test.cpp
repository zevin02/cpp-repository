#include<iostream>
using namespace std;


//���ͱ��
//ģ��

//c���Խ���
void swapint(int *a,int *b)
{}

//c++
//c++��������
void swap(int & a,int& b)
{}
void swap(double& a,double&b)
{}


//����ģ��
template<class T>//Ҳ��������template<typename T>��ģ������б�--����������

//Ҳ���Զ���������
//template<class T1,class T2>

//�����ж��ٸ��������ͣ��������Ϳ����ˣ��Զ�������Ҳ����
void swap(T& a, T& b)//���������б���������
{
	T x = a;
	a = b;
	b = x;
}

//int main()
//{
//	int a = 0, b = 1;
//	double c = 1.1, d = 2.0;
//	//����д��������
//	swap(a, b);//���õ���ʵ����֮��ĺ�����ģ��ʵ����
//	swap(d, c);
//	char e = ' ', f = 'a';
//	//���鷳�������Ƶģ���Щswap���Ĳ�ͬ���������棬ֻ�ǵ��������Ͳ�һ��������������һ���ģ�
//	
//	return 0;
//
//}

//ģ���ӡˢ���ǳ���
//��ͨ����£��磬Ҫ��һ��ʫ��1000�࣬��1000����������Ч�ʺܵ�
//���ǾͿ��԰�ʫ�ʿ���һ��ģ�����棬ӡˢ����1000�ݣ��ǳ��ķ���
template<class t>
t add(const t& a, const t& b)
{
	return a + b;
}


template<class T1,class T2,class T3>
T1 add(const T2& a, const T3& b)
{
	return a + b;
}


int main()
{
	int a = 1, b = 2;
	double c = 1.1, d = 2.3;
	cout << add(a, b) << endl;
	cout << add(c, d) << endl;
	//���Ҫ����a��d��,������ֱ��Ū
	//1.ǿ��ת
cout<<add((double)a, d)<<endl;//��Щ�����Լ���
 
//2.��ʾʵ����
cout << add<int>(a, d) << endl;//ָ������Ҫʵ���������ͣ�ָ��t��int����
cout << add<double>(a, d) << endl;
cout << add(c, d) << endl;
	return 0;
}

//���ģ�壬�﷨Ҳ�����Ƶ�
template<class t1>



class Stack
{
private:
	int _top; 
	int _capacity;
	t1 * _a;
public:
	Stack(int capacity = 4)
		:_top(0)
		, _capacity(4)
	{
		_a = new t1[capacity];//����*a�Ĵ����ʼ���ǳ�����
	}
	~Stack()
	{
		delete[] _a;
		_a = nullptr;
	}

	void Push(const t1& m);
};

template<class t1>

void Stack<t1>::Push(const t1& m)//Ҫָ����ģ��
{

}

int main()
{
	//��ģ�岻֧�ֲ������͵����ݣ�ֻ֧����ʾʵ������ָ��
	Stack<int> st1(2);//��int
	Stack <double>st2(2);//��double
	Stack<int*>st3;
	Stack<char>st4;
	st1.Push(1);

	return 0;
}