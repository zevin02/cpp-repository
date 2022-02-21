#include<iostream>
using namespace std;


//泛型编程
//模板

//c语言交换
void swapint(int *a,int *b)
{}

//c++
//c++可以重载
void swap(int & a,int& b)
{}
void swap(double& a,double&b)
{}


//函数模板
template<class T>//也可以这样template<typename T>，模板参数列表--参数的类型

//也可以定义多个类型
//template<class T1,class T2>

//无论有多少个函数类型，都用他就可以了，自定义类型也可以
void swap(T& a, T& b)//函数参数列表，参数对象，
{
	T x = a;
	a = b;
	b = x;
}

//int main()
//{
//	int a = 0, b = 1;
//	double c = 1.1, d = 2.0;
//	//我们写函数交换
//	swap(a, b);//调用的是实例化之后的函数，模板实例化
//	swap(d, c);
//	char e = ' ', f = 'a';
//	//很麻烦都是类似的，这些swap最大的不同再类型上面，只是单纯的类型不一样其他东西都是一样的，
//	
//	return 0;
//
//}

//模板和印刷术非常像
//普通情况下，如，要抄一首诗，1000编，让1000个人来抄，效率很低
//我们就可以把诗词刻在一个模具上面，印刷出来1000份，非常的方便
template<class t>
t add(const t& a, const t& b)
{
	return a + b;
}


//template<class T1,class T2,class T3>
//T1 add(const T2& a, const T3& b)
//{
//	return a + b;
//}


//int main()
//{
//	int a = 1, b = 2;
//	double c = 1.1, d = 2.3;
//	cout << add(a, b) << endl;
//	cout << add(c, d) << endl;
//	//如果要对于a和d加,不可以直接弄
//	//1.强制转
//cout<<add((double)a, d)<<endl;//这些都是自己推
// 
////2.显示实例化
//cout << add<int>(a, d) << endl;//指定我们要实例化的类型，指定t用int类型
//cout << add<double>(a, d) << endl;
//cout << add(c, d) << endl;
//	return 0;
//}

//类的模板，语法也是类似的
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
		_a = new t1[capacity];//对于*a的处理初始化非常方便
	}
	~Stack()
	{
		delete[] _a;
		_a = nullptr;
	}
};

int main()
{
	Stack st1(2);//存int
	Stack st2(2);//存double

	return 0;
}