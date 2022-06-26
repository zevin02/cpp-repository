#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

// default强制生成默认成员函数
//delete 禁止生成默认成员函数,单例模式，不允许拷贝，不允许赋值,只能有一个对象,在类里面也不可以使用这个默认成员函数
//final无法被继承，无法重写
//override检测是否有重写
class person
{
private:
    string _name;
    int _age=0;//缺省值c++11打的一个补丁，如果我们在外面没有初始化，就会用这个进行初始化
    person operator=(person& s)=delete;//只声明不实现，声明成私有，c++98防拷贝，但是这个在私有
public:
    person()=default;//原本编译器生不成，现在编译器就能生成了
    person(const char *name, int age)
        : _name(name), _age(age)
    {
    }
    person(person &p)
        : _name(p._name), _age(p._age)
    {
    }
};



// int main()
// {
//     //我们如果没有写构造函数的化，编译器会自动去生成一个构造函数
//     //但是如果我们写了构造函数，编译器就不会生成默认构造函数
//     person s;
//     return 0;
// }



/*
    拷贝构造和移动构造
    赋值和移动赋值
    拷贝构造-----深拷贝（string vector）

    移动构造————浅拷贝（资源移动）-------本质上就是资源的移动，狸猫换太子

    vector<int> func()
    {
        vector<int> ret;
        ....
        return ret;//这里就是一个传值返回就是会进行一个拷贝，但是以为有了一个移动构造，所以资源就不会太浪费了
    }
    vector<int> v=func();//以为ret是一个将亡值，所以直接把ret的资源给到v，减少了很多的处理
    
    移动赋值也是一样的道理


    移动构造和移动赋值也是一个默认的成员函数了
    * 如果没有实现自己移动构造，也没有实现析构，拷贝构造，拷贝赋值的任意一个（这四个都没有写才会处理），那么编译器才会自动生成一个默认的移动构造，
    那么对于内置类型会执行成员按字节拷贝，而对于自定义类型，看看它有没有写移动构造，有的话就掉，没有的话，就调用拷贝构造
    （1.默认生成的条件更加复杂，
        2. 自定义类型，内置类型）

    但凡我们写了其他函数，他就不会生成了
    * 同理移动赋值，和移动构造是一样的


    所以建议我们自己写移动构造和移动赋值

    而对于mystack s1;
        mystack s2=std::move(s1)
        就会使用默认生成的移动构造（里面的queue，会调用deque）

*/

/*
    模板的可变参数
    例如printf（formate，...）这就是一个经典的可变参数
    
*/

// template<class ...Args>
// //args就是一个可变参数模板包，代表是0到n个模板参数，可能没有参数
// void showlist(Args ...args)
// {
//     //我们怎么拿到第一个参数对应的东西呢,解析出内容
//     cout<<sizeof...(Args)<<endl;//这样就可以分别获取调用者调用，传入几个参数
//     //不支持使用args[i]

// }

//这里的args就是一个函数参数包，形参对象，

//所以不好解析，所以我们要增加一个模板参数，传入我们一共传入了多少个参数


//解析并打印出，每个参数 的类型和值
template<class T>
void ss(const T &t)//解析最后一个参数
{
    cout<<t<<endl;
}
template<class T,class ...Args>

void ss(T val,Args ... args)//这里的T就是会匹配第一个参数
{
    cout<<typeid(val).name()<<":"<<val<<endl;
    ss(args...);//用递归的形式进行解析args后面就是剩余的参数包,如果只有一个函数的时候就不会调用它了
}


int main()
{
    //我们如何拿到模板参数的类型和对象呢
    // showlist(1);
    // showlist(1,'a');
    // showlist("string",'A',1);
    ss(1.1,2,"dasd");
    return 0;
}