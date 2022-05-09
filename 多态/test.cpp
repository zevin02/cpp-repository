#include <iostream>
using namespace std;

/*
class Person
{
public:
    virtual void BuyTicket()//虚函数，只能去调用它
    {
        cout << "买票--全票" << endl;
    }
};
class Student : public Person
{
public:
//子类中满足三同（函数名相同，参数返回值相同）就叫做重写
//本质就是不同的人去做同一件事情，结果不一样
   virtual void BuyTicket()
    //如果不是虚函数就构成隐藏，父类的只能显示调用
    {
        cout << "买票-半价" << endl;
    }
};


//满足多态就就和类型无关了，
void func(Person &p)//不存在类型转换，会使用切片，

{
    p.BuyTicket();
    p.BuyTicket(10);//调不到，这和隐藏没有关系，这里是父类
}


//构成多态，传的是哪个类型的对象，调用的就是这个类型的虚函数------和对象有关
//不构成多态，调用的就是p这个类型的虚函数   ------和类型有关

/*

void func(Person *p)
{
    p->BuyTicket();
}
/ void func(Person* p)//我们没有用父类的指针和引用，而是用对象,就不能实现多态
{
    p->BuyTicket();
}

*/

/*
int main()
{
    Person ps;
    Student st;
    func(st);//正常来说因为我们是父类的引用，所以的对父类使用，一定是没有问题的，但是这个对子类也是可以使用的
    //构成隐藏和父类没有关系，父类不受影响，和子类的函数
    func(ps);//不构成多态这样用就会报错
    return 0;
}

*/

class Person
{
public:
    virtual ~Person()//析构的名字都被特殊处理过了，差个虚函数的条件，这样就能够实现多态了
    {
        cout << "person" << endl;
    }
};
class Student : public Person
{
public:
    virtual ~Student() //

    {
        cout << "student" << endl;
    }
};

//析构函数是否是虚函数都正常调用了
int main()
{
    /*
    Person p;
    Student s;//person也会被析构，但是没加virtual也没有关系，
    */
   //
    Person *p1 = new Person; // new 是开空间+构造函数
    Person *p2 = new Student;//这里是基类的指针，这里是父类的指针，就需要多态了
    Student *p3 = new Student;//这里是基类的指针,z这里不需要多态


    //p1->destructor()
    //p2->destructor()
    


    //多态申请的对象如果给了父类指针管理，那么需要析构函数是虚函数（我们直接全部都）
    delete p1;//析构函数+释放空间
    //我期望p1这里调用父类的析构函数
    delete p2;//指向student就掉student，又会掉person
    delete p3;
    //这里调用子类的析构函数
    //这里不构成多态，都指向person，因为p2也是person
    //构成多态才可以
    return 0;
}

//多态我们留