#include <iostream>
#include<cstdio>
using namespace std;

class person
{
public:
    virtual void buyticket()
    {
        cout << "all" << endl;
    }
    void f()
    {
        cout << "hello world" << endl;
    }

protected:
    int _a = 0;
};
class student : public person
{
public:
    virtual void buyticket()
    {
        cout << "half" << endl;
    }

private:
    int _b = 0;
};

void func(person &p) // p看到的还是父类对象，看到的一样是个虚表指针，只不过父类对象里面的虚表里面，是重写的虚函数，所以就是调用不同的函数
//对象的虚函数表里面存的是什么，就决定了掉的是什么
{
    p.buyticket(); //找虚
    p.f();         //普通函数调用是直接调用
}

//多继承中的虚表
class base1
{
public:
    virtual void func1()
    {
        cout << "base func1" << endl;
    }
    virtual void func2()
    {
        cout << "base func2" << endl;
    }

private:
    int b;
};

class base2
{
public:
    virtual void func1()
    {
        cout << "base2 func1" << endl;
    }
    virtual void func2()
    {
        cout << "base2 func2" << endl;
    }

private:
    int b2;
};

class derive : public base1, public base2
{
public:
    virtual void func1() //
    {
        cout << "derive func1" << endl;
    }
    virtual void func3()
    {
        cout << "derive func3" << endl;
    }

private:
    int d;
};
//构成多态就是运行时决议调用谁
//不构成多态就是编译时决议调用谁

class Base
{
public:
    virtual void func1() { cout << "base1::func1" << endl; }
    virtual void func2() { cout << "base1::func2" << endl; }

private:
    int a;
};


class driver : public Base
{
public:
    virtual void func1()
    {
        cout << "driver func1" << endl;
    }
    virtual void func3()
    {
        cout << "deriver func3" << endl;
    }
    void func4()
    {
        cout << "derive func4" << endl;
    }

private:
    int b;
};


typedef void(*vfptr)() ;//函数指针的typedef方式不一样，把名字定义在中间，重命名为vfptr
//对函数指针进行重命名


void printvftable(vfptr table[])//函数指针数组
{
    for(int i=0;table[i]!=nullptr;i++)//在windows下虚表最后一个元素是空
    {   
        printf("vft[%d] :%p\n",i,table[i]);
        //我们有了一个函数地址，那么就可以调用它
        vfptr f=table[i];//f指向了函数指针的地址
        f();//调用了这个函数
        //我们发现这个是可以调用的
        //就算是私有的我们也可以调用到，因为我们这里不是通过直接调用，而是通过取出来了虚函数的地址，
        //这里不是通过对象调的
        //有了虚表就会有一些安全隐患

    }
    cout<<endl;
}
int main()
{
    person mike;
    student jason;
    func(mike);  //到mike里面找到虚函数指针，在虚函数指针里面找到对应的虚函数，然后调用它
    func(jason); //如果是子类，就会发生切割（切片），
    person &r1 = jason;
    person r2 = jason;
    student s1;
    student s2;

    derive d; //多继承之后，就有两个虚表，
    //子类里面有两张虚表，它自己的虚函数只放一个虚表，放在第一个继承的虚表里面
    // base1和base2里面都有func1，但是发现他们的地址不一样，只是jump指令，最后会jump到一个地方去了

    


    Base b;//虚表的指针在初始化列表（构造函数）里面处理，内置类型不处理，自定义类型调用自己的构造函数处理
    //vfptr(virtual function table pointer )

    //printvftable((vfptr*)(*(void**)&b));//取虚表数组的首元素地址，在这个地方的头4个字节, 先转化成int* 再解引用就变成int了可以获得头4个字节了，但是类型不匹配, 所以还得再强转一下
    //取一个对象里面的虚表（虚函数指针数组）
    //这样就弄出来了虚表里面的两个函数
    //不能直接转化的，不是所有类型都可以强制类型转化的（不相关的类型是不可以直接转化的，相关类型之间才可以直接转），要先取出来对应的地址
    driver s;
    //printvftable((vfptr*)(*(void**)&s));//取虚表数组的首元素地址，在这个地方的头4个字节, 先转化成int* 再解引用就变成int了可以获得头4个字节了，但是类型不匹配, 所以还得再强转一下

    //重写的func1，拷贝下来的func2，还有自己的 func3
    derive k;
    base2* l=&k;
    //printvftable((vfptr*)*((void**)((char*)&k+sizeof(base1))));//取虚表数组的首元素地址，在这个地方的头4个字节, 先转化成int* 再解引用就变成int了可以获得头4个字节了，但是类型不匹配, 所以还得再强转一下
    printvftable((vfptr*)*((void**)(l)));//取虚表数组的首元素地址，在这个地方的头4个字节, 先转化成int* 再解引用就变成int了可以获得头4个字节了，但是类型不匹配, 所以还得再强转一下
    //获得base2的虚函数表，使用切片的方法，这样就很容易了
    return 0;
}