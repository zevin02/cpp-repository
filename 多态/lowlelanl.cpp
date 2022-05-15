#include <iostream>
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
    virtual void func1()//
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

    derive d;//多继承之后，就有两个虚表，
    //子类里面有两张虚表，它自己的虚函数只放一个虚表，放在第一个继承的虚表里面
    //base1和base2里面都有func1，但是发现他们的地址不一样，只是jump指令，最后会jump到一个地方去了
    return 0;
}