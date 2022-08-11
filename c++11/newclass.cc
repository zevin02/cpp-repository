#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include<map>
using namespace std;
#include<thread>
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
void ss(const T &t)//解析最后一个参数, 递归推的终止函数
{
    cout<<"endl"<<endl;
    cout<<t<<endl;
}
template<class T,class ...Args>

//解析并打印参数包里面的每一个参数的类型和值
//T就是每个参数包的参数类型，val就是每个参数包里面对饮的值

void ss(T val,Args ... args)//这里的T就是会匹配第一个参数,
{
    cout<<typeid(val).name()<<":"<<val<<endl;
    ss(args...);//用递归的形式进行解析args后面就是剩余的参数包,如果只有一个函数的时候就不会调用它了
}

//但是每次都像这样多加一个参数，再写一个终止函数，那就很烦了
//我们只想要写一个参数的模板的可变参数
//展开函数


template<class T>
int printlist(T val)
{
    T copy(val);
    cout<<typeid(T).name()<<":"<<val<<endl;
    return 0;
}


template<class ...Args>
void showlist(Args ...args)//可以传入一个或者多个参数，可以自动推导这个类型
{
   int arr[]={printlist(args)...};//这里的[]没有给值，它会自己去看里面有多少个值，推出来，会一个一个往下调用print参数包 
   cout<<endl;
   //这里因为要去计算arr数组的大小，所以会去把参数包给展开
}

/*
    pushback现在可以支持右值引用，现在可以支持资源的转移，
    左值的pushback就是在原来的一块空间后面，然后在开一个空间，这个空间指向新开的那个空间
    而右值的就是在原来已近都开好的空间的基础上，调用定位new，把资源转移到这个空间上面

*/

/*
    emplace_back

*/

void demo()
{
    vector<pair<int,string>> lt;
    lt.push_back(make_pair(10,"dsad"));//pushback可以这样执行
    lt.emplace_back(make_pair(10,"das"));//emplaceback也可以这样执行，因为它里面的是可变参数模板，并且是万能引用
    lt.emplace_back(10,"fd");//也可以这样使用，它这里面的这两个参数就会一起生成了pair
    //因为我们学过初始化列表
    lt.push_back({2,"fdas"});//这个对于多参数也可以这样去使用
    /*
        * 对于右值对象，emplace_back会先构造一个对象，再去移动构造
        * 对于一个左值对象，emplace_back会先去构造一个左值对象
        * 对于参数包，emplace_back直接使用参数包定位new去构造
        * 
    
    */
}


//thread是不允许拷贝的构造的

void threads()
{
    //线程库
    thread t1;//这里可以创建一个无参的，即线程不执行
    thread t2(print, 10,2);//第一个参数因为是模板，所以它是一个万能引用，func它不一定是一个函数，可调用对象就可以了，即可以传左值也可以传右值
    //第二个参数是可变的模板参数，可以传0-n个参数
    //第一个可以
    t2.join();//这和c的线程库也是一样的
    //不像c语言要使用一个结构体传进去，

    //原来在c语言我们是使用线程id来控制这些线程的
    //但是现在线程，可以使用一个容器去管理

    int n;
    cin >> n;
    vector<thread> vthds;
    vthds.resize(n);//提前开好n个线程

    //现在有任务来了，我们要让这些线程都跑起来
    for (auto& e : vthds)
    {
        e = thread(print,100,2);//这里构造一个匿名对象赋值给它,这个地方又利用了一个移动赋值,把右边的这个临时
        //对象传过去给e去执行,出了作用域就销毁了
        //右边是一个右值
        //这里的线程不支持拷贝构造，把一个线程拷贝给另一个线程，所以直接delete掉了
        //线程也不支持赋值，但是可以支持移动赋值

    }
    for (auto& e : vthds)
    {
        e.join();//e就是取到里面的每一个对象,join掉
    }
}



int main()
{
    //我们如何拿到模板参数的类型和对象呢
    // showlist(1);
    // showlist(1,'a');
    // showlist("string",'A',1);
    ss(1.1,2,"dasd");
    showlist(1,2,"sad");
    return 0;
}


