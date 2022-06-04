#include<iostream>
#include<string>
#include<vector>
#include<list>
#include<map>
#include<typeinfo>
#include<array>
using namespace std;



struct Point
{
    int _x;
    int _y;
   /*explicit*/ Point(int x,int y)
    :_x(x),_y(y){cout<<"1"<<endl;}
};


class A
{
    private:
    int _a;
    public:
    explicit A(int a)
    :_a(a){}

};


    //单参数类型支持隐式类型转换
void test2()
{
    A aa(2);//单参数的类型，可以使用正常的方式
    //A b=2;//也可以使用这种隐式类型的转换
    //2拷贝构造一个A，在进行拷贝构造成b
    //加一个explicit，就不能这样了
    string s1="hjs";//string的构造函数没有加explicit
    vector<string> v;
    v.push_back("hjk");//这也是隐式类型转换

}



void test1()
{

    //以前
    Point p={1,2};//c语言是使用这种方式来初始化
    int brr[5]={1,2,3,4,5};//使用这种大括号进行初始化

    ////////////////////////////////////////////
    //现在s
    int a=1;
    int b={2};//现在还可以这样进行初始化,=也省略了
    int c{3};
    int arr[5]{1,2,3,4};
    Point k{1,2};
    int * ptr=new int[5]{1,2,3};//初始化了前3个值，后面的值全都是0
    Point* ptrd=new Point[2]{{1,1},{2,2}};//现在还可以这样进行初始化,里面必须要又两个{}
    //new要去调用他的构造函数



    //正常调用point
    Point p1(1,2);//调用构造函数
    
    //c++11支持的多参数的构造函数
    Point p2={1,2};
    Point p3{1,2};



}

void test3()

{
    //都是因为支持initializer_list的构造函数

    //以前的vector初始化
    vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    vector<int> v2={1,2,3,4};//现在vector也可以这样初始化, 掉的就是initializer list进行初始化

    initializer_list<int> lt={1,2,3};//
    list<int> l={1,2,3};//链表也可以这样初始化
    map<string,string> dic={{"dasd","dsa"},{"dsada","fd"}};//map也可以
    v2={10,20,30};//也可以用赋值，不是构造，在赋值运算符重载那里使用了initialzer_list 

    for(auto e:v2)
    {
        cout<<e<<" ";
    }

}

int func(int a)
{
    return a;
}
void test4()
{
    const int x=10;
    cout<<typeid(x).name()<<endl;//获得x的类型名字
    decltype(x) z=2;//获得x的类型名，来初始化另一个变量
    double y=2.2;
    decltype(x*y) ret;//ret类型为double
    decltype(&x) p;//p类型为int*

    int(*func)(int)=func;//函数指针
    auto pfunc=func;//直接用auto也可以
    decltype(pfunc) pfun3=func;//定义一个变量
    map<string,string> dict={{"sort","排序"},{"insert","插入"}};
    auto it=dict.begin();
    auto cpit=it;
    //但是不能把auto作为模板参数
    vector<decltype(it)> v;//这样就很方便
    v.push_back(it);

}
void test5()
{
    array<int,10> a;//静态数组
    a[11];//可以支持对越界的检查


}

void test6()
{
    //forward_list//单链表,很少用

}


int main()
{   
    test1();
    test2();
    test3();
    test4();
    return 0;
}
