#include<iostream>
using namespace std;
//1.类模板,模板可以接收任意个数的参数
#include<tuple>
#include<array>
#include<vector>
#include<memory>
template<class... Args>
struct A{
    //传入参数
    A(const Args&... args)
    {
        // cout<<args...;
    }
    int x;
    int y;
};

//2.计算参数的个数
template<class ... Args>
size_t count(const Args... args)
{
    constexpr size_t size=sizeof...(args);
    return size;
}

//3.使用可变参数实现一个tuple
template<class ...Args>
//返回类型可以是一个自动的
auto maketuple(const Args... args)
{
    //使用可变参数，可以理解为参数的展开
    return std::make_tuple(args...);
}

//4.使用可变参数构造一个数组
template<class... Args>
auto makearray(Args ... args)
{
    return array{args...};//初始化列表展开
}

struct Person {
    std::string name;
    int age;

    // Constructor
    Person(std::string n, int a) : name(n), age(a) {}
};

//5.传入类型和参数列表
template<class T,class ...Args>
unique_ptr<T> make_struct(Args... args)
{
    return unique_ptr<T>(new T(args...));//使用可变参数来进行初始化
}

//6.折叠表达式
template<class ...Args>
void print(Args... args)
{
    ((cout<<args),...);//前面一个括号就是一个初始操作，使用逗号表达式，就是所有操作都会执行
    //后面的操作会按照前面的操作一直进行
    
}


int main()
{
    A a(1,2,false);
    cout<<count(1,3,"false")<<endl;
    auto t=maketuple(2,3,4);//获得一个元组
    cout<<get<0>(t);
    for(auto v:makearray(3,4,5))
    {
        cout<<v<<" ";
    }
    auto ptr=make_struct<Person>("lily",10);//传入参数类型为Person，以及参数列表
    cout<<ptr->age<<endl;
    print(1,"sa",23);
    return 0;
}