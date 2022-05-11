#include <iostream>
using namespace std;

//多态：不同类型的人去做同一件事情，结果不同(多种形态)：看人下菜

/*


*/

/*

//设计一个无法被继承的基类，只能让基类的构造函数变成私有，因为初始化子类对象的时候要去调用其父类的构造函数，但是没法使用,间接限制
//c++ 98的方式
class A
{
private:
    A(int a = 0)
        : _a(a)
    {
    }

public:
    //因为如果是一个成员函数，返回A 他必须是一个对象，但是他没有对象，加了一个静态就可以使用了
    static A createobj(int a = 0) //调用这个函数就可以使用了，获得父类的构造函数，如果是成员函数
    //静态的成员函数，没有this指针，只能访问静态的成员变量，和成员函数，不能访问_a 这些成员变量
    {

        return A(a);
    }

protected:
    int _a;
};
class B:public A
{

};
//子类继承了父类，但是构造函数被变成私有的了
int main()
{
    //因为我们把A 类型的构造函数变成一个私有的构造函数，所以他没有办法被使用，但是我们写了一个静态的成员函数就可以获得这个东西
    A aa=A::createobj(10);//就可以这样把对象创建出来了,
    //这里是A 去调用，说明已经初始化了，所以要又静态的才可以

    return 0;
}

*/

// c++11 的方式
//让A 这个类不能被继承，只要加一个final就可以了，加了final的话这个类就没有办法被继承

class A final //不希望A 被继承

{
protected:
    int _a;
};

// class B:public A
// {

// };

class C
{
public:
    virtual void f() final // 我不想他被重写
    {
        cout << "hello " << endl;
    }
};
// class D :public C
// {
//     public:
//     virtual void f()//重写
//     {
//         cout<<"world"<<endl;
//     }
// };

/*


override
class car
{
    public:
    virtual void drive()
    {

    }
};


class benz: public car
{
    public:
    virtual void drive()  override//如果一不小心父类没有加virtual的话，就会构成隐藏关系，加了之后就会检查是否完成重写
    {

    }
};

int main()
{
    return 0;
}

*/

// 抽象类，无法实例化出对象

//抽象---在现实世界中没有对应的实物
//一个类型，如果一般在现实世界中，没有具体的对应事物，就定义成抽象类比较好，人，人都有职能是学习（学生，老师），老师的职能是传道授业
//动物也是抽象类，熊猫什么都要去继承他
//抽象类强制了子类去完成重写、某一个虚函数
//override完成检查的工作，
//纯虚函数更体现了接口继承（实现继承），继承下来是为了重新实现



//抽象类里面多了一个虚函数表指针（表就是数组，里面存的虚函数的地址，函数指针数组），会有多4个字节


class car
{
public:
    virtual void drive() = 0; //纯虚函数，是只声明，不实现的,因为实现没有价值,因为包含纯虚函数的类不能实例化出对象

    // virtual void fly()=0
};

class benz : public car
{
public:
    virtual void drive()//重写虚函数，
    {
        cout << "hello " << endl;
    }
};

int main()
{

    //可以用指针和引用
    car *p=new benz;//用父类的对象来管理子类
    p->drive(); //可以调到
    return 0;
}