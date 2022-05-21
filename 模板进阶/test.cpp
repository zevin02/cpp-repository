#include <iostream>
#include <array> //arry就是一个定长的数组

using namespace std;

/*
* 非类型模板参数
* 类模板的特化
* 模板的分离编译

*/

//在cpp里面不推荐使用宏，我们可以使用const或者
// #define N 100
//非类型模板参数，然后传值就可以了（定义的是一个常量,整形常量）

//模板参数也必须是从右边往左缺省
template <class T, size_t N = 100>
//使用模板一个栈存int 一个栈存double
class mystack
{
public:
    void push(const T &x)
    {
    }

private:
    T _a[N];
    size_t top;
};

template <size_t N> //我们直接使用也可以
class A
{
};
void test1()
{
    mystack<int, 100> st1; //我们想让st1是100
    mystack<int, 200> st2; //我们想让st2是200
    mystack<int> st3;      //缺省
    array<int, 100> a1;    //没什么用，也在栈上，对越界的检查更加严格，和c语言的数组一样
    int a[100];            //这两个一样
    a1[4] = 4;             //他也不会初始化，对象
    a[4] = 4;              //数组
    cout << sizeof(a1) << endl;

    A<100> aa; // A这个类直接使用
}
template <class T>
bool objless(const T &left, const T &right)
{
    return left < right;
}

/*
函数模板的特化
1.必须有一个基础的函数模板
2。关键词template后面接一对空的尖括号
3.函数名后跟一对简括或《》，里面指定需要特化的类型
4.函数参数列表：必须和函数模板的基础参数类型完全一致

*/
template <class T>
//基础模板，模板的特殊化
bool isequal(T &left, T &right)
{
    return left == right;
}
#include <cstring>
//特化
template <>
bool isequal<const char *const>(const char *const &left, const char *const &right) //特化成const char* 的，但是这个比较没用
{
    return strcmp(left, right) == 0;
}

void test2()
{
    cout << objless(1, 2) << endl; //调用的参数匹配
}

template <class T1, class T2>
class Date
{
public:
    Date() { cout << "Date<T1,T2>" << endl; }

private:
    T1 _d1;
    T2 _d2;
};

//特化就是特殊化------特殊处理，比如需要针对某些类型进行特殊化处理
//以便让大部分的类型都可以使用，只有小部分的类型是无法使用的，通过这种模板特殊化的方式就可以了
//一般情况下没有，但是有的时候很有用
//特化是对参数的进一步的限制，



template <>
class Date<int, char> //如果模板参数传的是int或者char就调用这个
{
public:
    Date() { cout << "Date<int,char>" << endl; }

private:
    int _d1;
    char _d2;
};


//全特化：所有模板参数都给确定的类型，如上


void test3()
{
    Date<int ,int>d1;//int,int会调用第一个
    Date<int ,char>d2;//int,char 会调用特殊化的Date

}
//偏特化，半特化，只对部分的参数进行特化
template<class T3>
class Date<T3,char>
{
    public:
    Date()
    {
        cout<<"Date<T3,char>"<<endl;
    }
    private:

};




//模板的分离编译
/*
最大的优势：方便我们维护，看xxx.h了解框架，看xxx.cpp了解功能，实现细节。

我们想要看一个类的框架，只要看类的声明和结构的定义就可以了，成员大概是干什么的，有什么的功能.h
我想看每个某个具体是如何实现的，方便维护                         .cpp



把满足一个功能的放到一个名字里面，

有人离职了，我们去接收这个项目，就很容易看他的代码，协作的时候看一下同事写的代码

*/






int
main()
{
    test1();
    test2();
    test3();
    Date<int ,char> d;//全特化
    Date<double ,char> d1;//半特化
    Date<int ,int> d2;//非特化
    Date<int ,double> d3;//非特化

    return 0;
}
