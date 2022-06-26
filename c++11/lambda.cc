#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

//可调用对象
/*
1. 函数指针  c
2  仿函数    c++98
3. lambda   c++11
4. 包装器
*/

void test1()
{
    int arr[] = {4, 1, 6, 4, 5, 6};
    sort(arr, arr + sizeof(arr) / sizeof(int), greater<int>()); //这里第三个参数调用仿函数，实现降序
}

//但是又可能要排序的顺序有很多项，我要按其中一项来排序
struct Goods
{
    string _name;
    double _price;
    int _evaluate;
    Goods(string name, double price, int evaluate)
        : _name(name), _price(price), _evaluate(evaluate) {}
};

//这里调用仿函数
struct comparepriceless
{
    bool operator()(const Goods &g1, const Goods &g2)
    {
        return g1._price < g1._price;
    }
};



//在{}作用域外面就必须为空
int a=0,b=2;
//也不能捕捉a和b，可以定义在全局，但是不能捕捉东西
// auto func=[a,b](){;};
//lambda之间不能互相赋值
int main()
{
    vector<Goods> v = {{"banana", 2.2, 12}, {"lamda", 3.2, 15}}; // initializer list
    
    auto priceless=[](const Goods& g1,const Goods&g2){return g1._price<g2._price;};//这里是一种方法,但是可以直接放到sort函数里面进行比较

    
    sort(v.begin(), v.end(), comparepriceless());                //完美想按照3个都进行排序
    sort(v.begin(), v.end(),[](const Goods& g1,const Goods&g2){return g1._price<g2._price;} );                  //这样写就很方便，
    sort(v.begin(), v.end(),[](const Goods& g1,const Goods&g2){return g1._evaluate<g2._evaluate;} );            //这样写就很方便，
    // c++98支持这样的使用仿函数，但是这样有点烦，要比较就要写好几个仿函数
    //所以我们就应该使用lamda表达式




    /*
      捕捉列表  参数，返回值，函数体实现（也可以叫匿名函数，）
      lambda表达式没有返回值可以不写，有返回值也可以不写，它可以自动推导

    */
    //实现一个两个数相加的lambda,lambda的底层实现实际上是被处理成一个匿名的仿函数，lambda+uuid的一个类
    //捕捉列表， 参数  返回值    函数体实现
    auto add1 = [](int a, int b) -> int
    { return a + b; }; //一般定义在局部域里面
    // auto add1=[](int a,int b){return a+b;};//一般定义在局部域里面
    decltype(add1) add2 = add1;
    cout << add1(1, 2) << endl; //调用
    //没有参数也可以省略
    // auto f=[](){cout<<"hghh"<<endl;};
    auto f = []
    { cout << "hghh" << endl; }; //没有参数可以省略参数列表
    f();                         //调用还是要像函数一样去调用

    //函数体和捕捉列表都是不能省略的
    //捕捉列表作用：
    int a = 1;
    int b = 3;
    auto s = [](int &a, int &b)
    { swap(a, b); };
    // s(a, b);

    auto swap2=[&a,&b]()mutable{//使用mutable进行修饰的时候，（）不能省略
        int z=a;
        a=b;
        b=z;
    };//mutable改变其常属性,但还要引用捕捉
    //捕捉的各种类型
    /*
    编译器根据[]来判断它是不是一个lambda表达式

        * [var]表示传值捕捉变量,多个值可以用，分割
        * [=]表示传值捕捉所有父作用域里面的变量，包括函数中的this
        * [&var]表示传引用捕捉var
        * [&]表示传引用捕捉所有父类作用域里的变量
         
        [=,&a,&b],以传值引用所有，但是以引用捕捉a，b
        [&,a,this]以引用捕捉所有，但是a和this用传值进行捕捉
        不能重复捕捉

    
    */
    swap2();
    cout<<a<<b<<endl;
    return 0;
}