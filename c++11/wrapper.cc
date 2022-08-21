#include <iostream>
using namespace std;
#include <functional>

//可调用对象类型，1. 仿函数  2.lambda表达式    3.函数指针
template <class F, class T>
T useF(F f, T x) //因为F的类型不一样,会推导出3个类型
{
    static int cout = 0;
    return f(x); //这个就有可能实例化出3种,
    //这样效率太低了
    //我希望让模板只实例化出一份，因为它只是可调用对象不同
}

double f(double i)
{
    return i / 2;
}
struct Functor
{
    double operator()(double i)
    {
        return i / 2;
    }
};

class Plus
{
public:
    static double fI(double x)
    {
        return x;
    }
    double f(double i)
    {
        return i / 2;
    }
};

void demo1()
{
    //我们使用包装器，之后就只实例化出一份对象了
    function<double(double)> f1(f);
    cout << useF(f1, 11.11) << endl;         //里面调用一个函数指针
    function<double(double)> f2 = Functor(); //仿函数对象

    cout << useF(f2, 11.11) << endl; //仿函数
    function<double(double)> f3 = [](double i)
    { return i / 2; }; //仿函数对象

    cout << useF(f3, 11.11) << endl;
}

void demo2()
{
    //包装出统一的类型
    function<double(double)> f1(f); //包装器里面,左边的double是函数的返回值,(double)是函数的参数,去构造它,这里包装了一个函数指针
    cout << f1(11.1) << endl;       //使用就和普通的一样用
    //包装仿函数
    function<double(double)> f2 = Functor(); //仿函数对象
    cout << f2(12) << endl;

    //只要是成员函数就要加&
    function<double(double)> f3 = &Plus::fI; //静态的成员函数
    //还可以包装成员函数
    cout << f2(10) << endl;
    //对于非静态的成员函数
    function<double(Plus, double)> ff = &Plus::f; //非静态的成员函数要多加一个Plus，因为有this指针
    cout << ff(Plus(), 123) << endl;
}

#include <stack>
#include <vector>
#include <map>
class Solution
{
public:
    int evalRPN(vector<string> &tokens)
    {
        //使用列表初始化
        //包装器，只要是可调用对象就行了,很方便
        //使用包装器之后就能用函数映射了

        map<string, function<int(int, int)>> opMapFunc; //动作和函数映射的map

        //命令增加了只需要加这个map这里,一个命令对应一个函数

        opMapFunc["+"] = [](int a, int b)
        { return a + b; }; //包装器，初始化用函数指针，仿函数，lambda表达式
        opMapFunc["-"] = [](int a, int b)
        { return a - b; }; //包装器，初始化用函数指针，仿函数，lambda表达式
        opMapFunc["*"] = [](int a, int b)
        { return a * b; }; //包装器，初始化用函数指针，仿函数，lambda表达式
        opMapFunc["/"] = [](int a, int b)
        { return a / b; }; //包装器，初始化用函数指针，仿函数，lambda表达式

        //也可以用列表初始化

        stack<int> s;
        int i = 0;
        int top;
        //逆波兰表达式，一个命令和一个函数的映射关系就可以用包装器来解决

        for (int i = 0; i < tokens.size(); i++)
        {
            string &str = tokens[i]; //用别名弄，减少了拷贝
            // str为操作数
            // map里面为操作数就找不到
            if (opMapFunc.find(str) == opMapFunc.end())
            {
                //说明就是操作数
                s.push(stoi(str)); //入栈
            }
            else
            {
                //这里就是操作符
                int left = s.top();
                s.pop();
                int right = s.top();
                s.pop();
                //取出来了数据
                s.push(opMapFunc[str](left, right));
            }
        }
        return s.top();
    }
};

// bind也是一个函数包装器
//接收一个可调用对象，生成一个可调用对象
int sub(int a, int b)
{
    return a - b;
}

class subber
{
public:
    int Sub(int a, int b)
    {
        return a - b;
    }
};

void demo3()
{
    function<int(int, int)> f = sub;
    cout << f(10, 3) << endl;

    //调整参数的顺序
    function<int(int, int)> f1 = bind(sub,placeholders::_1,placeholders::_2);//这个就是啥都没做
    cout << f1(10, 3) << endl;
    function<int(int, int)> f3 = bind(sub,placeholders::_2,placeholders::_1);//参数顺序调换了
    //这里的_1就是把原来的第一个参数换到现在的位置,_2就是把原来的第2个参数换到现在的第一个

    //这个就是可以把库里面的用的不习惯的函数，切换参数顺序

    //主要是通过绑定来进行调整参数个数


    cout << f3(10, 3) << endl;
    function<int(subber,int, int)> f4 = &subber::Sub;
    cout << f4(subber(),10, 3) << endl;//使用了用还要加一个对象
    //每次都这样用很烦
    function<int(int, int)> f5 = bind(&subber::Sub,subber(),placeholders::_1,placeholders::_2);//这样子进行绑定，第一个参数就绑死了，使用的时候就不需要再去添加
    cout << f5(10, 3) << endl;

    //假如说第一个参数都是一样的
    function<int(int)> f6=bind(&subber::Sub,subber(),100,placeholders::_1);//第一个参数都是100
    cout<<f6(20)<<endl;
    //这里也能用auto进行接收

    

}

int main()
{
    // demo1();
    // demo2();
    demo3();
    return 0;
}
